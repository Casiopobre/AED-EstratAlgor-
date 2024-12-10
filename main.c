#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "algoritmos.h"
#define TAMARRAY 10

int main() {
    char opcion;
    Ataque arrayAtaques[TAMARRAY];
    
    do {
        printf(BOLD_MAGENTA);
        printf("\n--------------------------------------------------------");
        printf("\n~*~*~*~*~*~*~*~ Seleccione unha opción ~*~*~*~*~*~*~*~\n");
        printf("\na) Backtracking\n");
        printf("\nb) Ramificacion e poda\n");
        printf("\ns) Sair\n");
        printf("--------------------------------------------------------\n");
        printf(RESET);
        printf("\nOpcion: ");
        scanf(" %c", &opcion);

        switch (opcion)
        {
        case 'a': case 'A':
            /* code */
            break;

        case 'b': case 'B':
            /* code */
            break;

        default:
            break;
        }
    } while (opcion != 's');
}