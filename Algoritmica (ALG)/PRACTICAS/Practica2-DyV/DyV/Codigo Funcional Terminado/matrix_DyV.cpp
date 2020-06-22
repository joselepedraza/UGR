#include "iostream"
#include "math.h"
#include <chrono>

using namespace std::chrono;

void mostrar(int **matrix, int F_inicial, int C_inicial, int F_total, int C_total) {
    for(int i = 0 ; i < F_total ; i++) {
        for(int j = 0 ; j < C_total ; j++) {
            std::cout << matrix[F_inicial+i][C_inicial+j] << "\t";
        }
        std::cout << std::endl;
    }
	std::cout << std::endl;
}

void dyv(int **matrix, int **traspuesta, int F_inicial, int C_inicial, int F_total, int C_total, int F_destino, int C_destino) {
	
	//Caso base 1 Fila 1 Columna
    if((F_total == 1)&&(C_total == 1)) {
		traspuesta[F_destino][C_destino] = matrix[F_inicial][C_inicial];
	}
    // Caso base 1 Fila X columnas (No cuadrada)
    else if(F_total == 1){
		for (int i = 0 ; i < C_total ; i++)
        	traspuesta[F_destino][C_destino+i] = matrix[F_inicial+i][C_inicial];
	}
    // Caso base 1 Columna X Filas (No cuadrada)
    else if(C_total == 1){
		for (int i = 0 ; i < F_total ; i++) 
        	traspuesta[F_destino+i][C_destino] = matrix[F_inicial][C_inicial+i];
	}
    // Caso recursivo
    //Cuadrantes: dyv(matriz, traspuesta, fil inicial, col inicial, fil totales, col totales, fil de destino, col de destino)
    else{
		//Cuadrante 1
    	dyv(matrix, traspuesta, F_inicial, C_inicial, F_total/2, C_total/2, F_destino, C_destino);
		//Cuadrante 2: se intercambia el destino con el cuadrante 3
    	dyv(matrix, traspuesta, F_inicial, (C_inicial + (C_total/2)), (F_total - F_total/2), C_total/2, (F_destino + (F_total/2)), C_destino);
		//Cuadrante 3: se intercambia el destino con el cuadrante 2
    	dyv(matrix, traspuesta, (F_inicial + (F_total/2)), C_inicial, F_total/2, (C_total - C_total/2), F_destino, (C_destino + (C_total/2)));
		//Cuadrante 4
    	dyv(matrix, traspuesta, (F_inicial + (F_total/2)), (C_inicial + (C_total/2)), (F_total - F_total/2), (C_total - C_total/2), (F_destino + (F_total/2)), (C_destino + (C_total/2)));
    }
}

int main (int argc, char * argv[]) {

    if(argc != 2) {
        std::cout << "Parametros erroneos: ./matrix_DyV tam_matrix" << std::endl;
        return 1;
    }

    //Tamaño matrix cuadrada
    int TAM = atoi(argv[1]);

    //Matrix cuadrada
    int **matrix;
	int **traspuesta;
    matrix = new int *[TAM];
    traspuesta = new int *[TAM];
    for (int i = 0 ; i < TAM ; i++) {
        matrix[i] = new int[TAM];
        traspuesta[i] = new int[TAM];
    }
    
    duration<double> suma = steady_clock::duration::zero();
    for(int p = 0 ; p < 5 ; p++) {
        //Inicializacion matrix   O(n²)
        for (int i = 0 ; i < TAM ; i++)
            for (int j = 0 ; j < TAM ; j++)      
                matrix[i][j] = (j+1)+(i*TAM);
            
        //Toma de tiempos de ejecucion DyV
        high_resolution_clock::time_point tantes, tdespues;
        tantes = high_resolution_clock::now();

        //Realizar traspuesta O()
        dyv(matrix, traspuesta, 0, 0, TAM, TAM, 0, 0);

        //Toma de tiempos de ejecucion DyV
        tdespues = high_resolution_clock::now();
        suma += duration_cast<duration<double>>(tdespues - tantes);
    }
    std::cout << TAM << " " << suma.count()/5 << std::endl;


    //Eliminar memoria
    for(int i = 0 ; i < TAM ; i++) {
        delete[] matrix[i];
        delete[] traspuesta[i];
    }
    delete[] matrix;
    delete[] traspuesta;

    return 0;
}