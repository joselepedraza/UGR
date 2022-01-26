/*
    Algoritmo que intena obtener un recubrimiento minimal de un arbol
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
            arbol: ficheros .arb
    Ejecucion:   ./bin/arbol data/arbol/fichero .arb
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>

using namespace std::chrono;

/**
 * @brief Realiza la lectura de un fichero que contiene la representacion de un arbol. Indicado
 *        en cada de la forma: {nodo} {nodos hijos} terminado con ;
 *        (se indica solamente el nodo padre y sus hijos, si un nodo no tiene hijos, se representa como hijo de otro)
 * 
 * @param is Flujo de lectura
 * @param arbol Map que almacena la representacion del arbol
 * @param N Numero de nodos
 */
void leerArbolFichero(std::ifstream &is, std::map<int, std::vector<int>> &arbol, int &N) {
    std::string basura = "";
    if (is) {
        is >> basura; //SOF
        int i = 0 ;
        // Mientras no se llegue a EOF
        while(basura != "EOF") {
            is >> basura;
            // Si es diferente a EOF, es un nodo
            if(basura != "EOF") {
                int padre = stoi(basura);
                std::vector<int> hijos;
                // Mientras haya nodos adyacentes
                while(basura != ";"){
                    is >> basura;
                    // Si hay mas nodos adyacentes
                    if(basura != ";") {
                        // Cuenta el numero de nodos
                        N++; 
                        hijos.push_back(stoi(basura));
                    }
                } 
                arbol[padre] = hijos;
                i++;
            }
        }
    }
    // Cuenta el nodo raiz
    N++;
}

/**
 * @brief Muestra la matriz de adyacencia de un arbol por pantalla
 * 
 * @param adyacencia Matriz de adyacencia
 */
void mostrarAdyancencia(const std::vector<std::vector<int>> &adyacencia) {
    for(int i = 0 ; i < adyacencia.size() ; i++) {
        for(int j = 0 ; j < adyacencia.size() ; j++)
            std::cout << adyacencia[i][j] << " ";
        std::cout << std::endl;
    }
}

/**
 * @brief Muestra el contenido del arbol indicando cada nodo padre y sus hijos
 * 
 * @param arbol Arbol a mostrar
 */
void mostrarArbol(const std::map<int, std::vector<int>> &arbol) {
    for (std::map<int,std::vector<int>>::const_iterator it = arbol.begin(); it != arbol.end(); it++) {
        std::cout << "Padre: " << it->first << " Hijos: ";
        for(int i = 0 ; i < (*it).second.size() ; i++) std::cout << (*it).second[i] << " ";
        std::cout << std::endl;
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
 * @param adyacencia Matriz de adyacencia de un arbol
 * @param nodos Vector con el grado de cada nodo
 * @param pos Posicion del nodo insertado como solucion
 */
void reduceAdyacente(const std::vector<std::vector<int>> &adyacencia, std::vector<int> &nodos, int pos) {
    // Rebaja el grado de los nodos adyacentes
    for(int j = 0 ; j < nodos.size() ; j++){
        // Se salta nodo solucion Y si el nodo adyacente tiene grado > 0 
        if(adyacencia[pos][j] && nodos[j]) nodos[j]--;
    }
    nodos[pos] = 0;
}

/**
 * @brief Obtiene el recubrimiento minimo de un arbol
 * 
 * @param adyacencia Matriz de adyacencia de un arbol
 * @param nodos Vector con los grados de cada nodo
 * @param solucion Vector con los nodos que recubren el arbol minimalmente
 */
void greedy_arbol(const std::vector<std::vector<int>> &adyacencia, std::vector<int> &nodos, std::vector<int> &solucion) {
    // Almacena la posicion del nodo solucion
    int pos = 0;
    // Indica cuando hay que seguir comprobando nodos
	bool sigue;

    // Mientras haya nodos con grado 1
	while(pos < nodos.size()){
        // Si el nodo tiene grado 1 (hoja) o (padre) si el nodo solo
        // esta conectado a otro nodo de grado 1
		if(nodos[pos] == 1){            
			sigue = true;
            int padre = -1;
            // Busca el padre
			for(int i = 0; i < adyacencia.size() && sigue; i++){
                // Se busca el padre (i) de un nodo (pos)
				if(adyacencia[pos][i]==1 ){
                    bool encontrado = false;
                    // Busca 
                    for(int j = 0 ; j < solucion.size() && !encontrado ; j++)
                        // Si el padre ya esta en la solucion, se ignora
                        if (i == solucion[j]) encontrado = true;
                    // Si no encuentra el padre en la solucion, se asigna como el padre
                    if(!encontrado) {
                        padre = i;
                        sigue = false;
                    }
				}
			}
            // Se añade a la solucion el nodo
            solucion.push_back(padre);
            // Se reducen los grados de los nodos adyacentes
			reduceAdyacente(adyacencia, nodos, padre);
            // Se reinicializa la busqueda
			pos = -1;
		}
        // Se pasa al siguiente nodo
		pos++;
	} 
}

int main(int argc, char *argv[]) {

    // Map que almacena la representacion de un arbol
    std::map<int, std::vector<int>> arbol;
    // Indica el numero de nodos del arbol
    int N = 0;

    // Lee el arbol de un fichero
    std::string archivo = argv[1];
    std::ifstream is(archivo);
    leerArbolFichero(is, arbol, N);
    is.close();
    
    // Matriz de adyacencia
    std::vector<std::vector<int>> adyacencia;
    
    // Inicializacion adyacencia a 0
    for(int i = 0 ; i < N ; i++){
        std::vector<int> datos;
        for(int j = 0 ; j < N ; j++) datos.push_back(0);
        adyacencia.push_back(datos);
    }

    // Indica entre que nodos hay conexion con un 1
    // Para cada nodo
    for (std::map<int,std::vector<int>>::iterator it = arbol.begin(); it != arbol.end(); it++) {
        // Recorre los nodos
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

    // Vector que almacena la solucion
    std::vector<int> solucion;

    // Obtiene el tiempo antes del algoritmo
    high_resolution_clock::time_point tantes, tdespues;
    tantes = high_resolution_clock::now();

    // Calcula el recubrimiento minimal del arbol
    greedy_arbol(adyacencia, nodos, solucion);

    // Obtiene el tiempo despues del algoritmo
    tdespues = high_resolution_clock::now();

    // Muestra la solucion
    std::cout << "Solucion: ";
    mostrarVector(solucion);
    duration<double> transcurrido = duration_cast<duration<double>>(tdespues - tantes);
    std::cout << "Tiempo: " << transcurrido.count() << std::endl;

    return 0;
}

