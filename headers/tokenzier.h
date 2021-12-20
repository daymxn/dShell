#ifndef DSHELL_TOKENZIER_H
#define DSHELL_TOKENZIER_H

#include "command.h"

/**
 * State container for token collection.\n
 *
 * Breaks up a string into commands, or "tokens".\n
 * See command_type for more info.
 *
 * @property tokens - an array of completed commands
 * @property token_length - the amount of commands collected so far
 * @property current_command - the command being constructed currently
 * @property current_builder - the string being constructed currently
 * @property index - the current position of the tokenizer in processing of line
 * @property memory_size - how large of a memory footprint tokens takes up
 * @property line - the string to process
 *
 * @see token_state()
 */
typedef struct{
    s_command** tokens;
    int token_length;
    s_command* current_command;
    s_string_builder* current_builder;
    int index;
    int memory_size;
    const char* line;
}s_token_state;

/**
 * Initializes s_token_state.\n
 *
 * Initializes current_command and current_builder,
 * with the rest being set to NULL and 0.
 *
 * @return pointer to a new s_token_state
 */
s_token_state* token_state();

/**
 * Destructor for a s_token_state.\n
 *
 * Calls cleanup() on all properties, and sets integer values to 0.
 *
 * @param this - the s_token_state to use
 */
void de_token_state(s_token_state* this);

/**
 * Appends the current_command to tokens.\n
 *
 * Handles all the memory management, and will also set
 * current_command to a newly initialized command.
 *
 * @param this - the s_token_state to use
 */
void add_current_to_tokens(s_token_state* this);

/**
 * Appends the current_command to tokens.\n
 *
 * Handles all the memory management, and will also set
 * current_command to a newly initialized command.
 *
 * @param this - the s_token_state to use
 */
void append_special(s_token_state* this, char character);

/**
 * Appends a character to the end of current_builder.\n
 *
 * Basically just a call to add_character() on the builder,
 * but makes for idiomatic code alongside append_special().
 *
 * @param this - the s_token_state to use
 * @param character - the char to add
 */
void append_character(s_token_state* this, char character);

/**
 * Converts the token_state_complete to a s_command** and returns it.\n
 *
 * Please note, that this method will automatically cleanup itself.
 * Internally, this method is very similar to the token_state
 * destructor. The only difference is that tokens is NOT copied
 * to a new memory segment, and is returned instead.\n
 *
 * This method DOES add a null terminator to the end of tokens.
 *
 * @param this - the s_token_state to use
 *
 * @return pointer to tokens
 */
s_command** token_state_complete(s_token_state* this);

/**
 * Checks if the next character in line is a certain character.\n
 *
 * Useful for validating multi-character symbols without moving
 * the index.
 *
 * @param this - the s_token_state to use
 * @param character - the char to check for
 * @return bool where true means character equals next character
 */
bool next_character_is(s_token_state* this, char character);

/**
 * Checks if a character matches predefined symbols.\n
 *
 * Special symbols are either treated differently, or
 * can affect the state in various ways.
 *
 * @param character - the character to validate against
 * @return bool where true means character is a special symbol
 */
bool is_character_special(char character);

/**
 * Appends the current_builder() string to current_command arguments.\n
 *
 * Will also reinitialize current_builder to a fresh builder.
 *
 * @param this - the s_token_state to use
 */
void finish_builder(s_token_state* this);

/**
 * Break up a string into s_command "tokens".\n
 *
 * The output will just be an array of the tokens,
 * and none of tokens will have children setup yet.
 *
 * @param line - a string of characters to process
 * @return pointer to an array of sorted s_command
 */
s_command** tokenizer(const char* line);

#endif //DSHELL_TOKENZIER_H
