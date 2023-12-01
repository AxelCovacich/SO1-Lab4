#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


#ifndef utils    /* This is an "include guard" */
#define utils    /* prevents the file from being included twice. */
                     /* Including a header file twice causes all kinds */
                     /* of interesting problems.*/

int original_stdin, original_stdout;

/**
 * This is a function declaration.
 * It tells the compiler that the function exists somewhere.
 */
FILE *abrirfile(char *nombre);
void printDir();
int separador(char *input,char **parsed,int LIMIT,char *delimitador);
char *chop_to_char(char *str, char *target);
void redirectSTDIN(char* filename);
void redirectSTDOUT(char* filename);
void restaurarSTD(int stdfile);




#endif