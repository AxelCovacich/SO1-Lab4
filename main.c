#include "utils.h"
#include "shell.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

  
int main()
{
    char inputString[MAXCHAR];
    char *args[MAXCMD];
    init_shell();
    while(1){
        printDir();
        if(takeInput(inputString)){
            continue;               //vacio
        }
        printf("Input: %s \n",inputString);
        if(inputprocess(inputString,args)){
            printf("Error, comando desconocido\n");
            continue;
        }
    }
    return 0;
}



