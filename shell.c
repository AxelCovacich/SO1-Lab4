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
#define clear() printf("\033[3J\033c");


// Greeting shell during startup
void init_shell()
{
    //clear();
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

    if((strcmp(Listadecomandos[1],parsed[0]) == 0)&& (parsed[1]==NULL)){       //salvando errores de crasheo cuando uso echo y cd sin argumentos
        parsed[1]="";
    }
   /* if(parsed[1]==NULL){
        parsed[1]="";
    }*/
    
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
            if(setenv("OLDPWD",getenv("PWD"),1)!=0){
                perror("Error al setear OLDPWD");
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
        if(setenv("OLDPWD",getenv("PWD"),1)!=0){
            perror("Error al setear OLDPWD");
            return 1;
        }
        if(setenv("PWD",getcwd(NULL,0),1)!=0){
            perror("Error al setear PWD");
            return 1;
        }

        return 1;
    case 3:
        while(parsed[n]!=NULL){
            if((strchr(parsed[n], '$') != NULL) ){
                memmove(parsed[n], parsed[n]+1, strlen(parsed[n]));
                printf(" %s",getenv(parsed[n]));
                n++;
                continue;
            }
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

void execSys(char **pathargs,char** parsed,int nropaths)
{
    printf("entro a copiarparsed0: %s\n",parsed[0]);
    char path[100];
    char *args[MAXCMD]={'\0'};
    

    printf("nro de paths: %d\n",nropaths);
    //strcpy(aux,parsed[0]); 
    //printf("aux: %s \n",aux);
    int n=0,flag=0;
    printf("voy a parsear\n");

    while(parsed[n+1]!=NULL){
        args[n]=parsed[n+1];
        n++;
    }
    int j=0;
    while(args[j]!=NULL){
        printf("argsj: %s ; \n",args[j]);
        j++;
    }
    //args[i+1]=NULL;
    printf("voy a forkear con n args0 y args 1: %d; %s ; %s\n",n,args[0],args[1]);
    // Forking a child

    pid_t pid = fork(); 

    if (pid == -1) {
        printf("\nFailed forking child..");
        return;
    }
     else if (pid == 0) {                       //soy el hijo

        if(strstr(parsed[0],"./")!=NULL){
            //relativo, tiene ./
            strcpy(path,getenv("PWD"));
            strcat(path,"/");
            strcat(path,parsed[0]);
            printf("path tiene: %s\n",path);
            if (execv(path, parsed) < 0) {
                perror("\nCould not execute command:");
            }
        }

        else{ 
            if(strchr(parsed[0],'/')!=NULL){
                strcpy(path,parsed[0]);
                if (execv(path, parsed) < 0) {
                    perror("\nCould not execute command:");
                }
            }
            else{
                for(int i=0; i<nropaths; i++){
                    strcpy(path,pathargs[i]);
                    strcat(path,"/");
                    strcat(path,parsed[0]);
                    flag=execv(path,parsed);
                }
                if(flag < 0)
                perror("\nCould not execute command:");
            }
        }
    
    exit(0);
    }
    else {
        // waiting for child to terminate
        wait(NULL); 
        return;
    }
}