#include <stdio.h>
#ifndef utils    /* This is an "include guard" */
#define utils    /* prevents the file from being included twice. */
                     /* Including a header file twice causes all kinds */
                     /* of interesting problems.*/

/**
 * This is a function declaration.
 * It tells the compiler that the function exists somewhere.
 */
FILE *abrirfile(char *nombre);
void printDir();
#endif