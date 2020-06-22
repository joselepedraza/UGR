#include "iostream"
#include "math.h"
#include <chrono>

using namespace std::chrono;

int main (int argc, char * argv[]) {

    if(argc != 2) {
        std::cout << "Parametros erroneos: ./matrix_bruta tam_matrix" << std::endl;
        return 1;
    }

    //Tamaño matrix cuadrada
    int TAM = atoi(argv[1]);

    //Matrix cuadrada
    int **matrix, **transpuesta;
    matrix = new int *[TAM];
    transpuesta = new int *[TAM];
    for (int i = 0 ; i < TAM ; i++) matrix[i] = new int[TAM];
    for (int i = 0 ; i < TAM ; i++) transpuesta[i] = new int[TAM];

    duration<double> suma = steady_clock::duration::zero();
    for(int p = 0 ; p < 5 ; p++) {
        
        //Inicializacion matrix   O(n²)
        for (int i = 0 ; i < TAM ; i++)
            for (int j = 0 ; j < TAM ; j++)      
                matrix[i][j] = (j+1)+(i*TAM);
            
        high_resolution_clock::time_point tantes, tdespues;
        tantes = high_resolution_clock::now();

        //Realizar transpuesta O(n²)
        for(int i = 0 ; i < TAM ; i++)
            for(int j = 0 ; j < TAM ; j++)
                transpuesta[j][i] = matrix[i][j];

        tdespues = high_resolution_clock::now();
        suma += duration_cast<duration<double>>(tdespues - tantes);
    }
    std::cout << TAM << " " << suma.count()/5 << std::endl;

    //Mostrar matrix transpuesta O(n²)
    /*
    for (int i = 0 ; i < TAM ; i++) {
        for (int j = 0 ; j < TAM ; j++)      
            std::cout << transpuesta[i][j] << "\t";
        std::cout << std::endl;
    }
    */

    //Elimina reserva memoria;
    for(int i = 0 ; i < TAM ; i++) delete[] transpuesta[i];;
    delete[] transpuesta;

    return 0;
}