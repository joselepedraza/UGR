/*
    Algoritmo que obtiene una solucion greedy mediante 
    la heuristica del vecino mas cercano de un archivo .tsp

    Alumno1: Jose Luis Pedraza Román
    Alumno2: Pedro Checa Salmerón
    Alumno3: Antonio Carlos Perea Parras
    Alumno4: Raúl Del Pozo Moreno

    UGR - ETSIIT - GII - Algoritmica - B1 - Grupo “Oliva”

    Compilacion: Se adjunta Makefile
    Estructura de carpetas:
        src: ficheros fuente
        bin: ficheros binarios
        data:
            tsp_escenarios: ficheros .tsp
    Ejecucion:   ./bin/tsp_vmc data/tsp_escenarios/fichero.tsp
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <chrono>
#include <map>
#include <string>

using namespace std::chrono;

/**
 * @brief Estructura de datos que almacena una ciudad, mediante su identificador (n) y sus coordenadas (x, y)
 * 
 */
struct Ciudad {
    int n = -1;
    std::pair<double,double> coordenadas =  std::make_pair(-1.0,-1.0);
};

/**
 * @brief Lee datos de un fichero de texto .tsp
 * 
 * @param is Flujo de entrada
 * @param ciudades Struct que almacena el identificador de la ciudad y sus coordenadas
 */
void leerFicheroTSP(std::ifstream &is, std::vector<Ciudad> &ciudades) {
    
    std::string basura = "";
    if (is) {
        int dimension = 0;
        // Leer hasta coordenadas
        while (basura != "NODE_COORD_SECTION") {
            is >> basura;
            // Si encuentra la dimension, la añade
            if (basura == "DIMENSION:") is >> dimension;
        }
        // Aqui empezamos a añadir al vector
        for(int i = 0 ; i < dimension ; i++) {
            Ciudad city;
            is >> city.n;
            is >> city.coordenadas.first;
            is >> city.coordenadas.second;
            ciudades.push_back(city);
        }
    }
}

/**
 * @brief Muestra el contenido de un vector por pantalla
 * 
 * @param v El vector a mostrar
 */
void mostrarVector(const std::vector<Ciudad> &v) {
    for(int i = 0 ; i < v.size() ; i++)
        std::cout << v[i].n << " " << v[i].coordenadas.first << " " << v[i].coordenadas.second << std::endl;
    std::cout << std::endl;
}

/**
 * @brief Muestra el contenido de una matriz cuadrada
 * 
 * @param matriz La matriz a mostrar
 * @param N El tamaño de la matriz 
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
 * @brief Calcula la distancia truncada entre dos ciudades
 * 
 * @param city1 Ciudad 1
 * @param city2 Ciudad 2
 * @return int Distancia truncada ( 4.5 -> 4 || 4.6 -> 5)
 */
int distancia(Ciudad city1, Ciudad city2) {
    // Calcula la distancia
    double d = sqrt(pow(city2.coordenadas.first-city1.coordenadas.first, 2)+pow(city2.coordenadas.second-city1.coordenadas.second, 2));
    // Redondea
    int ent = d/1;
    return (((d-ent) < 0.5) ? ent : ent+1);
}

/**
 * @brief Calcula la distancia a cada ciudad visitada incluyendo retorno
 * 
 * @param ruta Vector que almacena el orden de las ciudades a visitar
 * @return int Distancia de toda la ruta
 */
int distanciaTotal(const std::vector<Ciudad> &ruta) {
    int d = 0;
    for(int i = 0 ; i < ruta.size() ; i++) d += distancia(ruta[i+1], ruta[i]);
    return d;
}

/**
 * @brief Genera una matriz con las distancias entre las ciudades, una distancia 0 
 *        indica que la ciudad se refiere a si misma
 * 
 * @param ciudades Las ciudades a visitar
 * @param N El numero de ciudades
 * @param matriz Matriz de distancias
 */
void generarMatrizDistancias(std::vector<Ciudad> ciudades, int N, int **matriz) {

    // Cada ciudad con si misma no tiene distancia --> d = 0
    for(int i = 0 ; i < N ; i++) matriz[i][i] = 0;
    
    // Calcula distancias con otras ciudades
    // Recorre matriz superior (sin diagonal principal)
    for(int i = 0 ; i < N-1 ; i++)
        for(int j = i+1 ; j < N ; j++) {
            matriz[i][j] = distancia(ciudades[i], ciudades[j]);
            matriz[j][i] = matriz[i][j];
        }
}


