/*
    Algoritmo que realiza la traspuesta de una matriz cuadrada
    de tamaño n=2^k mediante divide y venceras

    Alumno1: Jose Luis Pedraza Román
    Alumno2: Pedro Checa Salmerón
    Alumno3: Antonio Carlos Perea Parras
    Alumno4: Raúl Del Pozo Moreno

    UGR - ETSIIT - GII - Algoritmica - B1 - Grupo “Oliva”

    Los archivos .cpp tienen que estar en una carpeta "src" 
    y los archivos binarios en una carpeta "bin"
    Compilar en la ruta que contiene dichas carpetas.

    Compilacion: g++ -std=gnu++0x src/matrix_DyV.cpp -o bin/matrix_DyV
    Ejecucion:   ./bin/matrix_DyV K
    K = tamaño matriz (2^K)

    Ejemplo: K=3 genera una matriz de 8*8  (2^3 * 2^3)

*/

#include "iostream"
#include "math.h"
#include <chrono>

using namespace std::chrono;

/**
 * @brief Metodo recursivo que realiza la traspuesta de una matriz
 * 
 * @param matriz Matriz con valores a trasponer
 * @param traspuesta Solucion con la traspuesta de la matriz
 * @param F_inicial Fila en la que empieza cada submatriz recursiva
 * @param C_inicial Columna en la que empieza cada submatriz recursiva
 * @param F_total Numero de filas totales de la submatriz recursiva
 * @param C_total Numero de columnas totales de la submatriz recursiva
 * @param F_destino Fila en la que termina cada submatriz recursiva
 * @param C_destino Columna en la que termina cada submatriz recursiva
 */
void dyv(int **matriz, int **traspuesta, int F_inicial, int C_inicial, int F_total, int C_total, int F_destino, int C_destino) {
	
	//Caso base: 1 Fila 1 Columna
    if((F_total == 1)&&(C_total == 1))
        traspuesta[F_destino][C_destino] = matriz[F_inicial][C_inicial];
    //Caso recursivo
    else{
        //Cuadrante 1
    	dyv(matriz, traspuesta, F_inicial, C_inicial, F_total/2, C_total/2, F_destino, C_destino);
        //Cuadrante 2: se intercambia el destino con el cuadrante 3
        dyv(matriz, traspuesta, F_inicial, (C_inicial + (C_total/2)), (F_total - F_total/2), C_total/2, (F_destino + (F_total/2)), C_destino);
        //Cuadrante 3: se intercambia el destino con el cuadrante 2
        dyv(matriz, traspuesta, (F_inicial + (F_total/2)), C_inicial, F_total/2, (C_total - C_total/2), F_destino, (C_destino + (C_total/2)));
        //Cuadrante 4
        dyv(matriz, traspuesta, (F_inicial + (F_total/2)), (C_inicial + (C_total/2)), (F_total - F_total/2), (C_total - C_total/2), (F_destino + (F_total/2)), (C_destino + (C_total/2)));
    }
}

int main (int argc, char * argv[]) {

    if(argc != 2) {
        std::cout << "Parametros erroneos: ./matriz_DyV tam_matriz" << std::endl;
        return 1;
    }

    //Tamaño matriz cuadrada
    int TAM = pow(2, atoi(argv[1]));

    //Reserva memoria matriz inicial y matriz traspuesta
    int **matriz;
	int **traspuesta;
    matriz = new int *[TAM];
    traspuesta = new int *[TAM];
    for (int i = 0 ; i < TAM ; i++) {
        matriz[i] = new int[TAM];
        traspuesta[i] = new int[TAM];
    }

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

        //Realizar traspuesta 
        dyv(matriz, traspuesta, 0, 0, TAM, TAM, 0, 0);

        //Obtiene el tiempo despues del algoritmo
        tdespues = high_resolution_clock::now();
        suma += duration_cast<duration<double>>(tdespues - tantes);
    }
    std::cout << TAM << " " << suma.count()/5 << std::endl;

    //Elimina memoria
    for(int i = 0 ; i < TAM ; i++) {
        delete[] matriz[i];
        delete[] traspuesta[i];
    }
    delete[] matriz;
    delete[] traspuesta;

    return 0;
}