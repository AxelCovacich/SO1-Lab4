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


const int MAX_SIZE = 256;


// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")


// Greeting shell during startup
void init_shell()
{
    clear();
    puts(
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n"
"▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n"
"▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒\n"
"▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒\n"
"▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒\n"
"▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▄░░▒▒▒▒▒\n"
"▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██▌░░▒▒▒▒\n"
"▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░▄▄███▀░░░░▒▒▒\n"
"▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░░█████░▄█░░░░▒▒\n"
"▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░▄████████▀░░░░▒▒\n"
"▒▒░░░░░░░░░░░░░░░░░░░░░░░░▄█████████░░░░░░░▒\n"
"▒░░░░░░░░░░░░░░░░░░░░░░░░░░▄███████▌░░░░░░░▒\n"
"▒░░░░░░░░░░░░░░░░░░░░░░░░▄█████████░░░░░░░░▒\n"
"▒░░░░░░░░░░░░░░░░░░░░░▄███████████▌░░░░░░░░▒\n"
"▒░░░░░░░░░░░░░░░▄▄▄▄██████████████▌░░░░░░░░▒\n"
"▒░░░░░░░░░░░▄▄███████████████████▌░░░░░░░░░▒\n"
"▒░░░░░░░░░▄██████████████████████▌░░░░░░░░░▒\n"
"▒░░░░░░░░████████████████████████░░░░░░░░░░▒\n"
"▒█░░░░░▐██████████▌░▀▀███████████░░░░░░░░░░▒\n"
"▐██░░░▄██████████▌░░░░░░░░░▀██▐█▌░░░░░░░░░▒▒\n"
"▒██████░█████████░░░░░░░░░░░▐█▐█▌░░░░░░░░░▒▒\n"
"▒▒▀▀▀▀░░░██████▀░░░░░░░░░░░░▐█▐█▌░░░░░░░░▒▒▒\n"
"▒▒▒▒▒░░░░▐█████▌░░░░░░░░░░░░▐█▐█▌░░░░░░░▒▒▒▒\n"
"▒▒▒▒▒▒░░░░███▀██░░░░░░░░░░░░░█░█▌░░░░░░▒▒▒▒▒\n"
"▒▒▒▒▒▒▒▒░▐██░░░██░░░░░░░░▄▄████████▄▒▒▒▒▒▒▒▒\n"
"▒▒▒▒▒▒▒▒▒██▌░░░░█▄░░░░░░▄███████████████████\n"
"▒▒▒▒▒▒▒▒▒▐██▒▒░░░██▄▄███████████████████████\n"
"▒▒▒▒▒▒▒▒▒▒▐██▒▒▄████████████████████████████\n"
"▒▒▒▒▒▒▒▒▒▒▄▄████████████████████████████████\n"
"████████████████████████████████████████████\n"
    );
    printf("******************"
        "************************");
    printf("\n\n\n\t****MY SHELL****");
    printf("\n\n\t-AXEL COVACICH SHELL-");
    printf("\n\n*******************"
        "***********************");
    char* username = getenv("USER");

    char hostname[MAX_SIZE];
    int ret = gethostname(&hostname[0], MAX_SIZE);
    if (ret == -1) {
        perror("gethostname");
        exit(EXIT_FAILURE);
    }

    printf("\n\nHostname: %s\n", hostname);
    printf("\nUSER is: @%s", username);
    printf("\n");
    sleep(1);
    //clear();
}

int takeInput(char* str)
{
    char* buf;
  
    buf = readline(":$ ");
    if (strlen(buf) != 0) {
        //add_history(buf);
        strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
}

int inputprocess(char* input, char** parsed){

    parseSpace(input, parsed,MAXCMD);
    if(commandHandler(parsed)){
        return 0;
    }
    else
        return 1;
}

int commandHandler(char **parsed){
    int nrocommands = 4, i, switchOwnArg = 0,n=1;
    char* Listadecomandos[nrocommands];
  
    Listadecomandos[0] = "quit";
    Listadecomandos[1] = "cd";
    Listadecomandos[2] = "echo";
    Listadecomandos[3] = "clr";

    if((strcmp(Listadecomandos[2],parsed[0]) == 0)&& (parsed[1]==NULL)){       //salvando errores de crasheo cuando uso echo y cd sin argumentos
        return 1;
    }
    if(parsed[1]==NULL){
        parsed[1]="";
    }
    
    for (i = 0; i < nrocommands; i++) {
        if (strcmp(Listadecomandos[i],parsed[0]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }
    switch (switchOwnArg) {
    case 1:
        printf("\nExiting...\n");
        exit(0);
    case 2:
        if((strcmp(parsed[1],"-"))==0){
            printf("\nUltimo directorio: %s ",getenv("OLDPWD"));
            return 1;
        }
        if((strcmp(parsed[1],""))==0){
            if(chdir(getenv("HOME"))!=0){
            perror("Error al cambiar directorio");
            return 1;
            }
            if(setenv("PWD",getenv("HOME"),1)!=0){
            perror("Error al setear PWD");
            return 1;
            }
            return 1;
        }
        if(chdir(parsed[1])!=0){
            perror("Error al cambiar directorio");
            return 1;
        }
        if(setenv("PWD",parsed[1],1)!=0){
            perror("Error al setear PWD");
            return 1;
        }
        
        return 1;
    case 3:
        if((strchr(parsed[1], '$') != NULL) ){
            memmove(parsed[1], parsed[1]+1, strlen(parsed[1]));
            n=2;
            printf("%s",getenv(parsed[1]));
        }
        while(parsed[n]!=NULL){
            printf(" %s",parsed[n]);
            n++;
        }
        printf("\n");
        return 1;
    case 4:
        clear();
        return 1;
    default:
        break;
    }
  
    return 0;   //error, no se reconocio el comando
}
