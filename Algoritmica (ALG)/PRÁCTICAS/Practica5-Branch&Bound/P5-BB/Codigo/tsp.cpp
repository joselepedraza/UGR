/*
    Algoritmo que obtiene una solucion mediante 
    branch and bound en el problema del viajante de comercio.

    Alumno1: Jose Luis Pedraza Román
    Alumno2: Pedro Checa Salmerón
    Alumno3: Antonio Carlos Perea Parras
    Alumno4: Raúl Del Pozo Moreno

    UGR - ETSIIT - GII - Algoritmica - B1 - Grupo “Oliva”

    Compilacion: Se adjunta Makefile
    Estructura de carpetas:
        src: ficheros fuente
        bin: ficheros binarios
    Ejecucion:   ./bin/tsp data/tsp/fichero.tsp
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <string>
#include <queue>
#include <chrono>
using namespace std::chrono;

/**
 * @brief Estructura que representa una ciudad, almacena su identificador y sus coordenadas
 * 
 */
struct Ciudad {
    int n = -1;
    std::pair<double,double> coordenadas =  std::make_pair(-1.0,-1.0);
};

/**
 * @brief Lee un fichero que almacena un conjunto de ciudades
 * 
 * @param is Fichero de entrada
 * @param ciudades Vector donde se almacenan las ciudades leidas
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
 * @brief Muestra un conjunto de ciudades a partir de un vector de ciudades y una ruta con los identificadores de cada ciudad
 * 
 * @param v Vector con las coordenadas de las ciudades
 * @param sol Vector con los identificadores de las ciudades
 */
void mostrarVector(const std::vector<Ciudad> &v, const std::vector<int> &sol) {
    for(int i = 0 ; i < sol.size() ; i++)
        std::cout << v[sol[i]].n << " " << v[sol[i]].coordenadas.first << " " << v[sol[i]].coordenadas.second << std::endl;
    std::cout << std::endl;
}

/**
 * @brief Muestra una matriz por pantalla
 * 
 * @param matriz Matriz a mostrar
 * @param N Tamaño de la matriz
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
 * @brief Calcula la distancia euclidea entre dos ciduades
 * 
 * @param city1 Ciudad 1
 * @param city2  Ciudad 2
 * @return int Distancia redondeada entre las ciudades
 */
int distancia(Ciudad city1, Ciudad city2) {
    // Calcula la distancia
    double d = sqrt(pow(city2.coordenadas.first-city1.coordenadas.first, 2)+pow(city2.coordenadas.second-city1.coordenadas.second, 2));
    // Redondea
    int ent = d/1;
    return (((d-ent) < 0.5) ? ent : ent+1);
}

/**
 * @brief Obtiene la distancia total de una ruta de ciudades
 * 
 * @param ruta Vector con las ciudades
 * @return int Distancia de la ruta
 */
int distanciaTotal(const std::vector<Ciudad> &ruta) {
    int d = 0;
    for(int i = 0 ; i < ruta.size() ; i++) d += distancia(ruta[i+1], ruta[i]);
    return d;
}

/**
 * @brief Genera una matriz de distancias entre ciudades simetrica
 * 
 * @param ciudades Ciudades a representar
 * @param N Tamaño de la matriz de distancias
 * @param matriz Matriz de distancias que se crea
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

/**
 * @brief Representa una ciudad con un coste, un recorrido solucion parcial, 
 * un conjunto de candidatos a evaluar, un contador de candidatos evaluados
 * y el numero de candidatos.
 * 
 */
struct Nodo {
    int id;
    int coste;
    std::vector<int> recorrido;
    std::vector<int> candidatos;
};

/**
 * @brief Estructura que compara dos nodos segun su coste al insertarlos en la cola con prioridad
 * 
 */
struct Comparador {
    bool operator() (const Nodo &n1, const Nodo &n2) const {
        return (n1.coste > n2.coste);
        
    }
};

// Funciones para obtener una solucion greedy inicial
//**********************************

/**
 * @brief Calcula el aumento de distancia que hay al insertar una ciudad entre otras dos
 * 
 * @param city1 Ciudad 1
 * @param city2 Ciudad 2
 * @param city3 Ciudad 3
 * @return int Distancia de la subruta
 */
int aumentoDistancia(Ciudad city1, Ciudad city2, Ciudad city3){
	return (distancia(city1, city2) + distancia(city1, city3) - distancia(city2, city3));
}

/**
 * @brief Ordena la solucion segun los pares visitados
 * 
 * @param solucion Vector que almacena la solucion ordenada 
 * @param visitadas Vector de pares que almacena la solucion
 */
