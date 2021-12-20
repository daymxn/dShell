#include "../headers/tokenzier.h"

s_token_state* token_state(){
    s_token_state* this = malloc(sizeof(s_token_state));
    this->tokens = NULL;
    this->token_length = 0;
    this->current_command = command();
    this->current_builder = string_builder();
    this->index = 0;
    this->memory_size = 0;
    this->line = NULL;

    return this;
}

void de_token_state(s_token_state* this){
    if(this == NULL) crash("de_token_state() was called with a NULL s_token_state");

    this->memory_size = 0;
    this->token_length = 0;
    this->index = 0;
    this->memory_size = 0;

    de_command(this->current_command);
    de_string_builder(this->current_builder);

    cleanup(V &this->current_command);
    cleanup(V &this->current_builder);
    cleanup(V &this);
}

void add_current_to_tokens(s_token_state* this){
    if(this == NULL) crash("add_current_to_tokens() was called with a NULL s_token_state");

    finish_builder(this);
    if(this->current_command->arguments == NULL && this->current_command->type == COMMAND) return;

    this->memory_size += sizeof(s_command*);
    this->tokens = expand_memory(this->tokens, this->memory_size);

    this->tokens[this->token_length] = this->current_command;
    this->token_length += 1;

    this->current_command = command();
}

void append_special(s_token_state* this, const char character){
    if(this == NULL) crash("append_special() was called with a NULL s_token_state");

    if(this->current_command->arguments != NULL || this->current_builder->length > 0) add_current_to_tokens(this);

    switch (character) {
        case '(':
            this->current_command->type = SUBSHELL_START;
            break;
        case ')':
            this->current_command->type = SUBSHELL_END;
            break;
        case ';':
            this->current_command->type = ENDCOMMAND;
            break;
        case '!':
            this->current_command->type = NOT;
            break;
        case '>':
            if(next_character_is(this, '>')){
                this->current_command->type = REDIRECT_TO;
                this->index+=1;
            }else{
                this->current_command->type = REDIRECT_TO_OVERWRITE;
            }
            break;
        case '&':
            if(next_character_is(this, '&')){
                this->current_command->type = AND;
                this->index+=1;
                break;
            } else crash("all ANDs must be followed my another AND, unless quoted");
        case '|':
            if(next_character_is(this, '|')){
                this->current_command->type = OR;
                this->index+=1;
                break;
            }
            this->current_command->type = PIPE;
            break;
        default:
            crash("append_special() was called with an invalid character.");
    }

    add_current_to_tokens(this);
}

void append_character(s_token_state* this, const char character){
    if(this == NULL) crash("append_character() was called with a NULL s_token_state");
    if(character == 0) crash("append_character() was called with a NULL character");

    add_character(this->current_builder, character);
}

s_command** token_state_complete(s_token_state* this){
    if(this == NULL) crash("token_state_complete() was called with a NULL s_token_state");

    this->memory_size += sizeof(s_command*);
    this->tokens = expand_memory(this->tokens, this->memory_size);
    this->tokens[this->token_length] = NULL;

    this->line = NULL;
    this->memory_size = 0;
    this->token_length = 0;
    this->index = 0;

    de_command(this->current_command); // might cause an issue?
    de_string_builder(this->current_builder);

    s_command** tokens = this->tokens;

    cleanup(V &this->current_command);
    cleanup(V &this->current_builder);
    cleanup(V &this);

    return tokens;
}

bool next_character_is(s_token_state* this, char character){
    if(this == NULL) crash("next_character_is() was called with a NULL s_token_state");
    if(character == 0) crash("next_character_is() was called with a NULL character");
    if(this->line == NULL) crash("next_character_is() was called with a NULL line");

    return this->line[this->index + 1] == character;
}

bool is_character_special(char character){
    switch (character) {
        case '(':
        case ')':
        case ';':
        case '!':
        case '>':
        case '&':
        case '|':
            return true;
        default:
            return false;
    }
}

void finish_builder(s_token_state* this){
    if(this == NULL) crash("finish_builder() was called with a NULL s_token_state");
    if(this->current_builder == NULL) crash("finish_builder() was called with a NULL current_builder");
    if(this->current_builder->length == 0) return;

    add_argument(this->current_command, make_string(this->current_builder));

    this->current_builder = string_builder();
}

s_command** tokenizer(const char* line){
    if(line == NULL) return NULL;

    s_token_state* state = token_state();
    state->line = line;
    bool QUOTED = false;

    char current_character = line[state->index];
    while(current_character){
        switch(current_character){
            case '"':
                QUOTED = !QUOTED;
                if(QUOTED && state->current_command->argument_length == 0 && state->current_builder->length == 0)
                    state->current_command->type = STRING;
                break;
            case '\n':
            case EOF:
                current_character = 0;
                add_current_to_tokens(state);
                continue;
            case ' ':
                finish_builder(state);
                break;
            default:
                if(!QUOTED && is_character_special(current_character)){
                    append_special(state, current_character);
                }else{
                    append_character(state, current_character);
                }
                break;
        }

        state->index += 1;
        current_character = line[state->index];
    }

    return token_state_complete(state);
}