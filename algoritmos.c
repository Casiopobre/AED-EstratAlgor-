#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "algoritmos.h"
#include "lista.h"

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

/**
 * TODO:
 * Error para N=6 sin usadas (beneficio 79) con usadas (beneficio 83)
 */

// Contadores para os pasos que dan as funcións auxiliares:
int pasosCriterio, pasosXerar, pasosSolucion, pasosMaisIrmans, pasosRetroceder;

// Contador dos nodos visitados:
int nodosVisitados;


// Dimension da matriz de beneficios:
int nB;

// Funcions auxiliares para backtacking:

/**
 * @brief Función para imprimir a asignación
 */
void _imprimirAsignacion(int vSol[], int tamM){
    printf(BRIGHT_BOLD_GREEN "\tAsignacións: \n" RESET);
    for (int i = 0; i < tamM; i++) {
        printf(CYAN);
        printf("\tGaleón %d: ", i+1);
        switch (i){
        case 0:
            printf("\tIron Victory\n");
            break;
        case 1:
            printf("\tGrief\n");
            break;
        case 2:
            printf("\tLord Quellon\n");
            break;
        case 3:
            printf("\tLamentation\n");
            break;
        case 4:
            printf("\tKite\n");
            break;
        case 5:
            printf("\tDagger\n");
            break;
        
        default:
            printf("\tERRO\n");
            break;
        }
        printf(RESET);

        printf(BLUE);
        printf("\tCidade %d: ", i+1);
        switch (vSol[i]){
        case 0:
            printf("\tKing's Landing\n");
            break;
        case 1:
            printf("\tLannisport\n");
            break;
        case 2:
            printf("\tOldtown\n");
            break;
        case 3:
            printf("\tWhite Harbor\n");
            break;
        case 4:
            printf("\tSeagard\n");
            break;
        case 5:
            printf("\tStorm's End\n");
            break;
        
        default:
            printf("\tERRO\n");
            break;
        }
        printf(RESET);
    }   
}

/**
 * @brief Función que xera o irmau proximo na arbore
 */
