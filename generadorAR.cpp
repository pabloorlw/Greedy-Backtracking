
#include "generadorAR.hpp"
#include <stdio.h>
#include "math.h"
#include <iostream>
#include <stdlib.h>

using namespace std;


//En el caso promedio se generan matrices aleatorias.
void genera_caso_promedio (int n, int ** amistad; int ** trabajo){
    srand(time(NULL) + rand());
    int random;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i == j){
                amistad[i][j] = 0;
                trabajo[i][j] = 0;
            } else{
                random = rand()%9 + 1;
                amistad[i][j] = random;
                random = rand()%9 + 1;
                trabajo[i][j] = random;
            }
            
        }
        
    }
    return;
}

