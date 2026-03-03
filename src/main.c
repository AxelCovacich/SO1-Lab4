#include "utils.h"
#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

  
int main(int argc, char **argv)
{
    char *pathargs[MAXCMD];
    char inputString[MAXCHAR];
    char *args[MAXCMD];
    char *pipedargs[MAXCMD];
    char *stdfilename[2];
    char envpaths[200];
    strcpy(envpaths,getenv("PATH"));    //guardo en envpaths los paths de la env PATH para poder trabajarla
    int nropaths = separador(envpaths,pathargs,MAXCMD,":"); //guardo en pathargs los paths por separado de la env PATH
    int pipecommands;
    init_shell();

    /*
        Ignoramos en el proceso padre las señales especificadas.
        Las señales ignoradas son aquellas que deberán ser atendidas
        sólo por los child processes en foreground execution.
    */
    signal(SIGINT,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    signal(SIGQUIT,SIG_IGN);

    if(argc < 2){   //si llamo a myshell sin argumentos ./myshell,se espera comandos por consola

        while(1){
            bgflag = 0;               //reinicio las flags
            stdinflag = 0;
            stdoutflag = 0;
            printDir();
            if(takeInput(inputString)){         //guardare en inputString lo que ingrese por consola
                continue;               //entrada vacia, espero comandos devuelta(al hacer enter sin nada)
            }

            //Procesa y divide el input. Intenta ejecutar comandos internos. Modifica las flags correspondientes.
            //Devuelve 1 si no econtro comando interno
            pipecommands = inputprocess(inputString,args,pipedargs,stdfilename);

            if(pipecommands == 1){
                execSys(pathargs,args,nropaths,stdfilename);   //Trato de ejecutar comandos externos mediante execv
            }
            else if(pipecommands > 1){  //se ejecutaran comandos con pipe
                executePipedCommands(pathargs,pipedargs, pipecommands,stdfilename);
            }
        }
        return 0;
    }

    else{
        printf("Leyendo comandos\n");
        FILE *fptr = abrirfile(argv[1]);
        while(fgets(inputString,500,fptr)!= NULL){ 
            bgflag = 0;               //reinicio las flags
            stdinflag = 0;
            stdoutflag = 0;
            printDir(); 
            printf(":$ %s\n",inputString);
            sleep(1);                                       //sleep para poder ver en consola como se van ejecutando los comandos
            if(inputprocess(inputString,args,pipedargs,stdfilename)){
                
                execSys(pathargs,args,nropaths,stdfilename);  //
            }
        }
        if(stdinflag){
            restaurarSTD(STDIN_FILENO);
            free(stdfilename[0]);
        }

        if(stdoutflag){
            restaurarSTD(STDOUT_FILENO);
            free(stdfilename[1]);
        }

        fclose(fptr);
        return 0;
    }
}

