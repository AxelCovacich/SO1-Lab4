#include "utils.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>


#define MAXCHAR 1000 // max number of letters to be supported
#define MAXCMD 100  // max number of commands

const int MAX_SIZE = 256;


// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

int inputprocess(char* input, char** parsed);
void parseSpace(char *input,char **parsed);
int commandHandler(char **parsed);
  
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
    printf("\n\n\n\n******************"
        "************************");
    printf("\n\n\n\t****MY SHELL****");
    printf("\n\n\t-AXEL COVACICH SHELLS-");
    printf("\n\n\n\n*******************"
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

int inputprocess(char* input, char** parsed){

    parseSpace(input, parsed);

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
  
    for (i = 0; i < nrocommands; i++) {
        if (strcmp(parsed[0], Listadecomandos[i]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }
  
    switch (switchOwnArg) {
    case 1:
        printf("\nExiting...\n");
        exit(0);
    case 2:
        //chdir(parsed[1]);
        printf("cuestionando cd");
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
  
    return 0;
}

// function for parsing command words
void parseSpace(char* str, char** parsed)
{
    int i;
  
    for (i = 0; i < MAXCMD; i++) {
        parsed[i] = strsep(&str, " ");
  
        if (parsed[i] == NULL)
            break;
        if (strlen(parsed[i]) == 0)
            i--;
    }
}