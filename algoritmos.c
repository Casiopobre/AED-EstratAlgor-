#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "algoritmos.h"

int matrizBeneficios3[3][3] = {
    {11, 17, 8},
    {9, 7, 6},
    {13, 15, 16}
};
int matrizBeneficios6[6][6] = {
    {11, 17, 8, 16, 20, 14},
    {9, 7, 6, 12, 15, 18},
    {13, 15, 16, 12, 16, 18},
    {21, 24, 28, 17, 26, 20},
    {10, 14, 12, 11, 15, 13},
    {12, 20, 19, 13, 22, 17}
};

// Contadores para os pasos que dan as funcións auxiliares:
int pasosCriterio = 0, pasosXerar = 0, pasosSolucion = 0, pasosMaisIrmans = 0, pasosRetroceder = 0;
int pasosCriterioUsadas = 0, pasosXerarUsadas = 0, pasosSolucionUsadas = 0, pasosMaisIrmansUsadas = 0, pasosRetrocederUsadas = 0;

// Contador dos nodos visitados:
int nodosVisitados = 1;
int nodosVisitadosUsadas = 1;

// Dimension da matriz de beneficios:
int nB;

// Funcions auxiliares para backtacking:

/**
 * @brief Función que xera o irmau proximo na arbore
 */
void _xerar(int nivel, int vSol[], int *beneficioAct, int mBeneficios[][nB]){
    pasosXerar += 1; // Contador

    vSol[nivel] += 1;

    if (vSol[nivel] == 0){
        *beneficioAct += matrizBeneficios3[nivel][vSol[nivel]];
    } else {
        *beneficioAct += matrizBeneficios3[nivel][vSol[nivel]] - matrizBeneficios3[nivel][vSol[nivel] - 1];
    }
}

/**
 * @brief Función que comproba se a asignacion e valida (SEN VECTOR USADAS)
 */

int _criterio(int nivel, int vSol[]){
    for (int i = 0; i < nivel; i++){
        pasosCriterio += 1; // Contador
        if (vSol[nivel] == vSol[i]){
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Función que comproba se se chegou a unha solución valida
 */
int _solucion(int nivel, int vSol[], int N){
    pasosSolucion += 1; // Contador
    return (nivel == N - 1 && _criterio(nivel, vSol));
}

/**
 * @brief Función que comproba se hai mais irmans
 */
int _maisIrmans(int nivel, int vSol[], int N){
    pasosMaisIrmans += 1; // Contador
    return (vSol[nivel] < N-1);
}

/**
 * @brief Función que retrocede un nivel na arbore
 */
void _retroceder(int *nivel, int vSol[], int *beneficioAct){
    pasosRetroceder += 1; // Contador
    *beneficioAct -= matrizBeneficios3[*nivel][vSol[*nivel]];
    vSol[*nivel] = -1;
    *nivel -= 1;
}

/**
 * @brief Función que implementa o algoritmo de backtracking sen vector usadas
 */
void Backtracking(int N){
    // Declaramos as variables:
    int mBeneficios[N][N], vSol[N], solOptimaAct[N];
    int nivel = 0, valorOptimoAct = -1, beneficioAct = 0;
    nB = N;

    if (N == 3){
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                mBeneficios[i][j] = matrizBeneficios3[i][j];
            }
        }
    } else if (N == 6){
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                mBeneficios[i][j] = matrizBeneficios6[i][j];
            }
        }
    } else {
        printf(RED "Erro: N non valido\n" RESET);
        return;
    }

    for (int i = 0; i < N; i++){
        vSol[i] = -1;
        solOptimaAct[i] = -1;
    }
    
    do{
        _xerar(nivel, vSol, &beneficioAct, mBeneficios);
        if (_solucion(nivel, vSol, N) && (beneficioAct > valorOptimoAct)){
            valorOptimoAct = beneficioAct;

            for (int i = 0; i < 3; i++){
                solOptimaAct[i] = vSol[i];
            }
        }
        if (_criterio(nivel, vSol)){
            nodosVisitados += 1;
            if (nivel < N - 1){
                nivel += 1;
            }
        }
        while (!_maisIrmans(nivel, vSol, N) && nivel >= 0){
            _retroceder(&nivel, vSol, &beneficioAct);
        }
    } while (nivel != -1);

    printf(BOLD_YELLOW ">> Sin vector de usadas e matriz de tamaño %d:\n" RESET, N);
    printf(BOLD_GREEN);
    printf("\tValor optimo: %d\n", valorOptimoAct);
    printf("\tNum de nodos visitados: %d\n", nodosVisitados);
    printf("\tNum pasos _criterio: %d\n", pasosCriterio);
    printf("\tNum pasos _xerar: %d\n", pasosXerar);
    printf("\tNum pasos _solucion: %d\n", pasosSolucion);
    printf("\tNum pasos _maisIrmans: %d\n", pasosMaisIrmans);
    printf("\tNum pasos _retroceder: %d\n", pasosRetroceder);
    printf(RESET);
    
}


