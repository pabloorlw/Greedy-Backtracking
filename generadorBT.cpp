
#include "generadorBT.hpp"
#include <stdio.h>
#include "math.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

//En el mejor caso coger el primer modelo de cada prenda supone gastar justo el dinero que tenemos
void genera_caso_mejor (int nprendas, int * nmodelos, int ** precios, int dinero_total){
    int dinero_gastado = 0;
    for (int i = 1; i < nprendas; i++){
        precios[i][1] = dinero_total/nprendas;
        precios[i][0] = precios[i][1];
        precios[0][i] = precios[i][1];
        dinero_gastado = dinero_gastado + precios[i][1];
    }
    precios[nprendas][1] = dinero_total - dinero_gastado;
    precios[nprendas][0] = precios[nprendas][1];
    precios[0][nprendas] = precios[nprendas][1];
    srand(time(NULL) + rand());
    int random;
    for (int i = 1; i <= nprendas; i++){
        int j = 2;
        int maximo = precios[i][0];
        int minimo = precios[0][i];
        while (j <= nmodelos[i]){
            random = rand()%200 + 1;
            precios[i][j] = random;
            if (random > maximo){
                maximo = random;
            }
            if (random < minimo){
                minimo = random;
            }
            precios[i][0] = maximo;
            precios[0][i] = minimo;
            j++;
        }
    }
    for (int i = nprendas-1; i > 0; i--){
        precios[i][0] = precios[i][0] + precios[i+1][0];
        precios[0][i] = precios[0][i] + precios[0][i+1];
    }
    return;
}



//En el caso promedio se generan matrices aleatorias.
void genera_caso_promedio (int nprendas, int * nmodelos, int ** precios){
    srand(time(NULL) + rand());
    int random;
    for (int i = 1; i <= nprendas; i++){
        int j = 1;
        int maximo = 0;
        int minimo = 999999;
        while (j <= nmodelos[i]){
            random = rand()%200 + 1;
            precios[i][j] = random;
            if (random > maximo){
                maximo = random;
            }
            if (random < minimo){
                minimo = random;
            }
            precios[i][0] = maximo;
            precios[0][i] = minimo;
            j++;
        }
    }
    for (int i = nprendas-1; i > 0; i--){
        precios[i][0] = precios[i][0] + precios[i+1][0];
        precios[0][i] = precios[0][i] + precios[0][i+1];
    }
    return;
}

