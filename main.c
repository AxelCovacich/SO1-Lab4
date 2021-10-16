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
    char *pathargs[MAXCMD];
    int nropaths = getbinpaths(pathargs,MAXCMD);
    for(int i=0; i<nropaths; i++){
        printf("Path i: %d - %s\n",i,pathargs[i]);
    }
    init_shell();
    while(1){
        printDir();
        if(takeInput(inputString)){
            continue;               //vacio
        }
        printf("Input: %s \n",inputString);
        if(inputprocess(inputString,args)){
            int n=0;
            while(args[n]!=NULL){
                printf("mainargsparaexec: %s \n",args[n]);
                n++;
            }
            printf("voy a exec \n");
            execSys(pathargs,args,nropaths);
            printf("Error, comando desconocido\n");
            continue;
        }
    }
    return 0;
}



