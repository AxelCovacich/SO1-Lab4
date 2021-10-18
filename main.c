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

  
int main(int argc, char **argv)
{
    char *pathargs[MAXCMD];
    char inputString[MAXCHAR];
    char *args[MAXCMD];
    int bgflag;
    int nropaths = separador(getenv("PATH"),pathargs,MAXCMD,":");
    
    init_shell();
    if(argc < 2){   //si llamo a myshell sin argumentos ./myshell, espero comandos por consola

        while(1){
            bgflag=0;
            printDir();
            if(takeInput(inputString)){
                continue;               //entrada vacia, espero comandos devuelta(al hacer enter sin nada)
            }
            if(inputprocess(inputString,args,&bgflag)){         //devuelve 1 si no econtro comando interno
                execSys(pathargs,args,nropaths,bgflag);   //
                //printf("Error, comando desconocido");

            }
        }
        return 0;
    }

    else{
        printf("Leyendo comandos\n");
        FILE *fptr = abrirfile(argv[1]);
        while(fgets(inputString,500,fptr)!= NULL){ 
            bgflag=0;
            printDir(); 
            printf(":$ %s\n",inputString);
            sleep(1);        
            if(inputprocess(inputString,args,&bgflag)){
                
                execSys(pathargs,args,nropaths,bgflag);  //
            }
        }
        fclose(fptr);
        return 0;

    }
}



