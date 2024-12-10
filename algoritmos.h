#ifndef ALGORITMOS_H
#define ALGORITMOS_H
#define MAXNOME 32

// Estruturapara almacenar os datos da cidade, o galeón e seu numero identificativo
typedef struct ataqueGaleon{
    unsigned int id;
    char cidade[MAXNOME];
    char galeon[MAXNOME];
} Ataque;

// Funcions:

/**
 * @brief Le un arquivo e almacena os datos nun array de estruturas de tipo Ataque
 * @param nomeArquivo Nome do arquivo a ler
 * @param arrayAtaques Array de estruturas de tipo Ataque onde se almacenarán os datos
 */
void lerArquivo(char *nomeArquivo, Ataque *arrayAtaques)

#endif //ALGORITMOS_H