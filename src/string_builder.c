#include "../headers/string_builder.h"

s_string_builder* string_builder() {
    s_string_builder* new_object = malloc(sizeof (s_string_builder));
    new_object->length = 0;
    new_object->memory_size = 0;
    new_object->characters = NULL;
    return new_object;
}

void add_character(s_string_builder* this, const char character) {
    if(this == NULL) crash("add_character() was called with a NULL s_string_builder");

    this->memory_size += sizeof(char);
    this->characters = expand_memory(this->characters, this->memory_size);
    this->characters[this->length] = character;
    this->length += 1;
}

void de_string_builder(s_string_builder* this){
    if(this == NULL) crash("de_string_builder() was called with a NULL s_string_builder");

    this->memory_size = 0;
    this->length = 0;
    cleanup(V &this->characters);
    cleanup(V &this);
}

const char* make_string(s_string_builder* this){
    if(this == NULL) crash("make_string() was called with a NULL s_string_builder");

    add_character(this, 0);
    char* str = malloc(this->length);
    memcpy(str, this->characters, this->length);

    de_string_builder(this);
    return str;
}