void ordenarSolucion(std::vector<Ciudad> &solucion, std::vector<std::pair<Ciudad, Ciudad>> &visitadas) {
	// Inicializa la solucion
	solucion.push_back(visitadas[0].first);
    solucion.push_back(visitadas[0].second);
	// Guarda la ciudad a buscar en los pares
    Ciudad auxC = visitadas[0].second;
	// Elimina la ciudad visitada
	visitadas.erase(visitadas.begin());

    // Mientras haya ciudades visitadas
    while(visitadas.size()){
		// Guarda la posicion a insertar
		int i = 0;
		// Mientras el ultimo elemento de solucion sea distinto al primero del par
		while(auxC.n != visitadas[i].first.n) i++;
		// Guarda la ciudad 
		auxC = visitadas[i].second;
		// La añade a la solucion
		solucion.push_back(auxC);
		// Elimina el par de las visitadas
        visitadas.erase(visitadas.begin() + i);
    }
}

/**
 * @brief Calcula la ruta por el vecino mas cercano
 * 
 * @param ciudades Vector con las ciudades a visitar
 * @param solucion Vector que almacena la solucion
 */
void insercion(const std::vector<Ciudad> &ciudades, std::vector<Ciudad> &solucion) {

	// Vector de pares que almacena las ciudades visitadas
	// Cada par indica de que ciudad a que ciudad va 
    std::vector<std::pair<Ciudad,Ciudad>> visitadas;

	// Almacena coordenadas para la ciudad N E S
	int norte = -1, este = -1, sur = -1;
	// Almacena la posicion de las ciudades seleccionadas
	int ciudad_norte, ciudad_este, ciudad_sur;

    // Obtiene las ciudades N E S
	for(int i=0; i<ciudades.size(); i++){
		if(ciudades[i].coordenadas.second > norte){
			norte = ciudades[i].coordenadas.second;
			ciudad_norte = i;
		}
		if(ciudades[i].coordenadas.first > este){
			este = ciudades[i].coordenadas.first;
			ciudad_este = i;
		}
		if(ciudades[i].coordenadas.second < sur || sur==-1){
			sur = ciudades[i].coordenadas.second;
			ciudad_sur = i;
		}
	}	

	// Añade a visitadas pares con la ciudad {N,E}, {E,S}, {S,N}
	std::pair<Ciudad, Ciudad> aux;
	visitadas.push_back(std::make_pair(ciudades[ciudad_norte], ciudades[ciudad_este]));
	visitadas.push_back(std::make_pair(ciudades[ciudad_este], ciudades[ciudad_sur]));
	visitadas.push_back(std::make_pair(ciudades[ciudad_sur], ciudades[ciudad_norte]));
	
	// Vector que almacena las ciudades no visitadas (candidatas)
	std::vector<Ciudad> candidatas;

	// Añade las ciudades no visitadas
	for(int i = 0 ; i < ciudades.size() ; i++){
		if(i != ciudad_norte && i != ciudad_este && i != ciudad_sur)
			candidatas.push_back(ciudades[i]);
	}

	// Para cada ciudad no visitada
	while (candidatas.size()) {
		// Almacena las distancias
		int d_min = 9999999;
		// Almaecna la ciudad a insertar y borrar
		int ciudad_a_aniadir, par_a_modificar;
		// Para cada ciudad candidata
	    for(int i = 0 ; i < candidatas.size() ; i++){
			// Se comprueba donde se inserta para cada ciudad visitada
			for(int j = 0 ; j < visitadas.size() ; j++){
				// Calcula el aumento que se tendria con la insertada
				int d = aumentoDistancia(candidatas[i], visitadas[j].first, visitadas[j].second);
				// Si mejora
				if(d < d_min || d_min == -1) {
					d_min = d;
					ciudad_a_aniadir = i;
					par_a_modificar = j;
				}
			}
		}

		// Guarda la ciudad a sustituir
		Ciudad modificada = visitadas[par_a_modificar].second;
		// Establece la nueva ciudad visitada
		visitadas[par_a_modificar].second = candidatas[ciudad_a_aniadir];
		// Añade el nuevo par actualizado
		visitadas.push_back(std::make_pair(candidatas[ciudad_a_aniadir], modificada));
		// Elimina el par desactualizado
		candidatas.erase(candidatas.begin() + ciudad_a_aniadir);
	}
	
	// Se ordena la solucion segun los pares
	ordenarSolucion(solucion, visitadas);
}

//**********************************
// Fin metodos solucion previa greedy

