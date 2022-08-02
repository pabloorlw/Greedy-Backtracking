
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define MAX_ALUMNOS 100
//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int N;
int amistad[MAX_ALUMNOS][MAX_ALUMNOS];
int trabajo[MAX_ALUMNOS][MAX_ALUMNOS];
int suma[MAX_ALUMNOS][MAX_ALUMNOS];
bool visitado[MAX_ALUMNOS];

//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////

//Usamos un struct pareja para que seleccionar pueda coger de 2 en 2
struct pareja{
    int x;
    int y;
};

//Seleccionar busca la pareja de no asignados con mayor valor en la matriz suma
pareja seleccionar(){
    int x = 0;
    int y = 0;
    int maximo = -1;
    for (int i = 0; i < N; i++){
        for (int j = i+1; j < N; j++){
            if (!visitado[i] && !visitado[j]){
                if (suma[i][j] > maximo){
                    x = i;
                    y = j;
                    maximo = suma[i][j];
                }
            }
        }
    }
    visitado[x] = true;
    visitado[y] = true;
    
    pareja resultado;
    resultado.x = x;
    resultado.y = y;
    return resultado;
}

void algoritmo_voraz(){
    int solucion[MAX_ALUMNOS];
    int bact = 0;
    
    for (int j = 0; j < MAX_ALUMNOS; j++){
        solucion[j] = -1;
    }
    
    //Creamos la matriz "suma", con la que realmente trabajamos.
    //Almacena los beneficios calculados según se indican en la especificación.
    for (int j = 0; j < N; j++){
        for (int h = j; h < N; h++){
            suma[j][h] = (amistad[j][h]+amistad[h][j])*(trabajo[j][h]+trabajo[h][j]);
            suma[h][j] = suma[j][h];
        }
    }
    
    int asignados = 0;
    //Mientras no asignemos todos, no hay SOLUCIÓN.
    while(asignados != N){
        pareja p = seleccionar();
        //SIEMPRE INSERTAMOS, FACTIBLE es siempre cierto.
        solucion[asignados] = p.x;
        solucion[asignados + 1] = p.y;
        asignados = asignados + 2;
        //Actualizamos el beneficio
        bact = bact + suma[p.x][p.y];
        //Si son impares y queda uno suelto, lo dejamos solo (será el único).
        if (N - asignados == 1){
            int i = 0;
            while (i < N && visitado[i]){
                i++;
            }
            solucion[asignados] = i;
            visitado[i] = true;
            asignados++;
        }
    }
    
    int i;
    cout << bact << endl;
    cout << solucion[0];
    i = 1;
    while (i < N){
        cout << " " << solucion[i];
        i++;
    }
    cout << endl;
    
}

int main (void)
{
    int ncasos;
    cin >> ncasos;
    for (int i= 0; i<ncasos; i++) {
        for (int j = 0; j < MAX_ALUMNOS; j++){
            visitado[j] = false;
            for (int h = 0; h < MAX_ALUMNOS; h++){
                amistad[j][h] = -1;
                trabajo[j][h] = -1;
                suma[j][h] = -1;
            }
        }
        cin >> N;
        for (int j = 0; j < N; j++){
            for (int h = 0; h < N; h++){
                if(h == j){
                    amistad[h][h] = 0;
                    h++;
                 }
                if (h < N){
                    cin >> amistad[j][h];
                }
            }
        }
        for (int j = 0; j < N; j++){
            for (int h = 0; h < N; h++){
                if(h == j){
                    trabajo[h][h] = 0;
                    h++;
                }
                if (h < N){
                    cin >> trabajo[j][h];
                }
            }
        }
        algoritmo_voraz();
    }
}