void _xerar(int nivel, int vSol[], int *beneficioAct, int mBeneficios[][nB]){
    pasosXerar += 1; // Contador

    vSol[nivel] += 1;
    if (nB == 3){
        if (vSol[nivel] == 0)
            *beneficioAct += matrizBeneficios3[nivel][vSol[nivel]];
        else
            *beneficioAct += matrizBeneficios3[nivel][vSol[nivel]] - matrizBeneficios3[nivel][vSol[nivel] - 1];
    } else if (nB == 6){
        if (vSol[nivel] == 0)
            *beneficioAct += matrizBeneficios6[nivel][vSol[nivel]];
        else
            *beneficioAct += matrizBeneficios6[nivel][vSol[nivel]] - matrizBeneficios6[nivel][vSol[nivel] - 1];
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
int _solucion(int nivel, int vSol[], int tamM){
    pasosSolucion += 1; // Contador
    return (nivel == tamM - 1 && _criterio(nivel, vSol));
}

/**
 * @brief Función que comproba se hai mais irmans
 */
int _maisIrmans(int nivel, int vSol[], int tamM){
    pasosMaisIrmans += 1; // Contador
    return (vSol[nivel] < tamM-1);
}

/**
 * @brief Función que retrocede un nivel na arbore
 */
void _retroceder(int *nivel, int vSol[], int *beneficioAct){
    pasosRetroceder += 1; // Contador
    if (nB == 3)
        *beneficioAct -= matrizBeneficios3[*nivel][vSol[*nivel]];
    else if (nB == 6)
        *beneficioAct -= matrizBeneficios6[*nivel][vSol[*nivel]];
    vSol[*nivel] = -1;
    *nivel -= 1;
}

/**
 * @brief Función que implementa o algoritmo de backtracking sen vector usadas
 * @param tamM Tamaño da matriz de beneficios
 */
void Backtracking(int tamM){
    // Declaramos as variables:
    int mBeneficios[tamM][tamM], vSol[tamM], solOptimaAct[tamM];
    int nivel = 0, valorOptimoAct = -1, beneficioAct = 0;
    // Seteamos os valores iniciais:
    nB = tamM;
    pasosCriterio = 0, pasosXerar = 0, pasosSolucion = 0, pasosMaisIrmans = 0, pasosRetroceder = 0;
    nodosVisitados = 1;

    if (tamM == 3){
        for (int i = 0; i < tamM; i++) {
            for (int j = 0; j < tamM; j++) {
                mBeneficios[i][j] = matrizBeneficios3[i][j];
            }
        }
    } else if (tamM == 6){
        for (int i = 0; i < tamM; i++) {
            for (int j = 0; j < tamM; j++) {
                mBeneficios[i][j] = matrizBeneficios6[i][j];
            }
        }
    } else {
        printf(RED "Erro: N non valido\n" RESET);
        return;
    }

    for (int i = 0; i < tamM; i++){
        vSol[i] = -1;
        solOptimaAct[i] = -1;
    }
    
    do{
        _xerar(nivel, vSol, &beneficioAct, mBeneficios);
        if (_solucion(nivel, vSol, tamM) && (beneficioAct > valorOptimoAct)){
            valorOptimoAct = beneficioAct;

            for (int i = 0; i < tamM; i++){
                solOptimaAct[i] = vSol[i];
            }
        }
        if (_criterio(nivel, vSol)){
            nodosVisitados += 1;
            if (nivel < tamM-1){
                nivel += 1;
            }
        }
        while (!_maisIrmans(nivel, vSol, tamM) && nivel >= 0){
            _retroceder(&nivel, vSol, &beneficioAct);
        }
    } while (nivel != -1);

    printf(BOLD_YELLOW ">> Sin vector de usadas e matriz de tamaño %d:\n" RESET, tamM);
    printf(BOLD_GREEN);
    printf("\tBeneficio total: %d\n", valorOptimoAct);
    printf("\tNum de nodos visitados: %d\n", nodosVisitados);
    printf("\tNum pasos _criterio: %d\n", pasosCriterio);
    printf("\tNum pasos _xerar: %d\n", pasosXerar);
    printf("\tNum pasos _solucion: %d\n", pasosSolucion);
    printf("\tNum pasos _maisIrmans: %d\n", pasosMaisIrmans);
    printf("\tNum pasos _retroceder: %d\n", pasosRetroceder);
    printf(RESET);

    _imprimirAsignacion(solOptimaAct, tamM);
}


// Backtracking con vector usadas:  //////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Función que xera o irmau proximo na arbore
 */
void _xerarUsadas(int nivel, int vSol[], int *beneficioAct, int mBeneficios[][nB], int usadas[]){
    pasosXerar += 1; // Contador

    if (vSol[nivel] != -1){
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
    pasosCriterio += 1; // Contador
    return usadas[vSol[nivel]] == 1;
}

/**
 * @brief Funcion que comproba se a solucion é valida
 */
int _solucionUsadas(int nivel, int vSol[], int tamM, int usadas[]){
    pasosSolucion += 1; // Contador
    return (nivel == tamM - 1 && _criterioUsadas(nivel, vSol, usadas));
}

/**
 * @brief Función que comproba se hai mais irmans
 */
int _maisIrmansUsadas(int nivel, int vSol[], int tamM){
    pasosMaisIrmans += 1; // Contador
    return (vSol[nivel] < tamM-1);
}

/**
 * @brief Función que retrocede un nivel na arbore
 */
void _retrocederUsadas(int *nivel, int vSol[], int *beneficioAct, int usadas[]){
    pasosRetroceder += 1; // Contador
    if (nB == 3)
        *beneficioAct -= matrizBeneficios3[*nivel][vSol[*nivel]];
    else if (nB == 6)
        *beneficioAct -= matrizBeneficios6[*nivel][vSol[*nivel]];
    usadas[vSol[*nivel]] -= 1;
    vSol[*nivel] = -1;
    *nivel -= 1;
}

/**
 * @brief Función que implementa o algoritmo de backtracking con vector usadas
 */
void BacktrackingUsadas(int tamM){
    // Declaramos as variables:
    int mBeneficios[tamM][tamM], vSol[tamM], solOptimaAct[tamM], usadas[tamM];
    int nivel = 0, valorOptimoAct = -1, beneficioAct = 0;
    // Seteamos os valores iniciais:
    nB = tamM;
    pasosCriterio = 0, pasosXerar = 0, pasosSolucion = 0, pasosMaisIrmans = 0, pasosRetroceder = 0;
    nodosVisitados = 1;

    if (tamM == 3){
        for (int i = 0; i < tamM; i++) {
            for (int j = 0; j < tamM; j++) {
                mBeneficios[i][j] = matrizBeneficios3[i][j];
            }
        }
    } else if (tamM == 6){
        for (int i = 0; i < tamM; i++) {
            for (int j = 0; j < tamM; j++) {
                mBeneficios[i][j] = matrizBeneficios6[i][j];
            }
        }
    } else {
        printf(RED "Erro: N non valido\n" RESET);
        return;
    }

    for (int i = 0; i < tamM; i++){
        vSol[i] = -1;
        solOptimaAct[i] = -1;
        usadas[i] = 0;
    }
    
    do{
        _xerarUsadas(nivel, vSol, &beneficioAct, mBeneficios, usadas);
        if (_solucionUsadas(nivel, vSol, tamM, usadas) && (beneficioAct > valorOptimoAct)){
            valorOptimoAct = beneficioAct;

            for (int i = 0; i < tamM; i++){
                solOptimaAct[i] = vSol[i];
            }
        }
        if (_criterioUsadas(nivel, vSol, usadas)){
            nodosVisitados += 1;
            if (nivel < tamM - 1){
                nivel += 1;
            }
        }
        while (!_maisIrmansUsadas(nivel, vSol, tamM) && nivel >= 0){
            _retrocederUsadas(&nivel, vSol, &beneficioAct, usadas);
        }
    } while (nivel != -1);

    printf(BOLD_YELLOW ">> Con vector de usadas e matriz de tamaño %d:\n" RESET, tamM);
    printf(BOLD_GREEN);
    printf("\tBeneficio total: %d\n", valorOptimoAct);
    printf("\tNum de nodos visitados: %d\n", nodosVisitados);
    printf("\tNum pasos _criterio: %d\n", pasosCriterio);
    printf("\tNum pasos _xerar: %d\n", pasosXerar);
    printf("\tNum pasos _solucion: %d\n", pasosSolucion);
    printf("\tNum pasos _maisIrmans: %d\n", pasosMaisIrmans);
    printf("\tNum pasos _retroceder: %d\n", pasosRetroceder);
    printf(RESET);

    _imprimirAsignacion(solOptimaAct, tamM);

}



/**
 * TODO:
 * Imprimir as asignacións, e revisar valores
 */

// Funcións auxiliares para ramificación e poda:

// Determina o valor máximo dunha matriz
int max(int B[][N]){
    int max = B[0][0];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(B[i][j] > max) max = B[i][j];
        }
    }
    return max;
}

// Calcula o beneficio estimado dun nodo
void _BE(TIPOELEMENTOLISTA *e){
    e->BE = (e->CI + e->CS) / 2;
}

// Valcula a cota inferior dun nodo
void _CI_trivial(TIPOELEMENTOLISTA *e){
    e->CI = e->beneficioAct;
}

// Calcula a cota superior dun nodo
void _CS_trivial(TIPOELEMENTOLISTA *e, int mBeneficios[][N]){
    e->CS = e->beneficioAct + (N - (e->nivel + 1)) * max(mBeneficios);
}

TIPOELEMENTOLISTA _seleccionar(TLISTA *l){
    TPOSICION pos = primeroLista(*l);
    float beneficioMax = -1;
    TIPOELEMENTOLISTA nodoMax;
    TPOSICION posMax = NULL;

    while(pos != finLista(*l)){
        TIPOELEMENTOLISTA nodoAct;
        recuperarElementoLista(*l, pos, &nodoAct);
        if(nodoAct.BE > beneficioMax){
            beneficioMax = nodoAct.BE;
            nodoMax = nodoAct;
            posMax = pos;
        }
        pos = siguienteLista(*l, pos);
    }

    if(posMax != NULL){
        suprimirElementoLista(l, posMax);
    }
    return nodoMax;
}

int _solucionRyP(TIPOELEMENTOLISTA e){
    return e.nivel == (N-1);
}

void asignacionTrivial(){
    // Matriz a emplear:
    int mBeneficios[N][N];
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
    nodosVisitados = 1;

    TLISTA LNV;
    TIPOELEMENTOLISTA raiz, x, y, s;
    float C = 0;

    raiz.beneficioAct = 0;
    raiz.nivel = -1;
    for (int i = 0; i < N; i++){
        raiz.tupla[i] = -1;
        raiz.usadas[i] = 0;
    }
    _CI_trivial(&raiz);
    _CS_trivial(&raiz, mBeneficios);
    _BE(&raiz);
    raiz.n = 1;
    y.n = raiz.n;

    s.beneficioAct = -1;

    C = raiz.CI;

    // Creaos a lista
    crearLista(&LNV);

    // Gardo a raiz como o primeiro nodo da LNV
    insertarElementoLista(&LNV, primeroLista(LNV), raiz);

    // Aplicamos RyP
    while(!esListaVacia(LNV)){
        x = _seleccionar(&LNV);
        if(x.CS > C){
            for (int i = 0; i < N; i++){
                y.nivel = x.nivel+1;
                for (int j = 0; j < N; j++){
                    y.tupla[j] = x.tupla[j];
                    y.usadas[j] = x.usadas[j];
                }
                if (!x.usadas[i]){
                    y.tupla[y.nivel] = i;
                    y.usadas[i] = 1;
                    y.beneficioAct = x.beneficioAct + mBeneficios[y.nivel][i];

                    _CI_trivial(&y);
                    _CS_trivial(&y, mBeneficios);
                    _BE(&y);

                    y.n += 1;

                    if (_solucionRyP(y) && (y.beneficioAct > s.beneficioAct)){
                        s = y;
                        if (y.beneficioAct > C)
                            C = y.beneficioAct;
                    } else if (!_solucionRyP(y) && (y.CS > C)){
                        insertarElementoLista(&LNV, primeroLista(LNV), y);
                        if(y.CI > C)
                            C = y.CI;
                    }
                }
            }
        }
    }

    printf(BOLD_YELLOW "\n>> Ramificacion e poda con asignacón trivial (matriz de tamaño %d):\n" RESET, N);
    printf(BOLD_GREEN "\tSolucion: %d\n", s.beneficioAct);
    printf("\tNum nodos: %d\n" RESET, y.n);

}

int _asignacionVoraz(TIPOELEMENTOLISTA e, int mBeneficios[][N]){
    int beneficioAcumulado = 0;
    int usadasAux[N];
    for(int i = 0; i < N; i++){
        usadasAux[i] = e.usadas[i];
    }

    for (int i = e.nivel+1; i < N; i++){
        int maxBeneficio = -1;
        int k = -1;

        for (int j = 0; j < N; j++){
            if(!usadasAux[j] && mBeneficios[i][j] > maxBeneficio){
                maxBeneficio = mBeneficios[i][j];
                k = j;
            }
        }

        if(k != -1){
            usadasAux[k] = 1;
            beneficioAcumulado += maxBeneficio;
        }
    }
    return beneficioAcumulado;
}

int _maximosTareas(TIPOELEMENTOLISTA e, int mBeneficios[][N]){
    int beneficioAcumulado = 0;
    for(int i = e.nivel + 1; i < N; i++){
            int maxBeneficio = -1;
            for(int j= 0; j<N; j++){
                if (mBeneficios[i][j] > maxBeneficio){
                    maxBeneficio = mBeneficios[i][j];
                }
            }
            beneficioAcumulado += maxBeneficio;
        }
        return beneficioAcumulado;
}

void _CI_precisa(TIPOELEMENTOLISTA *e, int mBeneficios[][N]){
    e->CI = e->beneficioAct + _asignacionVoraz(*e, mBeneficios);
}

void _CS_precisa(TIPOELEMENTOLISTA *e, int mBeneficios[][N]){
    e->CS = e->beneficioAct + _maximosTareas(*e, mBeneficios);
}

TIPOELEMENTOLISTA _solAsignacionVoraz(TIPOELEMENTOLISTA e, int mBeneficios[][N]){
    int beneficioMax, tMax;
    for (int i = e.nivel+1; i < N; i++){
        beneficioMax = -1;
        tMax = -1;
        for(int j = 0; j < N; j++){
            if(!e.usadas[j] && mBeneficios[i][j] > beneficioMax){
                beneficioMax = mBeneficios[i][j];
                tMax = j;
            }
        }
        e.tupla[i] = tMax;
        e.usadas[tMax] = 1;
        e.beneficioAct += beneficioMax;
    }
    e.nivel = N - 1;
    return e;
}

void asignacionPrecisa(){
    // Matriz a emplear:
    int mBeneficios[N][N];
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

    // Seteamos as variables
    nodosVisitados = 1; // COntamos a raiz
    TLISTA LNV;
    TIPOELEMENTOLISTA raiz, x, y, s;
    float C = 0;

    raiz.beneficioAct = 0;
    raiz.nivel = -1;
    for (int i = 0; i < N; i++){
        raiz.usadas[i] = 0;
        raiz.tupla[i] = -1;
    }
    _CI_precisa(&raiz, mBeneficios);
    _CS_precisa(&raiz, mBeneficios);
    _BE(&raiz);

    crearLista(&LNV);
    insertarElementoLista(&LNV, primeroLista(LNV), raiz);

    s.beneficioAct = -1;

    while(!esListaVacia(LNV)){
        x = _seleccionar(&LNV);
        if(x.CS > C){
            for (int i = 0; i < N; i++){
                y = x;
                y.nivel = x.nivel + 1;

                if (!x.usadas[i]){
                    y.tupla[y.nivel] = i;
                    y.usadas[i] = 1;
                    y.beneficioAct = x.beneficioAct + mBeneficios[y.nivel][i];
                    _CI_precisa(&y, mBeneficios);
                    _CS_precisa(&y, mBeneficios);
                    _BE(&y);
                    nodosVisitados ++;

                    if (!_solucionRyP(y) && y.CS >= C && y.CS == y.CI){
                        y = _solAsignacionVoraz(y, mBeneficios);
                        s = y;
                        if(y.beneficioAct > C)
                            C = y.beneficioAct;
                        continue;
                    }
                    if (_solucionRyP(y) && y.beneficioAct > s.beneficioAct){
                        s = y;
                        if(y.beneficioAct > C)
                            C = y.beneficioAct;
                    } else if(!_solucionRyP(y) && y.CS > C){
                        insertarElementoLista(&LNV, primeroLista(LNV), y);
                    }
                }
            }
        } else if(x.CS == C && x.CS == x.CI){
            s = _solAsignacionVoraz(x, mBeneficios);
        }
    }
    printf(BOLD_YELLOW "\n>> Ramificacion e poda con asignacón precisa (matriz de tamaño %d):\n" RESET, N);
    printf(BOLD_GREEN "\tSolucion: %d\n", s.beneficioAct);
    printf("\tNum nodos: %d\n" RESET, nodosVisitados);
}


