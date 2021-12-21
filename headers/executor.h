#ifndef DSHELL_EXECUTOR_H
#define DSHELL_EXECUTOR_H

#include <sys/wait.h>
#include "command.h"
#include "internal.h"

/**
 * Recursively executes commands and returns the result.\n
 *
 * Will execute in Pre-Order Traversal form of
 * Depth First Search. Diversifies command based
 * on the COMMAND_TYPE. Complex commands get handed
 * off to execute_special(), while simple commands
 * get handed off to execute_command().
 *
 * @param command - the current command to execute
 * @return the exit code of the applications
 */
EXIT_STATUS execute(s_command* command);

/**
 * Handles executing of simple commands.\n
 *
 * Will execute in Pre-Order Traversal form of
 * Depth First Search.
 *
 * @param command - the current command to execute
 * @return the exit code of the application
 */
EXIT_STATUS execute_command(s_command* command);

/**
 * Handles special symbol commands.\n
 *
 * If the implementation is more complex than
 * a few lines, the method should call to a helper
 * method for the symbol.
 *
 * @param command - the current symbol to process
 * @return the exit code of the following applications
 */
EXIT_STATUS execute_special(s_command* command);

/**
 * Handles pipe symbols.\n
 *
 * Will redirect stdout/stdin as needed, while
 * also maintaining a reference of old stdout/stdin
 * values to restore at the end.
 *
 * @param command - the current symbol to process
 * @return the exit code of the following applications
 */
EXIT_STATUS handle_pipe(s_command* command);

/**
 * Handles redirect_to and redirect_to_overwrite symbols.\n
 *
 * Will redirect stdout/stdin as needed, while
 * also maintaining a reference of old stdout/stdin
 * values to restore at the end. If a subshell is found,
 * the result of the subshell will be the consumer (or provider).
 *
 * @param command - the current symbol to process
 * @param overwrite - whether to overwrite the file or not
 * @return the exit code of the following applications
 */
EXIT_STATUS handle_redirect_to(s_command* command, bool overwrite);

/**
 * Handles subshell symbols.\n
 *
 * Will spawn a fork and wait for the exit status of the child.
 *
 * @param command - the current symbol to process
 * @return the exit code of the following applications
 */
EXIT_STATUS handle_subshell(s_command* command);

/**
 * Launches the command.\n
 *
 * Also checks if the command is a builtin before forking.
 *
 * @param command - the current command to execute
 * @return the exit code of the application
 */
EXIT_STATUS launch(s_command* command);


#endif //DSHELL_EXECUTOR_H