/**
 * @brief Metodo que calcula una solucion mediante branch and bound del problema de viajante de comercio
 * 
 * @param inicial Nodo inicial que representa la primera ciudad
 * @param matriz Matriz de distancias entre ciudades
 * @param nodos_expandidos Cantidad de nodos expandidos
 * @param capacidad_cola Capacidad maxima alcanzada por la cola con prioridad
 * @param cantidad_podas Cantidad de podas realizadas
 * @param cota_global Cota que indica el coste mas pequeño obtenido por una solucion valida
 * @param solucion Vector que almacena la ruta solucion
 */
void branch(Nodo inicial, int **matriz, int &nodos_expandidos, int &capacidad_cola, int &cantidad_podas, int &cota_global, std::vector<int> & solucion) {

    // Cola con prioridad
    std::priority_queue<Nodo, std::vector<Nodo>, Comparador> cola;
    // Inicializa el nodo actual con el nodo inicial
    Nodo current = inicial;
    // Inicializa la cola con el nodo actual
    cola.push(current);
    int cap = 1;
    
    // Mientras haya nodos en la cola con prioridad
    while (!cola.empty() && current.coste < cota_global) {

        // Actualiza el nodo actual con el mas prometedor
        current = cola.top();
        // Aumenta el numero de nodos expandidos
        nodos_expandidos++;
        // Se elimina el elemento de la cola con prioridad
        cola.pop();

        // Genera los hijos del nodo padre (ciudades candidatas a visitar)
        for(int i = 0 ; i < current.candidatos.size() ; i++) {
            // Crea un hijo de la actual
            Nodo hijo = current;

            // Aumenta el coste de ir a la ciudad visitada
            hijo.coste += matriz[hijo.candidatos[i]][current.id];

            // Si el coste mejora
            if(hijo.coste < cota_global) {

                // Actualiza el identificador de la ciudad candidata
                hijo.id = hijo.candidatos[i];
                // Añade al recorrido la ciudad candidata
                hijo.recorrido.push_back(hijo.candidatos[i]);
                // Marca la ciudad candidata como visitada
                hijo.candidatos.erase(hijo.candidatos.begin()+i);

                // Si es hoja, comprueba con la vuelta al origen
                if(hijo.candidatos.empty()) {
                    // Actualiza el coste
                    hijo.coste += matriz[hijo.id][current.recorrido[0]];
                    // Si mejora el coste de la ruta incluyendo el origen
                    if(hijo.coste < cota_global) {
                        // Añade la vuelta al origen
                        hijo.recorrido.push_back(hijo.recorrido[0]);
                        cota_global = hijo.coste;
                        solucion = hijo.recorrido;
                    }
                }
                // No es hoja, se añade
                else {
                    // Aumenta el indicador de tamaño de la cola
                    cap++;
                    if(cap > capacidad_cola) capacidad_cola = cap;
                    // Añade el hijo a la cola por prioridad
                    cola.push(hijo);
                }
            }
            // Si no mejora, se poda
            else cantidad_podas++;
            
        }
    }
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

    // Calcula solucion greedy previa
    std::vector<Ciudad> solucionGreedy;
    insercion(ciudades, solucionGreedy);
    int cota_global = distanciaTotal(solucionGreedy);

    // Solucion
    std::vector<int> solucion;

    // Nodo inicial
    Nodo nodo;
    nodo.id = 0;
    for(int i = 1 ; i < ciudades.size() ; i++) nodo.candidatos.push_back(i);
    nodo.coste = 0;
    nodo.recorrido.push_back(0);

    int nodos_expandidos = 0;
    int capacidad_cola = 0;
    int cantidad_podas = 0;

    // Obtiene el tiempo antes del algoritmo
    high_resolution_clock::time_point tantes, tdespues;
    tantes = high_resolution_clock::now();

    // LLamada al metodo branch and bound
    branch(nodo, matriz, nodos_expandidos, capacidad_cola, cantidad_podas, cota_global, solucion);
    
    // Obtiene el tiempo despues del algoritmo
    tdespues = high_resolution_clock::now();

    // Muestra solucion
    for(int i = 0 ; i < solucion.size() ; i++)
        std::cout << solucion[i]+1 << " ";
    std::cout << std::endl;
    //mostrarMatriz(matriz, N);

    //Muestra la distancia de la nodo_Solucion    
    std::cout << "Distancia: " << cota_global << std::endl;
    duration<double> transcurrido = duration_cast<duration<double>>(tdespues - tantes);
    std::cout << "Tiempo: " << transcurrido.count() << std::endl;
    std::cout << "Nodos expandidos: " << nodos_expandidos << std::endl;
    std::cout << "Capacidad maxima cola: " << capacidad_cola << std::endl;
    std::cout << "Cantidad de podas: " << cantidad_podas << std::endl;

    for(int i = 0 ; i < N ; i++) delete[] matriz[i];
    delete[] matriz;

    return 0;
}