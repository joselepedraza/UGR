/*
    Algoritmo que intena obtener un recubrimiento minimal de un grafo no dirigido
    leido por fichero

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
            grafo: ficheros .gra
    Ejecucion:   ./bin/grafo data/grafo/fichero .gra
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>

using namespace std::chrono;

/**
 * @brief Realiza la lectura de un fichero que contiene la representacion de un grafo. Indicado
 *        en cada de la forma: {nodo} {nodos adyacentes} terminado con ;
 * 
 * @param is Flujo de lectura
 * @param grafo Map que almacena el grafo leido
 * @param N Numero de nodos del grafo
 */
void leerGrafoFichero(std::ifstream &is, std::map<int, std::vector<int>> &grafo, int &N) {
    std::string basura = "";
    if (is) {
        is >> basura; //SOF
        int i = 0 ;
        // Mientras no se llegue a EOF
        while(basura != "EOF") {
            is >> basura;
            // Si es diferente a EOF, es un nodo
            if(basura != "EOF") {
                int nodo_principal = stoi(basura);
                // Cuenta el numero de nodos del grafo
                N++;
                std::vector<int> nodos;
                // Mientras haya nodos adyacentes
                while(basura != ";"){
                    is >> basura;
                    // Si hay mas nodos adyacentes
                    if(basura != ";") nodos.push_back(stoi(basura));
                } 
                grafo[nodo_principal] = nodos;
                i++;
            }
        }
    }
}

/**
 * @brief Muestra un vector por pantalla
 * 
 * @param v Vector a mostrar
 */
void mostrarVector(const std::vector<int> &v) {
    for(int i = 0 ; i < v.size() ; i++) std::cout << v[i] << " ";
    std::cout << std::endl;
}

/**
 * @brief Metodo que reduce el grado de los nodos segun la matriz de adyacencia
 * 
 * @param adyacencia Matriz de adyacencia de un grafo
 * @param nodos Vector que almacena el grado (numero de aristas) de cada nodo de un grafo
 * @param pos Posicion del nodo solucion a reducir
 */
void reduceAdyacente(const std::vector<std::vector<int>> &adyacencia, std::vector<int> &nodos, int pos) {
    // Rebaja el grado de los nodos adyacentes
    for(int j = 0 ; j < nodos.size() ; j++){
        // Se salta nodo solucion Y si el grado del nodo no es 0, reduce el grado en 1
        if(adyacencia[pos][j] && nodos[j]) nodos[j]--;
    }
    // Se establece el grado del nodo solucion a 0
    nodos[pos] = 0;
}

/**
 * @brief Obtiene el recubrimiento minimo de un grafo
 * 
 * @param adyacencia Matriz de adyacencia de un grafo
 * @param nodos Vector con los grados de cada nodo
 * @param solucion Vector con los nodos que recubren el grafo minimalmente
 */
void greedy_grafo(const std::vector<std::vector<int>> &adyacencia, std::vector<int> &nodos, std::vector<int> &solucion) {
    // Recorremos diagonal
    for(int i = 0 ; i < nodos.size() ; i++) {
        // Hay bucle en nodo (a si mismo)
        if(adyacencia[i][i]) {
            // Se añade a solucion
            solucion.push_back(i);
            // Reduce los grados de los nodos adyacentes
            reduceAdyacente(adyacencia, nodos, i);
        }
    }

    int pos, max = -1;
    // Mientras el grado mayor obtenido sea != 0
    while(max) {
        // Recorremos nodos restantes
        max = 0, pos = 0;
        // Para cada candidato
        for(int i = 0; i < nodos.size() ; i++){
            // Se busca el max y se guarda posicion
            if(nodos[i] > max) {
                max = nodos[i];
                pos = i;
            }
        }
        // Si se ha encontrado un max
        if(max) {
            // Se añade a solucion
            solucion.push_back(pos);
            // Reduce los grados de los nodos adyacentes
            reduceAdyacente(adyacencia, nodos, pos);
        }
    }
}

int main(int argc, char *argv[]) {

    // Map que almacena un grafo leido de fichero
    std::map<int, std::vector<int>> grafo;
    // Almacena el numero de nodos del grafo
    int N = 0;

    // Lee el grafo del fichero
    std::string archivo = argv[1];
    std::ifstream is(archivo);
    leerGrafoFichero(is, grafo, N);
    is.close();

    // Matriz de adyacencia de un grafo
    std::vector<std::vector<int>> adyacencia;

    // Inicializacion adyacencia a 0
    for(int i = 0 ; i < N ; i++){
        std::vector<int> datos;
        for(int j = 0 ; j < N ; j++) datos.push_back(0);
        adyacencia.push_back(datos);
    }

    // Indica entre que nodos hay conexion con un 1
    // Para cada nodo
    for (std::map<int,std::vector<int>>::iterator it = grafo.begin(); it != grafo.end(); it++) {
        // Recorre sus adyacencias
        for(int i = 0 ; i < (*it).second.size() ; i++) {
            adyacencia[(*it).first][(*it).second[i]] = 1;
            adyacencia[(*it).second[i]][(*it).first] = 1;
        }
	}

    // Vector que almacena los grados de cada nodo candidato a solucion
    // Nodo candidato es aquel cuyo grafo es > 0
    std::vector<int> nodos; 
    for(int i = 0 ; i < N ; i++) {
        nodos.push_back(0);
        for(int j = 0 ; j < N ; j++) nodos[i]+=adyacencia[i][j]; 
    }

    // Vector que almacena los identificadores de los nodos solucion
    std::vector<int> solucion;

    // Obtiene el tiempo antes del algoritmo
    high_resolution_clock::time_point tantes, tdespues;
    tantes = high_resolution_clock::now();

    // Calcula el recubrimiento minimal de un grafo no dirigido
    greedy_grafo(adyacencia, nodos, solucion);

    // Obtiene el tiempo despues del algoritmo
    tdespues = high_resolution_clock::now();

    // Muestra solucion
    std::cout << "Solucion: ";
    mostrarVector(solucion);
    duration<double> transcurrido = duration_cast<duration<double>>(tdespues - tantes);
    std::cout << "Tiempo: " << transcurrido.count() << std::endl;

    return 0;
}

