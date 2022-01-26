/*
    Algoritmo que realiza la traspuesta de una matriz cuadrada
    de tamaño n=2^k mediante fuerza bruta

    Alumno1: Jose Luis Pedraza Román
    Alumno2: Pedro Checa Salmerón
    Alumno3: Antonio Carlos Perea Parras
    Alumno4: Raúl Del Pozo Moreno

    UGR - ETSIIT - GII - Algoritmica - B1 - Grupo “Oliva”

    Los archivos .cpp tienen que estar en una carpeta "src" 
    y los archivos binarios en una carpeta "bin"
    Compilar en la ruta que contiene dichas carpetas.

    Compilacion: g++ -std=gnu++0x src/matrix_bruta.cpp -o bin/matrix_bruta
    Ejecucion:   ./bin/matrix_bruta K
    K = tamaño matriz (2^K)

    Ejemplo: K=3 genera una matriz de 8*8  (2^3 * 2^3)

*/

#include "iostream"
#include "math.h"
#include <chrono>

using namespace std::chrono;

int main (int argc, char * argv[]) {

    if(argc != 2) {
        std::cout << "Parametros erroneos: ./matriz_bruta tamaño_matriz" << std::endl;
        return 1;
    }

    //Tamaño matriz cuadrada
    int TAM = pow(2, atoi(argv[1]));

    //Matriz cuadrada
    int **matriz;
    matriz = new int *[TAM];
    for (int i = 0 ; i < TAM ; i++) matriz[i] = new int[TAM];
    
    //Declaracion variable tiempo total de ejecucion del algoritmo
    duration<double> suma = steady_clock::duration::zero();

    //Ejecuta 5 veces el algoritmo y divide el timpo total entre 5
    for(int p = 0 ; p < 5 ; p++) {
        
        //Inicializa la matriz con valores del 1 a TAM
        for (int i = 0 ; i < TAM ; i++)
            for (int j = 0 ; j < TAM ; j++)      
                matriz[i][j] = (j+1)+(i*TAM);

        //Obtiene el tiempo antes del algoritmo
        high_resolution_clock::time_point tantes, tdespues;
        tantes = high_resolution_clock::now();

        //Realiza traspuesta recorriendo la matriz inferior
        for(int i = 0 ; i < TAM-1 ; i++)
            for(int j = i+1 ; j < TAM ; j++) {
                int aux = matriz[j][i];
                matriz[j][i] = matriz[i][j];
                matriz[i][j] = aux;
            }

        //Obtiene el tiempo despues del algoritmo
        tdespues = high_resolution_clock::now();
        //Suma el tiempo total
        suma += duration_cast<duration<double>>(tdespues - tantes);
    }
    //Muestra el tamaño del problema y media del tiempo
    std::cout << TAM << " " << suma.count()/5 << std::endl;

    //Elimina memoria
    for(int i = 0 ; i < TAM ; i++) delete[] matriz[i];
    delete[] matriz;

    return 0;
}