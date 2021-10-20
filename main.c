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
    char envpaths[200];
    strcpy(envpaths,getenv("PATH"));    //guardo en envpaths los paths de la env PATH para poder trabajarla
    int nropaths = separador(envpaths,pathargs,MAXCMD,":"); //guardo en pathargs los paths por separado de la env PATH
    int bgflag;

    
    init_shell();
    if(argc < 2){   //si llamo a myshell sin argumentos ./myshell,se espera comandos por consola

        while(1){
            bgflag=0;               //reinicio la flag de background
            printDir();
            if(takeInput(inputString)){         //guardare en inputString lo que ingrese por consola
                continue;               //entrada vacia, espero comandos devuelta(al hacer enter sin nada)
            }
            if(inputprocess(inputString,args,&bgflag)){         //Procesa y divide el input. Intenta ejecutar comandos internos. Modifica la bgflag en caso de que haya un & al final del comando Devuelve 1 si no econtro comando interno
                execSys(pathargs,args,nropaths,bgflag);   //Trato de ejecutar comandos externos mediante execv
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
            sleep(1);                                       //sleep para poder ver en consola como se van ejecutando los comandos
            if(inputprocess(inputString,args,&bgflag)){
                
                execSys(pathargs,args,nropaths,bgflag);  //
            }
        }
        fclose(fptr);
        return 0;

    }
}

