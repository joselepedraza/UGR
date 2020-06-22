/*
    Algoritmo que realiza la mezcla de K arrays ordenados de tamaño N 
    ordenados de menor a mayor en un arrayde tamaño K*N mediante fuerza bruta

    Alumno1: Jose Luis Pedraza Román
    Alumno2: Pedro Checa Salmerón
    Alumno3: Antonio Carlos Perea Parras
    Alumno4: Raúl Del Pozo Moreno

    UGR - ETSIIT - GII - Algoritmica - B1 - Grupo “Oliva”

    Los archivos .cpp tienen que estar en una carpeta "src" 
    y los archivos binarios en una carpeta "bin"
    Compilar en la ruta que contiene dichas carpetas.

    Compilacion: g++ -std=gnu++0x src/mezcla_DyV.cpp -o bin/mezcla_DyV
    Ejecucion:   ./bin/mezcla_DyV N K
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
 * @brief Metodo que genera una matriz mediante el algoritmo de Knuth para K arrays de N tamaños
 * 
 * @param K Numero de arrays
 * @param N Numero de elementos por vector
 * @return int** Matriz K*N de arrays ordenados de menor a mayor
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

    //para cada uno de los k arrays se lanza el algoritmo S (sampling) de Knuth
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
 * @brief Metodo que une y ordena partes de un vector. 
 * 
 * @param inicio Limite inferior desde donde ordena 
 * @param final limite superior hasta donde ordena
 * @param solucion Array de enteros que almacena y ordena partes de otros arrays
 * @param N Tamaño de los arrays de la matriz origen
 */
void unir_ordenados(int inicio, int final, int *solucion, int N) {
    
    //Calcula la mitad del vector
    int mitad = (inicio+final)/2;

    //Establece el final de los arrays
    int final_izq = (mitad-inicio+1)*N;
    int final_der = (final-mitad)*N;  

    //Crea arrays auxiliares
    int *arr_izq = new int[final_izq];
    int *arr_der = new int[final_izq];   

    //Rellena los arrays auxiliares
    for (int i = 0 ; i < final_izq ; i++) arr_izq[i] = solucion[inicio*N + i];
    for (int i = 0; i < final_der; i++) arr_der[i] = solucion[(mitad+1)*N + i];

    //Almacena la posicion en la que inserta en cada array
    int index_izq = 0, index_der = 0;

    //Compara y une
    for (int i = inicio*N ; index_izq + index_der < final_izq + final_der ; i++) { 
        //Si no hay elementos en la izquierda, añade derecha
        if(index_izq == final_izq) solucion[i] = arr_der[index_der++];
        //Si hay elementos en la izquierda y no en la derecha
        else if(index_der != final_der)
            //Si la derecha es menor, añade derecha
            if(arr_der[index_der] < arr_izq[index_izq]) solucion[i] = arr_der[index_der++];
            //Si no, añade izquierda
            else solucion[i] = arr_izq[index_izq++];
        // Si hay elementos en la izquierda, añade izquierda
        else solucion[i] = arr_izq[index_izq++];
    } 
}

void dyv(int **T, int *solucion, int inicio, int final, int N, int K) {
    
    //Caso base solo queda 1 array
    if(final == inicio) {
        for(int i = 0 ; i < N ; i++) solucion[inicio*N+i] = T[inicio][i];
    }
    //Si no, recursivo
    else {
        //Divide los arrays
        dyv(T, solucion, inicio, (final+inicio)/2, N, K);      //Arrays a la izquierda
        dyv(T, solucion, (final+inicio)/2+1, final, N, K);     //Arrays a la derecha
        //Une soluciones
        unir_ordenados(inicio, final, solucion, N);
    }
}

int main (int argc, char *argv[]) {

    if(argc != 3) {
        std::cout << "Numero parametros invalido: ./mezcla_bruta n_elem k_vect" << std::endl;
        return 1;
    }

    if(atoi(argv[1]) < 1 || atoi(argv[2]) < 1) {
        std::cout << "Por favor, numeros positivos" << std::endl;
        return 1;
    }

    const int N = atoi(argv[1]); //Tam vector
    const int K = atoi(argv[2]); //Num arrays

    //Reserva memoria matriz
    int **T;
    T = new int *[K];
    assert(T);
    for (int i = 0; i < K; i++) T[i] = new int[N];

    //Reserva memoria array solucion 
    int *solucion = new int[K*N];
    assert(solucion);

    //Declaracion variable tiempo total de ejecucion del algoritmo
    duration<double> suma = steady_clock::duration::zero();
    
    //Ejecuta 5 veces el algoritmo y divide el timpo total entre 5
    for(int p = 0 ; p < 5 ; p++) {
    
        //Genera matriz con algoritmo de Knuth    
        T = generaMatrizT(K, N);

        //Inicializa solucion a valores negativos
        for(int i = 0 ; i < K*N ; i++) solucion[i] = -1;

        //Obtiene el tiempo antes del algoritmo
        high_resolution_clock::time_point tantes, tdespues;
        tantes = high_resolution_clock::now();

        //Ejecucion DyV en base al numero de arrays
        dyv(T, solucion, 0, K-1, N, K);
    
        //Obtiene el tiempo despues del algoritmo
        tdespues = high_resolution_clock::now();
        suma += duration_cast<duration<double>>(tdespues - tantes);
    
    }
    std::cout << K << " " << suma.count()/5 << std::endl;

    return 0;
}

    

