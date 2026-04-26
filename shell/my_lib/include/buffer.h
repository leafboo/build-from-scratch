#include <stddef.h>
// This function takes the address of a pointer that points to an allocated memory(buffer) in the heap and its size and allocates memory using malloc
void allocate_memory_for_single_pointer(char **buffer, size_t bufsiz);
void allocate_memory_for_double_pointer(char ***buffer, size_t bufsiz);
void print_welcome_banner(void);
