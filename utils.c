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