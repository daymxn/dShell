#include "../headers/lifecycle.h"

_Noreturn void lifecycle(void){
    while(true){
        prompt("$");

        char* line = read_line(stdin);
        if(are_equal(line, "\n")){
            cleanup(V &line);
            continue;
        }
        s_command** commands = tokenizer(line);
        s_command* command_tree = parse(commands);
        execute(command_tree);

        de_command(command_tree);
        cleanup(V &commands);
        cleanup(V &line);
    }
}