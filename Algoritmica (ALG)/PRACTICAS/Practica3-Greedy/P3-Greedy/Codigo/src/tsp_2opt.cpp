/*
    Algoritmo que obtiene una solucion greedy mediante 
    la heuristica 2opt de un archivo .tsp

    Para esta tecnica se utiliza una solucion previa para 
    mejorar la eficiencia del algoritmo (en este caso se ha optado
    por la solucion de la heuristica del vecino mas cercano),
    ya que al partir de una solucion previa, el numero de 
    iteracciones es mucho menor.

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
    Ejecucion:   ./bin/tsp_2opt data/tsp_escenarios/fichero.tsp base
    Ejecucion:   "ejecutable" "fichero" {base | vmc}
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <string>
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
 * @brief Busca la ciudad mas cercana a la ultima ciudad visitada
 * 
 * @param ultima Ultima ciudad visitada
 * @param candidatas Ciudades candidatas a visitar
 * @return int Posicion de la ciudad candidata en el vector de candidatas
 */
int buscarMasCercano(Ciudad ultima, const std::vector<Ciudad> &candidatas) {
    // La distancia minima inicial es enorme para que tome como primera ciudad candidata la primera visitada
    int d_min = 9999999;
    // Almacena la posicion de la ciudad mas cercana
    int pos = 0;
    // Busca la mas cercana a la ultima visitada
    for (int i = 0 ; i < candidatas.size() ; i++) {
        // Calcula la distancia a la ciuda candidata
        int d = distancia(candidatas[i], ultima);
        // Actualiza si es mejor
        if (d < d_min) {
            d_min = d;
            pos = i;
        }
    }
    return pos;
}

/**
 * @brief Calcula la ruta por el vecino mas cercano
 * 
 * @param ciudades Ciudades por las que debe pasar el viajante
 * @param solucion Ciudades por las que ha pasado el viajante segun el vecino mas cercano
 */
void vmc(std::vector<Ciudad> &ciudades, std::vector<Ciudad> &solucion) {

    // Se inicializa la solucion al caso base
    solucion = ciudades;
    // Se añade la ciudad retorno
    solucion.push_back(solucion[0]);

    // Calcula la distancia total de la primera solucion base
    int t_min = distanciaTotal(solucion);

    // Empieza la ruta desde una ciudad distinta
    for(int i = 0 ; i < ciudades.size() ; i++) {

        // Añade la ciudad inicial a visitadas
        std::vector<Ciudad> visitadas;
        visitadas.push_back(ciudades[0]);

        // Añade las ciudades candidatas excluyendo la primera
        std::vector<Ciudad> candidatas;
        for(int j = 1 ; j < ciudades.size() ; j++) candidatas.push_back(ciudades[j]);
        
        // Almacena la posicion del elemento visitado a añadir
        int pos;
        
        // Para cada ciudad no visitada
        while (candidatas.size()) {
            // Obtiene la posicion de la ciudad mas cercana a la ultima visitada
            pos = buscarMasCercano(visitadas.back(), candidatas);
            // Añade la mas cercana
            visitadas.push_back(candidatas[pos]);
            // Se elimina del conjunto sin visitar la ciudad visitada
            candidatas.erase(candidatas.begin()+pos);
        }

        // Se añade la ciudad retorno
        visitadas.push_back(visitadas[0]);

        // Se calcula la distancia total de la ruta
        int total = distanciaTotal(visitadas);

        // Si el coste de la ruta mejora respecto a la anterior
        if (total < t_min) {
            t_min = total;
            solucion.clear();
            solucion = visitadas;
        }
        
        // Se cambia la ciudad origen
        if(i < ciudades.size()-1) {
            Ciudad aux = ciudades[0];
            ciudades[0] = ciudades[i+1];
            ciudades[i+1] = aux;
        }
        // Si es la ultima iteraccion, se cambia el primero por el ultimo
        else {
            Ciudad aux = ciudades[0];
            ciudades[0] = ciudades[ciudades.size()-1];
            ciudades[ciudades.size()-1] = aux;
        }
    }
}

/**
 * @brief Realiza el intercambio de ciudades en una ruta, poniendo en orden inverso de una posicion i a una posicion k
 * 
 * @param ruta Vector en el que se realiza el intercambio
 * @param i Posicion desde donde se comienza a intercambiar
 * @param k Posicion hasta donde se termina de intercambiar
 * @return std::vector<Ciudad> Vector con la ruta intercambiada
 */
