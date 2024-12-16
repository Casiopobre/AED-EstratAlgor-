#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "algoritmos.h"


int main() {
    char opcion, opcion2; 
    
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
            do{
                printf(BOLD_MAGENTA);
                printf("\n--------------------------------------------------------");
                printf("\n~*~*~*~*~*~*~*~ Seleccione unha opción ~*~*~*~*~*~*~*~\n");
                printf("\na) Con 3 elementos (sen vector usadas)\n");
                printf("\nb) Con 6 elementos (sen vector usadas)\n");
                printf("\nc) Con 3 elementos (con vector usadas)\n");
                printf("\nd) Con 6 elementos (con vector usadas)\n");
                printf("\ne) Atrás\n");
                printf("--------------------------------------------------------\n");
                printf(RESET);
                printf("\nOpcion: ");
                scanf(" %c", &opcion2);

                switch (opcion2){
                case 'a': case 'A':
                    Backtracking(3);
                    break;
                case 'b': case 'B':
                    Backtracking(6);
                    break;
                case 'c': case 'C':
                    BacktrackingUsadas(3);
                    break;
                case 'd': case 'D':
                    BacktrackingUsadas(6);
                    break;
                
                default:
                    break;
                }

            } while (opcion2 != 'e');
            break;

        case 'b': case 'B':
            /* code */
            break;

        default:
            break;
        }
    } while (opcion != 's');
}