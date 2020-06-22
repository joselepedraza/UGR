/*
    Algoritmo que obtiene una solucion mediante 
    backtracking del problema de la cena de gala.

    Alumno1: Jose Luis Pedraza Román
    Alumno2: Pedro Checa Salmerón
    Alumno3: Antonio Carlos Perea Parras
    Alumno4: Raúl Del Pozo Moreno

    UGR - ETSIIT - GII - Algoritmica - B1 - Grupo “Oliva”

    Compilacion: Se adjunta Makefile
    Estructura de carpetas:
        src: ficheros fuente
        bin: ficheros binarios
    Ejecucion:   ./bin/cena tamaño
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <chrono>
using namespace std::chrono;

/**
 * @brief Estructura que almacena el identificador de un comensal y la conveniencia acumulada
 * que hay de todos los comensales previamente sentados
 * 
 */
struct Comensal {
    int id;
    int conveniencia;
};

/**
 * @brief Lee un fichero que almacena una matriz de conveniencia
 * 
 * @param is El fichero, la primera linea indica el tamaño de la matriz, a continuacion, cada
 * fila indica la conveniencia de un comensal con el resto. La matriz es cuadrada.
 * @param matriz La matriz donde se almacena la conveniencia leida
 */
void leerFicheroCena(std::ifstream &is, int **matriz) {

    if (is) {
        int N = 0;
        is >> N;
        for (int i = 0 ; i < N ; i++)
            for(int j = 0 ; j < N ; j++)
                is >> matriz[i][j];
    }
}

/**
 * @brief Genera una matriz de conveniencia aleatoria. La matriz es cuadrada.
 * 
 * @param matriz La matriz que almacena la conveniencia
 * @param N Tamaño de la matriz
 */
void generaMatriz(int **matriz, int N) {
    for(int i = 0 ; i < N ; i++) matriz[i][i] = 0;
    
    for(int i = 0 ; i < N-1 ; i++)
        for(int j = i+1 ; j < N ; j++) {
            matriz[i][j] = rand()%101;
            matriz[j][i] = rand()%101;
        }
}

/**
 * @brief Muestra una matriz por pantalla indicando el comensal de cada fila/columna
 * 
 * @param matriz 
 * @param N 
 */
void mostrarMatriz(int **matriz, int N) {
    std::cout << "    ";
    for(int i = 0 ; i < N ; i++)  std::cout << i+1 << "\t"; 
    std::cout << std::endl;
    for(int i = 0 ; i < N ; i++) {
        std::cout << i+1 << " : ";
        for(int j = 0 ; j < N ; j++) std::cout << matriz[i][j] << "\t";
        std::cout << std::endl;
    }
}

/**
 * @brief Metodo recursivo que calcula mediante backtracking una solucion al problema de la cena de gala.
 * 
 * @param solucion Vector que almacena la solucion del problema
 * @param solucion_parcial Vector que almacena una solucion parcial
 * @param candidatos Vector de candidatos, indica los comensales que quedan por sentarse en cada momento.
 * @param contador Identifica si es un nodo hoja, lleva la cuenta de cuantos candidatos quedan por sentarse
 * @param nodo_actual Nodo que identifica al comensal que se evalua
 * @param matriz Matriz de conveniencia entre comensales
 * @param N Numero de comensales
 */
void backtracking(std::vector<Comensal> &solucion, std::vector<Comensal> solucion_parcial, std::vector<int> candidatos, int contador, Comensal nodo_actual, int **matriz, int N) {

    // Marca el comensal evaluado
    candidatos[nodo_actual.id] = -3;
    contador--;

    // Se añade al vector temporal solucion
    solucion_parcial.push_back(nodo_actual);

    // Nodo Hoja
    if(!contador) {
        // Se añade la vuelta
        Comensal n;
        n.id = solucion_parcial[0].id;
        n.conveniencia = matriz[nodo_actual.id][n.id] + matriz[n.id][nodo_actual.id] + nodo_actual.conveniencia;
        // Se añade el comensal a solucion temporal
        solucion_parcial.push_back(n);
        // Se comprueba
        if(solucion[solucion.size()-1].conveniencia < solucion_parcial[N].conveniencia) solucion = solucion_parcial;
    }
    // Nodo NO Hoja
    else {
        // Para cada comensal restante
        for(int i = 0 ; i < N ; i++) {
            if(candidatos[i] != -3) {
                Comensal n;
                n.id = i;
                // Suma de lo anterior mas la conveniencia mutua
                n.conveniencia = matriz[nodo_actual.id][n.id] + matriz[n.id][nodo_actual.id] + nodo_actual.conveniencia;
                // Comprobar si la conveniencia es factible (factibilidad)
                if( (n.conveniencia + 200*contador) >= solucion[solucion.size()-1].conveniencia) 
                    backtracking(solucion, solucion_parcial, candidatos, contador, n, matriz, N);
            }
        }
    }
}

int main(int argc, char *argv[]) {


    if (argc != 2) {
        std::cout << "El programa necesita el numero de comensales" << std::endl;
        return 1;
    }

    // Cantidad de comensales
    int N = std::stoi(argv[1]);
    
    // Vector que almacena la secuencia de comensales adyacentes
    std::vector<Comensal> solucion;
    std::vector<Comensal> solucion_parcial;

    // Vector de candidatos
    std::vector<int> candidatos;
    for(int i = 0 ; i < N ; i++) candidatos.push_back(i);

    // Matriz de conveniencia
    int **matriz;
    matriz = new int*[N];
    for (int j = 0 ; j < N ; j++)
    matriz[j] = new int[N];

    high_resolution_clock::time_point tantes, tdespues;
    duration<double> ttotal = steady_clock::duration::zero();

    // Realiza la ejecucion con 5 matrices aleatorias
    srand(time(NULL));
    for(int i = 0 ; i < 5 ; i++) {

        //Genera matriz aleatoria
        generaMatriz(matriz, N);

        // Inicializa la solucion
        Comensal c;
        c.id = 0;
        c.conveniencia = 0;
        solucion.push_back(c);

        // Obtiene el tiempo antes del algoritmo
        tantes = high_resolution_clock::now();

        // LLamada recursiva que calcula backtracking
        backtracking(solucion, solucion_parcial, candidatos, N, c, matriz, N);

        // Obtiene el tiempo despues del algoritmo
        tdespues = high_resolution_clock::now();
        ttotal += (duration_cast<duration<double>>(tdespues - tantes));

        // Muestra solucion
        //std::cout << "Solucion: ";
        //for(int j = 0 ; j < solucion.size() ; j++) std::cout << solucion[j].id+1 << " ";
        //std::cout << std::endl;
        //std::cout << "Conveniencia: " << solucion[N].conveniencia << std::endl;

        // Limpia la solucion
        solucion.clear();
    }
    
    // Muestra numero de comensales y el tiempo que ha tardado el algoritmo
    std::cout << "Comensales: " << N << std::endl;
    std::cout << "Tiempo: " << ttotal.count()/5 << std::endl;
}