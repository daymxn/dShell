#include "../headers/command.h"

s_command* command(){
    s_command* new_object = safe_malloc(sizeof(s_command));
    new_object->type = COMMAND;
    new_object->argument_length = 0;
    new_object->memory_size = 0;
    new_object->arguments = NULL;
    new_object->left = NULL;
    new_object->right = NULL;
    return new_object;
}

void de_command(s_command* this){
    if(this == NULL) crash("de_command() was called with a NULL s_command");

    if(this->left != NULL) de_command(this->left);
    if(this->right != NULL) de_command(this->right);

    for(int i = 0; i < this->argument_length; i++){
        cleanup(V &this->arguments[i]);
    }

    this->argument_length = 0;
    this->memory_size = 0;
    cleanup(V &this->arguments);
    cleanup(V &this);
}

void add_argument(s_command* this, const char* argument){
    if(this == NULL) crash("add_argument() was called with a NULL s_command");

    this->memory_size += sizeof(char*);
    this->arguments = expand_memory(this->arguments, this->memory_size);
    this->arguments[this->argument_length] = argument;
    this->argument_length += 1;
}
