#ifndef DSHELL_PARSER_H
#define DSHELL_PARSER_H

#include "pch.h"
#include "util.h"
#include "command.h"

/**
 * Search through the array for a specified type.\n
 *
 * Will loop through array and call apply_children()
 * on any command found with a type that matches the
 * specified type.
 *
 * @param commands - an array of commands to loop through
 * @param type - the COMMAND_TYPE to search for
 */
void parse_type(s_command** commands, COMMAND_TYPE type);

/**
 * Shifts all elements to the left by amount.\n
 *
 * Loops through array until NULL is found, swapping the pointers
 * of every n (where n is amount) elements.
 *
 * @param commands - an array of commands to loop through
 * @param amount - by how much distance in front of the current element to swap
 */
void shift_to_left(s_command** commands, int amount);

/**
 * Assigns children to a command.\n
 *
 * The elements left and right of the command are set to their respective
 * pointer under the command at index. The array is then shifted back twice
 * so that there are no gaps.
 *
 * @param commands - an array of commands to utilize
 * @param index - the position of the command to pivot from
 */
void apply_children(s_command** commands, int index);

/**
 * Recursively fully processes all subshells.\n
 *
 * Will loop through commands and collect elements along the way,
 * calling parse() with the final product. As such, any children of
 * subshells will be fully parsed in "one" pass.
 *
 * @param commands - an array of commands to loop through
 * @return the index of a SUBSHELL_END, or -1 if not found
 */
int condense_subshells(s_command** commands);

/**
 * Assigns all remaining elements as left children to one another.\n
 *
 * As such, a left over: 1->2 will become a tree where 2 is the left child of 1.
 * This is relevant for procedural commands, that should just be processed as is.
 *
 * @param commands - an array of commands to loop through
 */
void parse_leftovers(s_command** commands);

/**
 * Organizes an array of commands into a single tree.\n
 *
 * This is under the guise that execution flow follows
 * an Pre-Order Traversal via Depth-First Search.
 *
 * @param commands - an array of commands to process
 * @return pointer to a tree of s_command
 */
s_command* parse(s_command** commands);

#endif //DSHELL_PARSER_H
