#include <stdio.h>
#ifndef shell    /* This is an "include guard" */
#define shell    /* prevents the file from being included twice. */
                     /* Including a header file twice causes all kinds */
                     /* of interesting problems.*/

/**
 * This is a function declaration.
 * It tells the compiler that the function exists somewhere.
 */
#define MAXCHAR 1000 // max number of letters to be supported
#define MAXCMD 100  // max number of commands

void init_shell();
int takeInput(char* str);
int commandHandler(char **parsed);
int inputprocess(char* input, char** parsed,int *flag);
void execSys(char** pathargs,char** parsed,int nropaths,int bgflag);

#endif