/*
    Algoritmo que realiza la mezcla de K vectores ordenados de tamaño N 
    ordenados de menor a mayor en un vector de tamaño K*N mediante fuerza bruta

    Alumno1: Jose Luis Pedraza Román
    Alumno2: Pedro Checa Salmerón
    Alumno3: Antonio Carlos Perea Parras
    Alumno4: Raúl Del Pozo Moreno

    UGR - ETSIIT - GII - Algoritmica - B1 - Grupo “Oliva”

    Los archivos .cpp tienen que estar en una carpeta "src" 
    y los archivos binarios en una carpeta "bin"
    Compilar en la ruta que contiene dichas carpetas.

    Compilacion: g++ -std=gnu++0x src/mezcla_bruta.cpp -o bin/mezcla_bruta
    Ejecucion:   ./bin/mezcla_bruta N K
    N = tamaño vectores
    K = numero vectores

*/

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

/**
 * @brief Metodo que calcula un numero random
 * 
 * @return double Numero generado
 */
double uniforme() {
    int t = rand();
    double f = ((double)RAND_MAX + 1.0);
    return (double)t / f;
}

/**
 * @brief Metodo que genera una matriz mediante el algoritmo de Knuth para K vectores de N tamaños
 * 
 * @param K Numero de vectores
 * @param N Numero de elementos por vector
 * @return int** Matriz K*N de vectores ordenados de menor a mayor
 */
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

/**
 * @brief Metodo que compara un vector con la solucion de la comparacion anterior con un nuevo vector obtenido de una matriz
 * 
 * @param T Matriz donde obtiene cada vector a comparar
 * @param vectAnt Vector que contiene la solucion a las comparaciones de vectores previas
 * @param N Tamaño de los vectores de la matriz
 * @param iter Contador que indica la fila de la matriz que debe comparar
 * @return int* Vector solucion con la solucion anterior y el vector que se ha comparado de forma ordenada
 */
int* comparaVectores(int **T, int *vectAnt, int N, int iter) {

    //Reserva memoria para la solucion
    int *solucionA = new int[N*(iter+1)]; 
    assert(solucionA);
    //Almacena la posicion de la j (evita empezar desde el principio y repetir elementos del vector comparado)
    int j, pos_ultima = 0; 
    //Contador para almacenar la posicion insertada en el vector solucion
    int contador = 0; 

    //Recorre el vector principal (anterior con solucion)
    for (int i = 0 ; i < N*iter ; i++) {

        //Indica que se termina de recorrer el vector secundario
        bool termina = false;

        //Si el vector secundario ha alcanzado el limite, se añaden el resto de elementos del vector primario
        if(pos_ultima == N) solucionA[contador++] = vectAnt[i];
        //Se comparan vectores
        else {
            //Se recorre el vector secundario
            for (j = pos_ultima ; j < N && !termina ; j++) {

                //Si valor_i < valor_j, añade valor_i
                if (vectAnt[i] < T[iter][j]) {
                    solucionA[contador++] = vectAnt[i];
                    termina = true; //Termina de comparar el vector secundario
                }
                // Si valor_i >= valor_j, se añade j
                else solucionA[contador++] = T[iter][j];
                
                //Para no perder la posicion y no comparar elementos ya comparados
                pos_ultima = j;
                // Si es igual se reañade, los elementos siguientes son mayores, se termina de comparar
                if (vectAnt[i] == T[iter][j]) { 
                    solucionA[contador++] = vectAnt[i]; 
                    termina = true; 
                    pos_ultima++;
                }
                //Si es la ultima iter del vector comparado y es menor valor_j que valor_i, se añade
                else if(pos_ultima == N-1 && vectAnt[i] >= T[iter][j]) {
                    solucionA[contador++] = vectAnt[i];
                    pos_ultima++;
                }
            }
        }
    }
    
    //Añadir elementos restantes
    if (pos_ultima < N)
        for (int i = pos_ultima ; i < N ; i++) solucionA[contador++] = T[iter][i];

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

    //reserva memoria array solucion
    int *solucion = new int[2*N];
    assert(solucion);

    //Declaracion variable tiempo total de ejecucion del algoritmo
    duration<double> suma = steady_clock::duration::zero();
    
    //Ejecuta 5 veces el algoritmo y divide el timpo total entre 5
    for(int p = 0 ; p < 5 ; p++) {
        
        //Genera matriz con algoritmo de Knuth
        T = generaMatrizT(K, N);

        //Inicializa la solucion inicial
        for(int i = 0 ; i < N ; i++) solucion[i] = T[0][i];

        //Obtiene el tiempo antes del algoritmo
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

        //Obtiene el tiempo despues del algoritmo
        tdespues = high_resolution_clock::now();
        suma += duration_cast<duration<double>>(tdespues - tantes);
    }
    std::cout << K << " " << suma.count()/5 << std::endl;
    
    return 0;
}