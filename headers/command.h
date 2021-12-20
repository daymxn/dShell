#ifndef DSHELL_COMMAND_H
#define DSHELL_COMMAND_H

#include "pch.h"
#include "string_builder.h"

/**
 * Various types that a command can be.\n
 *
 * COMMAND is the default, STRING is reserved for
 * string literals, and the rest are special shell keywords.
 */
typedef enum {
    COMMAND = 0,
    STRING = 1,
    ENDCOMMAND = 2,
    PIPE = 3,
    SUBSHELL = 4,
    SUBSHELL_START = 5,
    SUBSHELL_END = 6,
    NOT = 7,
    AND = 8,
    OR = 9,
    REDIRECT_TO = 10,
    REDIRECT_TO_OVERWRITE = 11
} COMMAND_TYPE;

/**
 * Container for commands.\n
 *
 * Provides helper methods for easy management
 * during command creation and post-creation.
 *
 * @property type - enum representation of the command category
 * @property argument_length - the amount of arguments added so far
 * @property memory_size - how large of a memory footprint the arguments take up
 * @property left - the left command node relative to this command
 * @property right - the right command node relative to this command
 * @property arguments - array of strings corresponding to the command arguments, with
 * arguments[0] being the command word
 */
typedef struct{
    COMMAND_TYPE type;
    int argument_length;
    int memory_size;
    void* left;
    void* right;
    const char** arguments;
}s_command;

/**
 * Initializes s_command.\n
 *
 * Sets everything to 0 and NULL, except the type. The type
 * defaults to COMMAND.
 *
 * @return pointer to a new s_command
 */
s_command* command();

/**
 * Destructor for a s_command.\n
 *
 * Calls cleanup() on all properties, and sets integer values to 0.
 *
 * @param this the s_command to use
 */
void de_command(s_command* this);

/**
 * Appends an argument to the end of a s_command.\n
 *
 * Automatically reallocates space, increases the length by one,
 * updates the memory_size, and will update the old ptr if the
 * address moves.\n
 *
 * Note that the argument is directly assigned to the command,
 * and is not copied to a new segment.
 *
 * @param this the s_command to use
 * @param argument the string to add
 */
void add_argument(s_command* this, const char* argument);

#endif //DSHELL_COMMAND_H
