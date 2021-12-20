#include "../headers/internal.h"

char* builtins[] = {
        "cd",
        "help",
        "exit"
};

builtin* builtin_functions[] = {
        &b_cd,
        &b_help,
        &b_exit
};

const int NUMBER_OF_BUILTINS = sizeof(builtins) / sizeof(char*);

int b_cd(const char** args){
    if(args == NULL) return EXIT_SUCCESS;

    if(args[1] != NULL && chdir(args[1])){
        fatal("cd error");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int b_help(const char** args){
    printf("----- dShell -----" NEWLINE);
    printf("Builtin commands: " NEWLINE);

    for(int i = 0; i < NUMBER_OF_BUILTINS; i++){
        printf("~ %s" NEWLINE, builtins[i]);
    }

    return EXIT_SUCCESS;
}

int b_exit(const char** args){
    exit(EXIT_SUCCESS);
}

builtin* get_builtin(const char* name){
    if(name == NULL) crash("get_builtin() was called with a NULL name");

    for(int i = 0; i < NUMBER_OF_BUILTINS; i++){
        if(are_equal(name, builtins[i])) return builtin_functions[i];
    }

    return NULL;
}