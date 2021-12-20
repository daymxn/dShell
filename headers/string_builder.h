#ifndef DSHELL_STRING_BUILDER_H
#define DSHELL_STRING_BUILDER_H

#include "util.h"

/**
 * Implements a string builder type.\n
 *
 * Provides a length property, and helper
 * methods for ensuring proper memory
 * management and creation of strings.\n
 *
 * @property length - the amount of characters in the string
 * @property memory_size - how large of a memory footprint the string takes up
 * @property characters - the current string
 *
 * @see string_builder()
 */
typedef struct{
    int length;
    int memory_size;
    char* characters;
} s_string_builder;

/**
 * Initializes s_string_builder.\n
 *
 * Sets the initial length/memory_size to 0, and does not
 * allocate any initial space for characters.
 *
 * @return pointer to a new s_string_builder
 */
s_string_builder* string_builder();

/**
 * Destructor for a s_string_builder.\n
 *
 * Calls cleanup() on all properties, and sets integer values to 0.
 *
 * @param this the s_string_builder to use
 */
void de_string_builder(s_string_builder* this);

/**
 * Appends a character to the end of a s_string_builder.\n
 *
 * Automatically reallocates space, increases the length by one,
 * updates the memory_size, and will update the old ptr if the
 * address moves.
 *
 * @param this the s_string_builder to use
 * @param character the char to add
 */
void add_character(s_string_builder* this, char character);

/**
 * Converts the s_string_builder to a char* and returns it.\n
 *
 * Please note, that this method will automatically cleanup itself.
 * Internally, this method is very similar to the string_builder
 * destructor. The only difference is that characters is copied
 * to a new memory segment before being freed, and is returned.\n
 *
 * This method DOES add a null terminator to the end of the string.
 *
 * @param this the s_string_builder to use
 *
 * @return pointer to a new string
 */
const char* make_string(s_string_builder* this);

#endif //DSHELL_STRING_BUILDER_H