int recursiva(int contador, int nodo_actual, int nodo_anterior, int **matriz, std::vector<int> sinVisitar, std::map<std::string, int> &mapa) {

    
    std::cout << "N " << sinVisitar[nodo_actual] << std::endl;
    if(nodo_anterior != -1) std::cout << "\tD (" << nodo_anterior+1 << "," << nodo_actual+1 << ") = " << matriz[nodo_actual][nodo_anterior] << std::endl;

    // Actualiza el nodo visitado a -3
    // Mantiene los indices y evita redimensionar vector
    sinVisitar[nodo_actual] = -3;
    contador++;

    int min , d = 0, d_t = 0;

    // Nodo hoja, calcula retorno
    if(contador == sinVisitar.size()) {
        d_t = matriz[nodo_actual][nodo_anterior] + matriz[nodo_actual][0];
    }
    else {
        min = 99999;
        // Para cada ciudad sin visitar
        for(int i = 0 ; i < sinVisitar.size() ; i++) {
            // Se salta las ciudades visitadas
            if(sinVisitar[i] != -3) {
                // LLamada recursiva
                d = recursiva(contador, i,  nodo_actual, matriz, sinVisitar, mapa);
                if(min > d) min = d;
            }
        }

        // Calcula la distancia acumulada con el nodo padre
        d_t = matriz[nodo_actual][nodo_anterior] + min;
        
        std::cout << "Suma total: " << matriz[nodo_actual][nodo_anterior] << " " << min << " = " << d_t << std::endl;
        std::cout << std::endl;
    }

    return d_t;

}

/**
 * @brief Calcula la ruta del viajante de comercia mediante programacion dinamica
 * 
 * @param ciudades Las ciudades a visitar
 * @param solucion La ruta a seguir
 */
// Bottom-Top
int pd(std::vector<Ciudad> ciudades, std::vector<Ciudad> &solucion, int **matriz, int N, std::map<std::string, int> &mapa) {

    //N-1 indica el nivel (Numero ciudades - 1)
    //N-1 indica el numero de ciudades a las que puede ir la ciudad actual
    // Se intenta recursividad de avance
    /*
        https://www.ingenieria.unam.mx/sistemas/PDF/Avisos/Seminarios/SeminarioV/Sesion6_IdaliaFlores_20abr15.pdf
        Recursividad de Avance:elproblemaseresuelvepartiendodelaprimeraetapahacialaúltima.
    */

    mostrarMatriz(matriz, N);
    std::cout << std::endl;
    std::vector<int> sinVisitar;
    for(int i = 0 ; i < N ; i++) sinVisitar.push_back(ciudades[i].n);


    int d = recursiva(0, 0, -1, matriz, sinVisitar, mapa);

    return d;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "Numero de parametros erroneos, debe indicar el fichero de ciudades" << std::endl;
        return 1;
    }
    
    // Vector donde sea almacenan las ciudades
    std::vector<Ciudad> ciudades;

    // Leer archivo tsp
    std::string archivo = argv[1];
    std::ifstream is(archivo);
    leerFicheroTSP(is, ciudades);
    is.close();

    // Cantidad de ciudades
    int N = ciudades.size();

    // Matriz que almacena las distancias entre las ciudades
    int **matriz;
    matriz = new int* [N];
    for(int i = 0 ; i < N ; i++) matriz[i] = new int[N];
    
    // Generar matriz de distancias
    generarMatrizDistancias(ciudades, N, matriz);

    // Vector que almacena la solucion
    std::vector<Ciudad> solucion;

    std::map<std::string, int> mapa;

    // Obtiene el tiempo antes del algoritmo
    high_resolution_clock::time_point tantes, tdespues;
    tantes = high_resolution_clock::now();

    // Calcula la ruta por el vecino mas cercano
    int d = 0 ;
    d = pd(ciudades, solucion, matriz, N, mapa);
    
    // Obtiene el tiempo despues del algoritmo
    tdespues = high_resolution_clock::now();

    // Muestra solucion
    mostrarVector(solucion);

    //Muestra la distancia de la solucion    
    std::cout << "Distancia: " << d << std::endl;
    duration<double> transcurrido = duration_cast<duration<double>>(tdespues - tantes);
    std::cout << "Tiempo: " << transcurrido.count() << std::endl;

    for(int i = 0 ; i < N ; i++) delete[] matriz[i];
    delete[] matriz;

    return 0;
}