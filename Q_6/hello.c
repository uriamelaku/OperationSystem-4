/*
* File: hello.c
*/
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]) {
char *string, *string_so_far;
int i, length; length = 0;
for(i=0; i<argc; i++) {
length += strlen(argv[i])+1;
string = malloc(length+1);
/* * Copy the string built so far. */
if(string_so_far != (char *)0)
strcpy(string, string_so_far);
else *string = '\0';
strcat(string, argv[i]);
if(i < argc-1) strcat(string, " ");
string_so_far = string;
}
printf("You entered: %s\n", string_so_far);
return (0);
}

// gcc -g -o hello hello.c
// valgrind --vgdb=yes --vgdb-error=0 ./hello arg1 arg2 arg3 > valgrind_output.txt 2>&1

// other terminal:

// gdb ./hello
// target remote | vgdb
