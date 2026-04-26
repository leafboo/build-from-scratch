#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../my_lib/include/buffer.h"

char *read_line() {
    // this function should return the line  
    char *buffer;
    size_t buffer_size = 1024;

    allocate_memory_for_single_pointer(&buffer, buffer_size); // REMINDER: when malloc is used, memory is stored in the heap, thus it will not get freed when the function stack ends

    // getline() function also includes the newline character \n...so remove that
    ssize_t getline_return_val = getline(&buffer, &buffer_size, stdin);
    if (getline_return_val == -1) { // if line exceeds the bufsize, it automatically allocates new memory with a bigger buffer size
	if (feof(stdin)) {
	    exit(EXIT_SUCCESS);
	}
	perror("read_line | getline func");
	exit(EXIT_FAILURE);
    } 
    buffer[getline_return_val - 1] = '\0';

    return buffer;
}

// this function splits strings of a line by args 
char **split_line(char *line) {
    char **tokens;
    char *token;
    size_t bufsize = 1024; 
    int position = 1;

    allocate_memory_for_double_pointer(&tokens, bufsize);

    // TODO: make a function to reallocate memory when buffer overflow occurs

    token = strtok(line, " "); // NOTE: this modifies the original string buffer and replaces the delimiter with NULL terminating characters (\0)
    tokens[0] = token;

    while (token != NULL) {
	token = strtok(NULL, " ");

	tokens[position] = token;
	position++;
    }
    tokens[position] = NULL;

    return tokens;
}

void execute_command(char **args) {
    // in this function, we need to replace the current process(our program), with the process/command entered by the user
    if (args[0] == NULL) {
	exit(EXIT_FAILURE);
    }

    pid_t pid = fork(), cpid;

    if (pid < 0) {
	// failed to create a new process
	perror("execute_command");
	exit(EXIT_SUCCESS);
    } else if (pid == 0) {
	// child process
	if (execvp(args[0], args) == -1) {
	    perror("execute_command");
	    exit(EXIT_SUCCESS);
	}
    } else {
	// the parent process
	cpid = wait(NULL);
    }
}

void print_args(char **args) { // I only need the value here so pass by value is fine
    int address_index = 0, value_index = 0;

    while (args[address_index] != NULL) {
	// loop through each `address_index` and loop through each `value_index` and print the values in the value_index
	while (args[address_index][value_index] != '\0')	{
	    printf("%c", args[address_index][value_index]);
	    value_index++;
	}
	printf("\n");
	value_index = 0;
	address_index++;
    }

}

char *get_cwd(void) {
    printf("get_cwd function entered");
    char *cwd;
    allocate_memory_for_single_pointer(&cwd, 1024);

    // freeing a NULL pointer returned by a failed malloc is fine but idk I just felt like doing this 
    if (getcwd(cwd, 1024) == NULL && cwd != NULL) {
	free(cwd);
	cwd = NULL;
    }

    return cwd;
}

int main_loop(void) {
    int status = 1;
    char *line, *cwd = get_cwd();
    char **args;

    print_welcome_banner();

    do {
	printf("%s> ", cwd);
	line = read_line();
	args = split_line(line);

	execute_command(args);

	status = 0;

    } while (status);

    // return pointers here
    free(line);
    free(args);
    
    return status;
}

int main(int argc, char *argv[]) {

    main_loop();

    return EXIT_SUCCESS;
}


// PROJECT PLAN
// Accept user inputs 
// Our program: 
// 	loop until the user exits
// 		parse the args commands
// 		runs the command in a new child process
// 		kill child process
// 	repeat
