#include "../headers/util.h"

char* read_line(FILE* file){
    char* line = NULL;
    size_t buffer = 0;

    if(getline(&line, &buffer, file)) fcrash("read_line() called with no newline");

    return line;
}

void cleanup(void** obj){
    if(obj == NULL) crash("cleanup() called with NULL object");

    void* p = *obj;
    free(p);
    *obj = NULL;
}

void cleanup_array(void** array){
    if(array == NULL) crash("cleanup_array() called with NULL array");

    int index = 0;
    void* current = array[index];

    while(current != NULL){
        cleanup(&current);
        index += 1;
        current = array[index];
    }
}

void* expand_memory(void* current_memory, size_t size){
    if(size < 0) crash("expand_memory() called with negative size");

    void* temp = realloc(current_memory, size);
    if(!temp) crash("Failed to expand memory");
    return temp;
}

void swap_pointers(void** ptr1, void** ptr2){
    if(ptr1 == NULL) crash("swap_pointers() called with NULL ptr1");
    if(ptr2 == NULL) crash("swap_pointers() called with NULL ptr2");

    void* temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

bool are_equal(const char* str1, const char* str2){
    return (strcmp(str1, str2) == 0);
}

_Noreturn void crash(char* message){
    error(message);
    exit(EXIT_FAILURE);
}

_Noreturn void fcrash(char* message){
    fatal(message);
    exit(EXIT_FAILURE);
}

void warn(char* message){
    fprintf(stderr, "%s[%s]:%s %s %s", BOLD_YELLOW, TAG, YELLOW, message, NEWLINE);
}

void error(char* message){
    fprintf(stderr, "%s[%s]:%s %s %s", BOLD_RED, TAG, DEFAULT_COLOR, message, NEWLINE);
}

void fatal(char* message){
    fprintf(stderr, "%s[%s]:%s %s: %s %s", BOLD_RED, TAG, DEFAULT_COLOR, message, strerror(STDERR_FILENO), NEWLINE);
}

void prompt(char* directory){
    if(directory == NULL) crash("prompt() called with NULL directory");
    printf("%s%s%s %s %s> %s", BOLD_CYAN, TAG, BLUE, directory, BOLD_CYAN, DEFAULT_COLOR);
}