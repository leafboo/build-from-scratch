#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void reallocate_memory(char ***buffer) { // we need to pass by reference(get the address of the pointer)
    *buffer = realloc(*buffer, 1024);

    if (*buffer == NULL) {
	// something went wrong here 
	perror("reallocate_memory");
	exit(EXIT_FAILURE);
    }
}

void allocate_memory_for_single_pointer(char **buffer, size_t bufsiz) { // should accept the address of a pointer that points to an address of allocated memory
    *buffer = malloc(bufsiz); 
    if (*buffer == NULL) {
	perror("read_line"); // will print the error message: `read_line: error message`
	exit(EXIT_FAILURE);
    }
}

void allocate_memory_for_double_pointer(char ***buffer, size_t bufsiz) {
    *buffer = malloc(bufsiz); // NOTE: we need to dereference the buffer so that it can access the ORIGINAL VALUE
    if (*buffer == NULL) {
	perror("read_line"); // will print the error message: `read_line: error message`
	exit(EXIT_FAILURE);
    }
}

void print_welcome_banner(void) {
    printf(" __          __  _                            _                                  _          _ _ \n");
    printf(" \\ \\        / / | |                          | |                                | |        | | |\n");
    printf("  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___  | |_ ___    _ __ ___  _   _     ___| |__   ___| | |\n");
    printf("   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\  | '_ ` _ \\| | | |   / __| '_ \\ / _ \\ | |\n");
    printf("    \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | | | | | | |_| |   \\__ \\ | | |  __/ | |\n");
    printf("     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/  |_| |_| |_|\\__, |   |___/_| |_|\\___|_|_|\n");
    printf("                                                                    __/ |_____                 \n");
    printf("                                                                   |___/______|                \n");
}