std::vector<Ciudad> intercambio(std::vector<Ciudad> ruta, int i, int k) {
    std::vector<Ciudad> ruta_inter;
    // Añadir desde 0 hasta i
    for(int j = 0 ; j <= i ; j++) ruta_inter.push_back(ruta[j]);
    // Añadir de k a i-1
    int inc = 0;
    for(int j = k ; j > i ; j--) ruta_inter.push_back(ruta[j]);
    // Añadir de k+1 al final
    for(int j = k+1 ; j < ruta.size() ; j++) ruta_inter.push_back(ruta[j]);
    return ruta_inter;
}

/**
 * @brief Calcula una ruta por una heuristica 2-opt, en funcion de la distancia menor
 * 
 * @param ciudades Vector de ciudades a visitar
 * @param solucion_2opt Vector que almacena la ruta solucion del algoritmo
 */
void two_opt(std::vector<Ciudad> ciudades, std::vector<Ciudad> &solucion_2opt) {

    //Inicializa solucion
    solucion_2opt = ciudades;

    bool hay_mejora = true;

    while(hay_mejora) {
        hay_mejora = false;
        //Calcular distancia
        int distancia = distanciaTotal(solucion_2opt);
        //Para el resto sin visitar (excluye origen y vuelta)
        for(int i = 1 ; i < ciudades.size()-1 && !hay_mejora ; i++) {
            //Posibles combinaciones
            for(int j = i+1 ; j < ciudades.size()-1 ; j++) {
                //Obtiene una ruta con una variacion de intercambio
                std::vector<Ciudad> ruta_intercambiada = intercambio(solucion_2opt, i, j);
                int nueva_distancia = distanciaTotal(ruta_intercambiada);
                //Si mejora la solucion
                if (nueva_distancia < distancia) {
                    distancia = nueva_distancia;
                    solucion_2opt = ruta_intercambiada;
                    hay_mejora = true;
                }
            }
        }
    }
}


int main (int argc, char *argv[]) {
   
    if (argc != 3) {
        std::cout << "Numero de parametros erroneos" << std::endl;
        return 1;
    }
    
    //Vector donde sea almacenan las ciudades
    std::vector<Ciudad> ciudades;
    //Leer archivo tsp
    std::string archivo = argv[1];
    std::ifstream is(archivo);
    leerFicheroTSP(is, ciudades);
    is.close();
    
    // Vector que almacena la solucion por vecino mas cercano
    std::vector<Ciudad> solucion;

    // Si se quiere realizar sobre una solucion greedy previa por el vmc
    if(std::string(argv[2]) == "vmc") {
        // Calcula la ruta por el vecino mas cercano
        vmc(ciudades, solucion);
    }
    // Si no, se quiere calcular de un fichero base
    else if(std::string(argv[2]) == "base") {
        solucion = ciudades;
        solucion.push_back(solucion.front());
    }
    // Error de argumento
    else {
        std::cout << "Argumento 2 con valor erroneo, las opciones son:" << std::endl;
        std::cout << "\t'base' -> Ejecutar 2opt SIN solucion greedy previa" << std::endl;
        std::cout << "\t'vmc'  -> Ejecutar 2opt CON solucion greedy previa" << std::endl;
        return 1;
    }

    // Vector que almacena la solucion por 2opt
    std::vector<Ciudad> solucion_2opt;
    
    // Obtiene el tiempo antes del algoritmo
    high_resolution_clock::time_point tantes, tdespues;
    tantes = high_resolution_clock::now();

    // Calcula la ruta por 2opt
    two_opt(solucion, solucion_2opt);

    // Obtiene el tiempo despues del algoritmo
    tdespues = high_resolution_clock::now();

    // Muestra la solucion
    mostrarVector(solucion_2opt);

    //Muestra la distancia de la solucion    
    std::cout << "Distancia: " << distanciaTotal(solucion_2opt) << std::endl;
    duration<double> transcurrido = duration_cast<duration<double>>(tdespues - tantes);
    std::cout << "Tiempo: " << transcurrido.count() << std::endl;


    return 0;
}
