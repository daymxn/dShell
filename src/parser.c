#include "../headers/parser.h"

void parse_type(s_command** commands, COMMAND_TYPE type){
    if(commands == NULL) crash("parse_type() was called with a NULL s_command");

    int index = 0;
    s_command* current = commands[index];
    while(current != NULL){
        if(current->type == type){
            apply_children(commands, index);
            index -= 1; // account for moved element
        }
        index += 1;
        current = commands[index];
    }
}

void shift_to_left(s_command** commands, int amount) {
    if(commands == NULL) crash("shift_to_left() was called with a NULL s_command");
    if(amount <= 0) crash("shift_to_left() was called with an invalid amount");

    int index = 0;
    while(commands[index + amount] != NULL){
        swap_pointers(V &commands[index], V &commands[index + amount]);
        index += 1;
    }
}

void apply_children(s_command** commands, int index) {
    if(commands == NULL) crash("apply_children() was called with a NULL s_command");
    if(index <= 0) crash("apply_children() was called with an invalid index");

    s_command* current = commands[index];
    current->left = commands[index - 1];
    current->right = commands[index + 1];
    commands[index - 1] = current;
    commands[index] = NULL;
    commands[index + 1] = NULL;
    shift_to_left(&commands[index], 2);
}

int condense_subshells(s_command** commands){
    if(commands == NULL) crash("condense_subshells() was called with a NULL s_command");

    int index = 0;
    s_command* current = commands[index];
    while(current != NULL){
        if(current->type == SUBSHELL_START){
            int end = condense_subshells(&commands[index + 1]);
            if(end == -1) crash("missing ')' for subshell");

            end += index + 1;
            de_command(commands[end]);
            commands[end] = NULL;

            current->left = parse(&commands[index + 1]);
            commands[index + 1] = NULL;

            current->type = SUBSHELL;

            shift_to_left(&commands[index + 1], end - index);
        }else if(current->type == SUBSHELL_END) return index;

        index += 1;
        current = commands[index];
    }
    return -1;
}

void parse_leftovers(s_command** commands) {
    if(commands == NULL) crash("parse_leftovers() was called with a NULL s_command");

    int index = 1;
    s_command* current = commands[0];
    while(commands[index] != NULL){
        current->left = commands[index];
        current = commands[index];
        commands[index] = NULL;
        index += 1;
    }
}

s_command* parse(s_command** commands){
    condense_subshells(commands);

    parse_type(commands, PIPE);
    parse_type(commands, REDIRECT_TO);
    parse_type(commands, REDIRECT_TO_OVERWRITE);
    parse_type(commands, ENDCOMMAND);

    parse_leftovers(commands);

    return commands[0];
}