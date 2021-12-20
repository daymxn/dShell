#ifndef DSHELL_INTERNAL_H
#define DSHELL_INTERNAL_H

#include "pch.h"
#include "command.h"

/**
 * Functional type for builtins.\n
 *
 * Helps keep code clean.
 */
typedef EXIT_STATUS (builtin)(const char**);

/**
 * Change the current working directory.\n
 *
 * Performs a change of directory relative to
 * the current directory.
 *
 * @param args - a path query to utilize
 * @return the exit status code of the application
 */
EXIT_STATUS b_cd(const char** args);

/**
 * Prints a list of all builtins.\n
 *
 * @param args - currently not used, but will be in future
 * @return the exit status code of the application
 */
EXIT_STATUS b_help(const char** args);

/**
 * Exits the application with a status code of EXIT_SUCCESS.\n
 *
 * @param args - currently not used, but will be in future
 * @return the exit status code of the application
 */
EXIT_STATUS b_exit(const char** args);

/**
 * Returns builtin by string name.\n
 *
 * If no builtin is found that matches the string,
 * then NULL will be returned.
 *
 * @param name - the name of the builtin
 * @return a pointer to the builtin function
 */
builtin* get_builtin(const char* name);

#endif //DSHELL_INTERNAL_H
