
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define MAX_PRENDAS 20
#define MAX_MODELOS 20
//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nivel;
int M;
int C;
int precios[MAX_PRENDAS + 1][MAX_MODELOS + 1];
int s[MAX_PRENDAS + 1];
int modelos[MAX_PRENDAS + 1];
int pact;

//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////

//Función generar del esquema de backtracking
void generar(){
    //Si no es 0 restamos antes de sumar
    if (s[nivel] != 0){
        pact = pact - precios[nivel][s[nivel]];
        s[nivel] = s[nivel] + 1;
        pact = pact + precios[nivel][s[nivel]];
    } else {
        s[nivel] = s[nivel] + 1;
        pact = pact + precios[nivel][s[nivel]];
    }
   
}

//Función solucion del esquema de backtracking
bool solucion(){
    //Si estamos en el ultimo nivel y el dinero gastado no es demasiado devolvemos true.
    return (nivel == C) && (pact <= M);
}

//Función criterio del esquema de backtracking
//Separamos en varios condicionales para que no sea un condicional muy largo.
bool criterio(int voa){
    if ((nivel == C) || (pact >= M) || (pact + precios[nivel + 1][0] <= voa)){
        return false;
    }
    if (pact + precios[0][nivel + 1] > M){
        return false;
    }
    if (voa == M){
        return false;
    }
    return true;
}

//Función mas_hermanos del esquema de backtracking
bool mas_hermanos(){
    //devolvemos true si no es el último modelo.
    return s[nivel] < modelos[nivel];
    
}

//Función retroceder del esquema de backtracking
void retroceder(){
    //Hay que restar un poner a 0 el array s antes de retroceder en el nivel.
    pact = pact - precios[nivel][s[nivel]];
    s[nivel] = 0;
    nivel--;
}

//Función principal del esquema de backtracking
void backtracking(){
    nivel = 1;
    pact = 0;
    int voa = -1;
    do {
        generar();
        if ((solucion()) && (pact > voa)){
            voa = pact;
        }
        if (criterio(voa)){
            nivel++;
        } else {
            //Añadimos la condición de que si la sol. encontrada es la maxima no se visitan los hermanos, no es necesario.
            while ((!mas_hermanos() || voa == M) && (nivel > 0)){
                retroceder();
            }
        }
    } while (nivel > 0);
    if (voa == -1){
        cout << "no solution" << endl;
    } else {
        cout << voa << endl;
    }
    
    
}

int main (void)
{
    int ncasos;
    cin >> ncasos;
    for (int i= 0; i<ncasos; i++) {
        cin >> M >> C;
        for (int j = 0; j < MAX_PRENDAS + 1; j++){
            s[j] = 0;
            modelos[j] = 0;
            for (int h = 0; h < MAX_MODELOS + 1; h++){
                precios[j][h] = -1;
            }
        }
        for (int j = 1; j <= C; j++){
            int nmodelos;
            int maximo = 0;
            int minimo = 999999;
            cin >> nmodelos;
            modelos[j] = nmodelos;
            for (int h = 1; h <= nmodelos; h++){
                cin >> precios[j][h];
                if (precios[j][h] > maximo){
                    maximo = precios[j][h];
                }
                if (precios[j][h] < minimo){
                    minimo = precios[j][h];
                }
            }
            precios[j][0] = maximo;
            precios[0][j] = minimo;
        }
        for (int j = C-1; j > 0; j--){
            precios[j][0] = precios[j][0] + precios[j+1][0];
            precios[0][j] = precios[0][j] + precios[0][j+1];
        }
        backtracking();
    }
        
}

