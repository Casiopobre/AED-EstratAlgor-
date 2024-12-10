#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "algoritmos.h"
#define MAXBUF 64

void lerArquivo(char *nomeArquivo, Ataque *arrayAtaques){
    // Abrimos o arquivo
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL){
        printf(RED "Erro ao abrir o arquivo %s\n" RESET, nomeArquivo);
        exit(1);
    }

    // Lemos o arquivo
    char buffer[MAXBUF];
    int i = 0;
    fgets(buffer, MAXBUF, arquivo); // Ignoramos a primeira liña (cabceira)
    while(fgets(buffer, MAXBUF, arquivo) != NULL){
        sscanf(buffer, "%u,%[^,],%[^\n]", &arrayAtaques[i].id, arrayAtaques[i].cidade, arrayAtaques[i].galeon);
        i++;
    }
    // Pechamos o arquivo
    fclose(arquivo);
}


