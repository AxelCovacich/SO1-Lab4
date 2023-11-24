#include "utils.h"
#include "shell.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <ctype.h>



const int MAX_SIZE = 256;
int hijosbg=0;

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

int takeInput(char* str)        //funcion para leer entrada por teclado con la funcion readline
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

int inputprocess(char* input, char** parsed,char** parsedpipes,int *bgflag){
    int nropipes = separador(input,parsedpipes,MAXCMD,"|");
   // printf("Command pipeados %d\n",nropipes);
    //for (int j = 0; j < nropipes; j++) {
      //  printf("Command pipeado %d: %s\n", j + 1, parsedpipes[j]);
  //  }
    if(nropipes > 0){
        return nropipes;
    }
    int nrocmd = separador(input, parsed,MAXCMD," ");
    if(nrocmd==0){
        return 0;
    }
    if (strcmp(parsed[nrocmd-1], "&") == 0) {
        parsed[nrocmd-1] = NULL;
        *bgflag = 1;  // si el ultimo comando del string es & activo la flag de background
    }
    if(commandHandler(parsed)){     //retorna 1 si se encontro el comando interno y se trato de ejecutar
        return 0;
    }
    else if(nropipes == 0){
        return 1;
    }
        else{
            return 0;
        }                  
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
       if (parsed[0] == NULL) {
        // Empty command, do nothing
        return 0;
    }


    for (i = 0; i < nrocommands; i++) {
        if (strcmp(Listadecomandos[i],parsed[0]) == 0) {
            switchOwnArg = i + 1;
            break;
        }
    }
    switch (switchOwnArg) {
    case 1:                     //quit
      //  printf("\n Waiting for childs...\n");
        Zcleaner();
        printf("HASTA LA VISTA\n");
        exit(0);
    case 2:                     //cd
        if((strcmp(parsed[1],"-"))==0){
            if(chdir(getenv("OLDPWD"))!=0){
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
    case 3:         //echo
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

void execSys(char **pathargs,char** parsed,int nropaths,int bgflag)
{
    char path[100];    
    int flag=0;
    // Forking a child

    pid_t pid = fork(); 

    if (pid == -1) {
        printf("\nFailed forking child..");
        return;
    }
     else if (pid == 0) {                       //soy el hijo

        signal(SIGINT,SIG_DFL);
        signal(SIGTSTP,SIG_DFL);
        signal(SIGQUIT,SIG_DFL);


        if(strstr(parsed[0],"./")!=NULL){
            //relativo, tiene ./
            strcpy(path,getenv("PWD"));
            strcat(path,"/");
            strcat(path,parsed[0]);
            if (execv(path, parsed) < 0) {
                perror("\nCould not execute command");
            }
        }

        else{ 
            if(strchr(parsed[0],'/')!=NULL){
                strcpy(path,parsed[0]);
                if (execv(path, parsed) < 0) {
                    perror("\nCould not execute command");
                }
            }
            else{
                for(int i=0; i<nropaths; i++){      //recorro los paths de $PATH para ejecutar el comando externo
                    strcpy(path,pathargs[i]);
                    strcat(path,"/");
                    strcat(path,parsed[0]);
                    flag=execv(path,parsed);
                }
                if(flag < 0){
                    perror("\nCould not execute command");
                }
            }
        }
    
    exit(0);
    }
    else {
        // waiting for child to terminate
        if(!bgflag){
            wait(NULL);
            
            //waitpid(pid,NULL,WNOHANG); //si no hay background, espero al hijo a que termine, estoy en fg
        }
        else{
            hijosbg++;
            printf("\nProcess en bg %d\n\n",pid); //imprimo pid del hijo ejecutandose en bg 
            signal(SIGCHLD, handler);       //activo la signal para reportar la terminacion de ejecucion del hijo en bg
            //sleep(1);                       //sleep para tener la consola un poco mas ordenada por los print
            printf("\n Soy padre, deberia irme al prompt");
        }
        return;
    }
}


void executePipedCommands(char** pathargs,char** pipedargs,int nropipes,int bgflag) {
    
    char* commandaux[MAXCMD];   
     /*
        File descriptors para pipes.

        pipefd[0] > lectura
        pipefd[1] > escritura
    */
    
    int pipefd[2]; 
    pid_t p1,p2;

    

    if(pipe(pipefd) == -1){
        printf("\nError al crear pipe"); 
        return; 
    }

    p1 = fork(); 
    
    if (p1 < 0) { 
        printf("\nNo se pudo realizar fork"); 
        return; 
    }

    if(p1 == 0){

        signal(SIGINT,SIG_DFL);         //se ignoral las señales CTRL-C ,etc..
        signal(SIGTSTP,SIG_DFL);
        signal(SIGQUIT,SIG_DFL);

        close(pipefd[0]);               //se cierra el read end
        dup2(pipefd[1],STDOUT_FILENO);  //duplico el stdout
        close(pipefd[1]);               //cierro el stdout en el fd

        separador(pipedargs[0],commandaux,MAXCMD," ");
       // printf("Soy el hijo1, strings pipedargs0: %s, commandaux0: %s, commandaux1: %s. Nro args: %d \n",pipedargs[0],commandaux[0],commandaux[1],numargs);
        if (execvp(commandaux[0], commandaux) < 0) { 
            printf("\nCould not execute command 1.."); 
            exit(0); 
        }
    }
    else { 
        //Ejecucion del padre 
        p2 = fork(); 
  
        if (p2 < 0) { 
            printf("\nCould not fork"); 
            return; 
        } 
  
        // Hijo 2 
        // Solo lee del read end 
        if (p2 == 0) { 

            signal(SIGINT,SIG_DFL);
            signal(SIGTSTP,SIG_DFL);
            signal(SIGQUIT,SIG_DFL);

            close(pipefd[1]);               //cierro el output/stdout
            dup2(pipefd[0], STDIN_FILENO);  //duplico el stdin
            close(pipefd[0]);               //cierro el stdin fd 

            separador(pipedargs[1],commandaux,MAXCMD," ");
            //printf("Soy el hijo2, strings pipedargs1: %s, commandaux0: %s, commandaux1: %s. Nro args: %d \n",pipedargs[1],commandaux[0],commandaux[1],numargs);

            if (execvp(commandaux[0], commandaux) < 0) { 
                printf("\nCould not execute command 2.."); 
                exit(0); 
            } 
        } else {  
          
                close(pipefd[0]); // Cierro read end
                close(pipefd[1]); // Cierro write end

                // espero por los dos hijos
                waitpid(p1, NULL, 0);
                waitpid(p2, NULL, 0);
        } 
    } 
}

void handler(int sig)           //handler cuando un hijo muere
{
    hijosbg--;
    int status;
    pid_t pid = wait(&status);
    if (pid<0){ //Ya habia sido limpiado por un wait(no background), no hago nada
        return;
    }
    printf("\nPid %d Done. Code: %d\n", pid,status);    //el hijo estaba en ejecucion y termino, imprimo su pid 
}   

void Zcleaner(){  
                //funcion para ejecutarse al finalizar el programa principal y esperar hijos en bg
    if (hijosbg>0){
        printf("Waiting for childs.\n");
        while(hijosbg>0){
            //esperando a que terminen los hijos
        }
    }
}
