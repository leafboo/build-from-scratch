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

    // getline() function also includes the newline character \n...so we need to remove that
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
    unsigned int position = 1; // this can never be negative

    allocate_memory_for_double_pointer(&tokens, bufsize);

    size_t num_characters = strlen(line);

    token = strtok(line, " "); // NOTE: this modifies the original string buffer and replaces the delimiter with NULL terminating characters (\0)
    tokens[0] = token;

    while (token != NULL) {
	if (position >= num_characters) {
	    reallocate_memory(&tokens);
	}

	token = strtok(NULL, " ");

	tokens[position] = token;
	position++;
	// TODO: check position here idk. And execute the realloc function whenever the buffer's size doesn't fit the stdin chars
    }
    tokens[position] = NULL;

    return tokens;
}

void execute_command(char **args) {
    // in this function, we need to replace the current process(our program), with the process/command entered by the user
    if (args[0] == NULL) {
	return;
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

int help() {
    printf("Welcome to my_shell!\n");
    printf("These are the current shell builtins we have:\n");
    printf("help - displays help page\n");
    printf("exit - exit the shell program\n");
    printf("cd - change directory\n");
    printf("banner - prints the welcome banner\n");
    return 1;
}
int exit_shell() {
    return 0;
}
int change_directory(char **args) {
    if (args[1] == NULL) {
	printf("there is no path provided.");
    } else {
	if (chdir(args[1]) != 0) {
	    perror("cd");
	}
    }

    return 1;
}
int print_banner() {
    print_welcome_banner();
    return 1;
}

char *shell_builtins_str[] = {
    "help",
    "exit",
    "cd",
    "banner",
};

int (*shell_builtins[])(char **) = {
    &help,
    &exit_shell,
    &change_directory,
    &print_banner
};

int some_function(char **args) {
    size_t num_builtins = sizeof(shell_builtins) / sizeof(int *);
    for (unsigned int i = 0; i < num_builtins; i++) {
	if (strcmp(args[0], shell_builtins_str[i]) == 0) {
	    return shell_builtins[i](args);
	}   
    }

    execute_command(args);

    return 1;
}

// void print_args(char **args) { // I only need the value here so pass by value is fine
//     int address_index = 0, value_index = 0;
//
//     while (args[address_index] != NULL) {
// 	// loop through each `address_index` and loop through each `value_index` and print the values in the value_index
// 	while (args[address_index][value_index] != '\0')	{
// 	    printf("%c", args[address_index][value_index]);
// 	    value_index++;
// 	}
// 	printf("\n");
// 	value_index = 0;
// 	address_index++;
//     }
//
// }


char *get_cwd(void) {
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

	status = some_function(args);

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
