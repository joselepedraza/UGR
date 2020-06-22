/*
    Algoritmo que obtiene una solucion greedy mediante 
    la heuristica de insercion de un archivo .tsp

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
    Ejecucion:   ./bin/tsp_insercion data/tsp_escenarios/fichero.tsp
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <chrono>

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
 * @brief Calcula el aumento de distancia al añadir la ciudad1 entre la ciudad2 y la ciudad3
 * 
 * @param city1 Ciudad candidata
 * @param city2 Ciudad entre la que se inserta 
 * @param city3 Ciudad entre la que se inserta
 * @return int Distancia que se obtiene con la insercion
 */
int aumentoDistanciaTotal(Ciudad city1, Ciudad city2, Ciudad city3){
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
				int d = aumentoDistanciaTotal(candidatas[i], visitadas[j].first, visitadas[j].second);
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

int main (int argc, char *argv[]) {
   
    if (argc != 2) {
        std::cout << "Numero de parametros erroneos" << std::endl;
        return 1;
    }
    
    // Vector donde sea almacenan las ciudades
    std::vector<Ciudad> ciudades;

    // Leer archivo tsp
    std::string archivo = argv[1];
    std::ifstream is(archivo);
    leerFicheroTSP(is, ciudades);
    is.close();

    // Vector que almacena la solucion
    std::vector<Ciudad> solucion;
	
    // Obtiene el tiempo antes del algoritmo
    high_resolution_clock::time_point tantes, tdespues;
    tantes = high_resolution_clock::now();

    // Calcula la ruta por insercion
    insercion(ciudades, solucion);

    // Obtiene el tiempo despues del algoritmo
    tdespues = high_resolution_clock::now();

	// Mostrar solucion
	mostrarVector(solucion);

    //Muestra la distancia de la solucion    
    std::cout << "Distancia: " << distanciaTotal(solucion) << std::endl;
    duration<double> transcurrido = duration_cast<duration<double>>(tdespues - tantes);
    std::cout << "Tiempo: " << transcurrido.count() << std::endl;

    return 0;
}
