#ifndef DSHELL_UTIL_H
#define DSHELL_UTIL_H

#include "pch.h"

/**
 * We avoid functional macros. #NoSideEffectGang
 */
#define BOLD_RED "\033[1;31m"
#define DEFAULT_COLOR "\033[0m"
#define BOLD_CYAN "\033[1;36m"
#define BLUE "\033[0;34m"
#define TAG "dShell"
#define NEWLINE "\n"

/**
 * Frees up a pointer and sets it to NULL.\n
 *
 * Setting pointers to NULL after freeing them helps facilitate
 * a more error-trackable environment. As such, this method helps
 * retain a single line clean-up call- while also maintaining error-trackable
 * code.
 *
 * @example
 * char* str = getchar();\n
 * cleanup((void**) &str);
 *
 * @param obj a pointer to the memory segment to expand.
 */
void cleanup(void** obj);

/**
 * Free an array of pointers and set them to NULL.\n
 *
 * Internally, this just looks through an array of pointers until NULL,
 * and calls cleanup() on each index.
 *
 * @see cleanup
 * @param array - array of pointers to clean up.
 */
void cleanup_array(void** array);

/**
 * Will resize a memory region to size.\n
 *
 * Handles the calls to realloc, and error checking.
 *
 * @param current_memory - a pointer to the memory segment to expand
 * @param size - the TOTAL size of the new memory
 * @return the new pointer
 */
void* expand_memory(void* current_memory, size_t size);

/**
 * Prints the contents of perror to stderr, with a message and TAG appended.\n
 *
 * Primarily utilized for logging syscall related errors at runtime.
 *
 * @param message - an additional message describing the issue.
 */
void fatal(char* message);

/**
 * Attaches a TAG and color formatting to message, and logs it to stderr.\n
 *
 * Primarily utilized for general logging of errors, unrelated to a syscall.
 *
 * @param message - a message describing the issue.
 */
void error(char* message);


/**
 * Crashes program, pushing a message to stderr.\n
 *
 * Internally this just calls error() and exit().\n
 *
 * Utilized for general-case crashing.
 *
 * @param message a message describing the issue.
 */
_Noreturn void crash(char* message);

/**
 * Crashes program, pushing a message AND errno to stderr.\n
 *
 * Internally this just calls fatal() and exit().\n
 *
 * Utilized for crashing relevant to syscalls, where perror is needed.
 *
 * @param message an additional message describing the issue.
 */
_Noreturn void fcrash(char* message);

/**
 * Attaches a TAG and formatting to directory, and logs it to stdout.\n
 *
 * For logging a CLI signature before capturing input.
 * @param directory - the CWD
 */
void prompt(char* directory); //prob move to lifecycle or some shit

/**
 * Swaps the values of two pointers. \n
 *
 * Primarily utilized for swapping two pointers, by providing the address
 * of the given pointers.\n
 *
 * @example
 * char* ptr1;\n
 * char* ptr2;\n
 * swap_pointers(&ptr1, &ptr2);
 *
 * @param ptr1 - the first pointer to swap
 * @param ptr2 - the second pointer to swap
 */
void swap_pointers(void** ptr1, void** ptr2);

/**
 * Compares if two strings are equal.\n
 *
 * Behind the scenes, this just calls strcmp, as to avoid comparing the result of strcmp to 0.\n
 *
 * @param str1 - the first string to compare
 * @param str2 - the second string to compare
 */
bool are_equal(const char* str1, const char* str2);

/**
 * Reads from file until a NEWLINE is found, and returns the result as a string.\n
 *
 * Internally, this just calls getline() and handles the error checking;
 *
 * @param file - the file descriptor to read from.
 * @return string - a representation of the input as a char*.
 */
char* read_line(FILE* file);

#endif //DSHELL_UTIL_H
