# Note: when you execute the `make` command with no arguments, it executes the first rule in the file
# syntax:
# something: when the files that are put here changes, it signals make to execute the command at the bottom 
# of this line 

CC = gcc

all: clean buffer_lib shell

buffer_lib: my_lib/src/buffer.c
	$(CC) -c my_lib/src/buffer.c -o my_lib/build/buffer.o
	ar rcs my_lib/buffer.a my_lib/build/buffer.o
	

shell: src/main.c 
	$(CC) -c src/main.c -o src/build/main.o
	$(CC) -o shell src/build/main.o -Lmy_lib/ my_lib/buffer.a

clean: 
	find . -type f \
	\( -name "*.a" -o -name "*.o" -o -name "shell" \) -delete
