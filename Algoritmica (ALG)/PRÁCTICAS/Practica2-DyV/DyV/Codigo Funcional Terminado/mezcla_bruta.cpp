#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>
#include <chrono>

using namespace std::chrono;

double uniforme() {
    int t = rand();
    double f = ((double)RAND_MAX + 1.0);
    return (double)t / f;
}

int** generaMatrizT(int K, int N) {
    int **T;
    T = new int *[K];
    assert(T);

    for (int i = 0; i < K; i++) T[i] = new int[N];

    int TAM = K * N;
    int *aux = new int[TAM];
    assert(aux);

    srand(time(0));
    //genero todos los enteros entre 0 y k*n-1
    for (int j = 0; j < TAM; j++)
    aux[j] = j;

    //para cada uno de los k vectores se lanza el algoritmo S (sampling) de Knuth
    for (int i = 0; i < K; i++) {
        int t = 0, m = 0;
        while (m < N) {
            double u = uniforme();
            if ((TAM - t) * u >= (N - m)) t++;
            else {
                T[i][m] = aux[t];
                t++;
                m++;
            }
        }
    }
    delete[] aux;

    return T;
}

int* comparaVectores(int **T, int *vectAnt, int N, int iteraccion) {

    int *solucionA = new int[N*(iteraccion+1)]; 
    assert(solucionA);
    int j, pos_ultima = 0; //Almacena la posicion de la j (evita empezar desde el principio y repetir elementos del vector comparado)
    int contador = 0; //Contador para almacenar la posicion insertada en el vector solucion

    //Recorre el vector principal (anterior con solucion)
    for (int i = 0 ; i < N*iteraccion ; i++) {
        //Indica que se termina de recorrer el vector secundario
        bool termina = false;
        //Si el vector secundario ha alcanzado el limite, se añaden el resto de elementos del vector primario
        if(pos_ultima == N) solucionA[contador++] = vectAnt[i]; 
        //Se comparan vectores
        else {
            //Se recorre el vector secundario
            for (j = pos_ultima ; j < N && !termina ; j++) {
                //Si valor_i < valor_j, añade valor_i
                if (vectAnt[i] < T[iteraccion][j]) {
                    solucionA[contador++] = vectAnt[i];
                    termina = true; //Termina de comparar el vector secundario
                }
                // Si valor_i >= valor_j, se añade j
                else solucionA[contador++] = T[iteraccion][j];
                //Para no perder la posicion y no comparar elementos ya comparados
                pos_ultima = j;
                // Si es igual se reañade, los elementos siguientes son mayores, se termina de comparar
                if (vectAnt[i] == T[iteraccion][j]) { 
                    solucionA[contador++] = vectAnt[i]; 
                    termina = true; 
                    pos_ultima++; 
                }
                //Si es la ultima iteraccion del vector comparado y es menor valor_j que valor_i, se añade
                else if(pos_ultima == N-1 && vectAnt[i] >= T[iteraccion][j]) {
                    solucionA[contador++] = vectAnt[i];
                    pos_ultima++;
                }
            }
        }
    }
    
    //Añadir elementos restantes
    if (pos_ultima < N)
        for (int i = pos_ultima ; i < N ; i++) solucionA[contador++] = T[iteraccion][i];

    return solucionA;
}


int main (int argc, char *argv[]) {

    if(argc != 3) {
        std::cout << "Nuero parametros invalido: ./mezcla_bruta n k";
        return 1;
    }

    const int N = atoi(argv[1]); //Tam vector
    const int K = atoi(argv[2]); //Num vectores

    //Reserva memoria matriz
    int **T;
    T = new int *[K];
    assert(T);
    for (int i = 0; i < K; i++) T[i] = new int[N];

    //Reserva memoria vector auxiliar
    int TAM = K * N;
    int *aux = new int[TAM];
    assert(aux);

    duration<double> suma = steady_clock::duration::zero();
    for(int p = 0 ; p < 5 ; p++) {
        
        //Genera matriz con algoritmo de Knuth
        T = generaMatrizT(K, N);

        //Almacena el primer vector como resultado (resultado)
        int *solucion = new int[2*N];
        assert(solucion);
        for(int i = 0 ; i < N ; i++) solucion[i] = T[0][i];

        //Toma de tiempos de ejecucion DyV
        high_resolution_clock::time_point tantes, tdespues;
        tantes = high_resolution_clock::now();

        //Recorre todos los vectores
        for(int i = 1 ; i < K ; i++) {
            //Reserva memoria vector solucion temporal
            int *solucionAux = new int[N*(i+1)];
            //Compara solucion anterior con el siguiente vector de la matriz
            solucionAux = comparaVectores(T, solucion, N, i);
            //Actualiza la solucion
            for(int j = 0 ; j < N*(i+1) ; j++) solucion[j] = solucionAux[j];
        }

        tdespues = high_resolution_clock::now();
        suma += duration_cast<duration<double>>(tdespues - tantes);
    }
    std::cout << TAM << " " << suma.count()/5 << std::endl;


    ///////////////////////////////////////////////////////

    //Muestra solucion
    /*
    cout << endl;
    for(int i = 0 ; i < K*N ; i++) cout << solucion[i] << " ";
    cout << endl;
    */


    return 0;
}