// Backtracking con vector usadas:  //////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Función que xera o irmau proximo na arbore
 */
void _xerarUsadas(int nivel, int vSol[], int *beneficioAct, int mBeneficios[][nB], int usadas[]){
    pasosXerarUsadas += 1; // Contador

    if (vSol[nivel] == -1){
        usadas[vSol[nivel]] -= 1;
    }
    vSol[nivel] += 1;
    usadas[vSol[nivel]] += 1;
    if(vSol[nivel] == 0){
        *beneficioAct += mBeneficios[nivel][vSol[nivel]];
    } else {
        *beneficioAct += mBeneficios[nivel][vSol[nivel]] - mBeneficios[nivel][vSol[nivel] - 1];
    }
}

/**
 * @brief Función que comproba se a asignacion e valida (CON VECTOR USADAS)
 */
int _criterioUsadas(int nivel, int vSol[], int usadas[]){
    for (int i = 0; i < nivel; i++){
        pasosCriterioUsadas += 1; // Contador
        return usadas[vSol[nivel]] == 1;
    }
    return -1;
}

/**
 * @brief Funcion que comproba se a solucion é valida
 */
int _solucionUsadas(int nivel, int vSol[], int N, int usadas[]){
    pasosSolucionUsadas += 1; // Contador
    return (nivel == N - 1 && _criterioUsadas(nivel, vSol, usadas));
}

/**
 * @brief Función que comproba se hai mais irmans
 */
int _maisIrmansUsadas(int nivel, int vSol[], int N){
    pasosMaisIrmansUsadas += 1; // Contador
    return (vSol[nivel] < N-1);
}

/**
 * @brief Función que retrocede un nivel na arbore
 */
void _retrocederUsadas(int *nivel, int vSol[], int *beneficioAct, int usadas[]){
    pasosRetrocederUsadas += 1; // Contador
    *beneficioAct -= matrizBeneficios3[*nivel][vSol[*nivel]];
    usadas[vSol[*nivel]] -= 1;
    vSol[*nivel] = -1;
    *nivel -= 1;
}

/**
 * @brief Función que implementa o algoritmo de backtracking con vector usadas
 */
void BacktrackingUsadas(int N){
    // Declaramos as variables:
    int mBeneficios[N][N], vSol[N], solOptimaAct[N], usadas[N];
    int nivel = 0, valorOptimoAct = -1, beneficioAct = 0;
    nB = N;

    if (N == 3){
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                mBeneficios[i][j] = matrizBeneficios3[i][j];
            }
        }
    } else if (N == 6){
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                mBeneficios[i][j] = matrizBeneficios6[i][j];
            }
        }
    } else {
        printf(RED "Erro: N non valido\n" RESET);
        return;
    }

    for (int i = 0; i < N; i++){
        vSol[i] = -1;
        solOptimaAct[i] = -1;
        usadas[i] = 0;
    }
    
    do{
        _xerarUsadas(nivel, vSol, &beneficioAct, mBeneficios, usadas);
        if (_solucionUsadas(nivel, vSol, N, usadas) && (beneficioAct > valorOptimoAct)){
            valorOptimoAct = beneficioAct;

            for (int i = 0; i < 3; i++){
                solOptimaAct[i] = vSol[i];
            }
        }
        if (_criterioUsadas(nivel, vSol, usadas)){
            nodosVisitados += 1;
            if (nivel < N - 1){
                nivel += 1;
            }
        }
        while (!_maisIrmansUsadas(nivel, vSol, N) && nivel >= 0){
            _retrocederUsadas(&nivel, vSol, &beneficioAct, usadas);
        }
    } while (nivel != -1);

    printf(BOLD_YELLOW ">> Con vector de usadas e matriz de tamaño %d:\n" RESET, N);
    printf(BOLD_GREEN);
    printf("\tValor optimo: %d\n", valorOptimoAct);
    printf("\tNum de nodos visitados: %d\n", nodosVisitados);
    printf("\tNum pasos _criterio: %d\n", pasosCriterio);
    printf("\tNum pasos _xerar: %d\n", pasosXerar);
    printf("\tNum pasos _solucion: %d\n", pasosSolucion);
    printf("\tNum pasos _maisIrmans: %d\n", pasosMaisIrmans);
    printf("\tNum pasos _retroceder: %d\n", pasosRetroceder);
    printf(RESET);
    
}
