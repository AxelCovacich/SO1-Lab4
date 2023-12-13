#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

FILE *abrirfile(char *nombre){
    FILE *fp; //creo puntero de tipo file
    fp = fopen(nombre, "r");
    if (fp == NULL)
    {
        printf("Error al abrir el archivo %s",nombre);
        exit(1);
    }

    return fp;
}

// Function to print Current Directory.
void printDir()
{
    char cwd[1024];
    char hostname[256];
    getcwd(cwd, sizeof(cwd));
    gethostname(hostname,sizeof(hostname));
    char *user = getenv("USER");
    printf("\n%s@%s:~%s",user,hostname,cwd);
}

/* Function for parsing command words.Separa las palabras segun el delmitador y las guarda en el string parsed
. return value: cant de palabras*/
int separador(char* input, char** parsed, int LIMIT, char *delimitador) {
    int i;

    for (i = 0; i < LIMIT; i++) {

        parsed[i] = strsep(&input, delimitador);

        if (parsed[i] == NULL) {
            break;
        }
        if (strlen(parsed[i]) == 0 || strcmp(parsed[i], " ") == 0) {
            i--;
        }
        else {
            parsed[i][strcspn(parsed[i], "\n")] = 0;
        }
    }
    if (parsed[1] == NULL && strcmp(delimitador, "|") == 0) {
        return 0;
    }
    return i;
}

void redirectSTDIN(char* filename){

    int newin = open(filename,O_RDONLY,0777);

        if (newin == -1){
 
            return;
        }

        original_stdin = dup(STDIN_FILENO);     //guardo el stdin original para restaurarlo despues

        if (dup2(newin,STDIN_FILENO) == -1){
            printf("\nError, could not duplcate STDIN\n"); 
            return;
        }

        if (close(newin) == -1){
            printf("\nCould not close file descriptor when redirecting STDIN\n");
            return;
        }
        /*  La tabla de file descriptors queda asi:
        0 (stdin): filename(newin)
        1 (stdout): Standard output
        2 (stderr): Standard error  
        3 orginal_stdin
        */

    return;
}

void redirectSTDOUT(char* filename){


    int newout = open(filename,(O_WRONLY | O_CREAT),0777);

    if (newout == -1){

        printf("\nError, could not redirect STDOUT\n"); 
        return;
    }

    original_stdout = dup(STDOUT_FILENO);

    if (dup2(newout,STDOUT_FILENO) == -1){
        printf("\nError, could not duplcate STDOUT\n"); 
        return;
    }

    if (close(newout) == -1){
        printf("\nCould not close file descriptor when redirecting STDOUT\n");
        return;
    }
     /*  La tabla de file descriptors queda asi:
        0 (stdin): Standard input
        1 (stdout): newout
        2 (stderr): Standard error  
        3 orginal_stdout
        */

        /*  La tabla de file descriptors queda asi si ya se redirigio el stdin:
        0 (stdin): newin
        1 (stdout): newout
        2 (stderr): Standard error  
        3 orginal_stdin
        4 original_stdout
        */

    return;
}

//funcion para restaurar la redireccion de stdin o stdout.
void restaurarSTD(int stdfile){
    
    if(stdfile == STDIN_FILENO){

        if (dup2(original_stdin,STDIN_FILENO) == -1){
            printf("\nError, could not restore STDIN\n"); 
            return;
        }

        if (close(original_stdin) == -1){
            printf("\nCould not close file descriptor when restoring STDIN\n");
            return;
        }
    }
    else{

        if (dup2(original_stdout,STDOUT_FILENO) == -1){
            printf("\nError, could not restore STDOUT\n"); 
            return;
        }

        if (close(original_stdout) == -1){
            printf("\nCould not close file descriptor when restoring STDOUT\n");
            return;
        }


    }
}
//Esta función se encarga de cortar la cadena hasta la primera coincidencia con el caracter especificado.
char *chop_to_char(char *str, char *target)
{
    str[strcspn(str, target)] = '\0';

    return str;
}
