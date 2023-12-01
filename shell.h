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

int bgflag,stdinflag,stdoutflag;

void init_shell();
int takeInput(char* str);
int commandHandler(char** parsed,char** stdfilename);
int inputprocess(char* input, char** parsed,char** parsedpipes,char** stdfilename);
void execSys(char** pathargs,char** parsed,int nropaths,char** stdfilename);
void executePipedCommands(char** pathargs,char** pipedargs,int pipecommands,char** stdfilename);
void handler(int sig);
void Zcleaner();

#endif