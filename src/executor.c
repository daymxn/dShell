#include "../headers/executor.h"

EXIT_STATUS execute(s_command* command){
    if(command == NULL || command->type == STRING) return EXIT_SUCCESS;
    return (command->type == COMMAND) ? execute_command(command) : execute_special(command);
}

EXIT_STATUS execute_command(s_command* command) {
    if(command == NULL) crash("execute_command() called with a NULL command");

    int status = launch(command);
    if (status == EXIT_SUCCESS) status = execute(command->left);
    if (status == EXIT_SUCCESS) status = execute(command->right);
    return status;
}

EXIT_STATUS execute_special(s_command* command){
    if(command == NULL) crash("execute_special() called with a NULL command");

    EXIT_STATUS status;
    switch(command->type){
        case STRING:
        case SUBSHELL_START:
        case SUBSHELL_END:
        case COMMAND:
            crash("Invalid command called in execute_special()");
        case PIPE:
            return handle_pipe(command);
        case ENDCOMMAND:
            execute(command->left);
            return execute(command->right);
        case SUBSHELL:
            return handle_subshell(command);
        case NOT:
            return !execute(command->left);
        case AND:
            status = execute(command->left);
            return (status == EXIT_SUCCESS) ? execute(command->right) : status;
        case OR:
            status = execute(command->left);
            return (status != EXIT_SUCCESS) ? execute(command->right) : status;
        case REDIRECT_TO:
            return handle_redirect_to(command, false);
        case REDIRECT_TO_OVERWRITE:
            return handle_redirect_to(command, true);
    }
    return EXIT_FAILURE;
}


EXIT_STATUS handle_pipe(s_command* command){
    if(command == NULL) crash("handle_pipe() called with a NULL command");

    int old_stdin = safe_dup(STDIN_FILENO);
    int old_stdout = safe_dup(STDOUT_FILENO);

    int fd[2];
    if(pipe(fd)) fcrash("pipe failed");

    int input = fd[1];
    int output = fd[0];

    safe_dup2(input, STDOUT_FILENO);
    safe_close(input);

    EXIT_STATUS first_result = execute(command->left);

    safe_dup2(old_stdout, STDOUT_FILENO);
    safe_close(old_stdout);

    safe_dup2(output, STDIN_FILENO);
    safe_close(output);

    EXIT_STATUS second_result = execute(command->right);

    safe_dup2(old_stdin, STDIN_FILENO);
    safe_close(old_stdin);

    if(first_result != EXIT_SUCCESS) return first_result;
    if(second_result != EXIT_SUCCESS) return second_result;
    return EXIT_SUCCESS;
}

EXIT_STATUS handle_redirect_to(s_command* command, bool overwrite){
    if(command == NULL) crash("handle_redirect_to() called with a NULL command");

    const char* filename;
    s_command* right_child = command->right;
    s_command* left_child = command->left;

    if(right_child == NULL || left_child == NULL) crash("missing command for redirect");

    if(right_child->type != STRING && right_child->type != COMMAND){
        int old_stdout = safe_dup(STDOUT_FILENO);
        int fd[2];
        if(pipe(fd)) fcrash("pipe failed");

        safe_dup2(fd[STDIN_FILENO], STDOUT_FILENO);
        safe_close(fd[STDIN_FILENO]);

        execute(right_child);
        printf("\n");

        FILE* temp_file = fdopen(fd[STDOUT_FILENO], "r");
        if(temp_file == NULL) fcrash("fdopen failed");

        filename = read_line(temp_file);

        safe_fclose(temp_file);
        safe_close(fd[STDOUT_FILENO]); // might not be needed
        safe_dup2(old_stdout, STDOUT_FILENO);
        safe_close(old_stdout);
    }else{
        filename = right_child->arguments[0];
    }

    const char* mode = (overwrite) ? "w" : "a";
    FILE* fp = fopen(filename, mode);
    if(fp == NULL) fcrash("fopen failed");

    if(left_child->type == STRING){
        fprintf(fp, "%s", left_child->arguments[0]);
    }else{
        int old_stdout = safe_dup(STDOUT_FILENO);
        safe_dup2(fileno(fp), STDOUT_FILENO);

        execute(left_child);

        safe_dup2(old_stdout, STDOUT_FILENO);
        safe_close(old_stdout);
    }

    safe_fclose(fp);

    return EXIT_SUCCESS;
}

EXIT_STATUS handle_subshell(s_command* command){
    if(command == NULL) crash("handle_subshell() called with a NULL command");

    EXIT_STATUS status;
    int pid = fork();

    if(pid == -1) fcrash("Fork failed");

    if(pid){
        do {
            waitpid(pid, &status, WUNTRACED);
        }while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }else{
        execute(command->left);
        exit(EXIT_SUCCESS);
    }

    return status;
}

EXIT_STATUS launch(s_command* command){
    if(command == NULL) crash("launch() called with a NULL command");

    EXIT_STATUS status;

    builtin* cmd = get_builtin(command->arguments[0]);
    if(cmd != NULL) return (*cmd)(command->arguments);

    int pid = fork();

    if(pid == -1) fcrash("Fork failed");

    if(pid){
        do {
            waitpid(pid, &status, WUNTRACED);
        }while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }else{
        add_argument(command, NULL);
        execvp(command->arguments[0], (char *const *) command->arguments);
        fcrash("Error executing command");
    }

    return status;
}