#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

// function for parsing command words
int separador(char* input, char** parsed, int LIMIT, char *delimitador) {
    int i;
    //printf("separanding strlen:%ld \n", strlen(input));
    for (i = 0; i < LIMIT; i++) {
        //printf("adentro del for\n");
        parsed[i] = strsep(&input, delimitador);
        //printf("despeues de strsep: %s \n", parsed[i]);

        if (parsed[i] == NULL) {
            break;
        }
        if (strlen(parsed[i]) == 0 || strcmp(parsed[i], " ") == 0) {
            i--;
        }
        else {
            parsed[i][strcspn(parsed[i], "\n")] = 0;
        }
        //printf("fin del for\n");
    }
    printf("i vale: %d\n", i);
    if (parsed[1] == NULL && strcmp(delimitador, "|") == 0) {
        return 0;
    }
    return i;
}

