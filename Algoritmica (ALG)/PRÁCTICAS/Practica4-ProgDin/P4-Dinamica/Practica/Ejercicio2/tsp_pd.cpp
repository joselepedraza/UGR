/*
    Algoritmo que realiza la busqueda de una ruta optima de un fichero tsp
    mediante programacion dinamica

    Se tiene en cuenta que la ruta {1 2 3 4 5 1} = {3 4 5 1 2 3}

    Alumno1: Jose Luis Pedraza Román
    Alumno2: Pedro Checa Salmerón
    Alumno3: Antonio Carlos Perea Parras
    Alumno4: Raúl Del Pozo Moreno

    UGR - ETSIIT - GII - Algoritmica - B1 - Grupo “Oliva”

    Compilacion: Se adjunta Makefile
    Ejecucion:   ./tsp_pd data/tsp/fichero.tsp
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <chrono>
#include <unordered_map>
#include <string>

using namespace std::chrono;

/**
 * @brief Estructura de datos que almacena una ciudad, mediante su identificador (n) 
 * y sus coordenadas (x, y)
 * 
 */
struct Ciudad
{
    int n = -1;
    std::pair<double, double> coordenadas = std::make_pair(-1.0, -1.0);
};

/**
 * @brief Lee datos de un fichero de texto .tsp
 * 
 * @param is Flujo de entrada
 * @param ciudades Struct que almacena el identificador de la ciudad y sus coordenadas
 */
void leerFicheroTSP(std::ifstream &is, std::vector<Ciudad> &ciudades)
{

    std::string basura = "";
    if (is)
    {
        int dimension = 0;
        // Leer hasta coordenadas
        while (basura != "NODE_COORD_SECTION")
        {
            is >> basura;
            // Si encuentra la dimension, la añade
            if (basura == "DIMENSION:")
                is >> dimension;
        }
        // Aqui empezamos a añadir al vector
        for (int i = 0; i < dimension; i++)
        {
            Ciudad city;
            is >> city.n;
            is >> city.coordenadas.first;
            is >> city.coordenadas.second;
            ciudades.push_back(city);
        }
    }
}

/**
 * @brief Muestra el contenido de un vector de enteros por pantalla
 * 
 * @param v El vector a mostrar
 */
void mostrarVector(const std::vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

/**
 * @brief Muestra el contenido de una matriz de enteros cuadrada
 * 
 * @param matriz La matriz a mostrar
 * @param N El tamaño de la matriz 
 */
void mostrarMatriz(int **matriz, int N)
{
    std::cout << "    ";
    for (int i = 0; i < N; i++)
        std::cout << i + 1 << "\t";
    std::cout << std::endl;
    for (int i = 0; i < N; i++)
    {
        std::cout << i + 1 << " : ";
        for (int j = 0; j < N; j++)
            std::cout << matriz[i][j] << "\t";
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
int distancia(Ciudad city1, Ciudad city2)
{
    // Calcula la distancia
    double d = sqrt(pow(city2.coordenadas.first - city1.coordenadas.first, 2) + pow(city2.coordenadas.second - city1.coordenadas.second, 2));
    // Redondea
    int ent = d / 1;
    return (((d - ent) < 0.5) ? ent : ent + 1);
}

/**
 * @brief Calcula la distancia a cada ciudad visitada incluyendo retorno
 * 
 * @param matriz Matriz de distancias entre ciudades
 * @param ruta Vector que almacena el orden de las ciudades a visitar
 * 
 * @return int Distanciad de la ruta dada
 */
int distanciaTotal(int **matriz, const std::vector<int> &ruta)
{
    int d = 0;
    for (int i = 1; i < ruta.size(); i++)
        d += matriz[ruta[i - 1] - 1][ruta[i] - 1];
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
void generarMatrizDistancias(const std::vector<Ciudad> &ciudades, int N, int **matriz)
{
    // Cada ciudad con si misma no tiene distancia --> d = 0
    for (int i = 0; i < N; i++)
        matriz[i][i] = 0;

    // Calcula distancias con otras ciudades
    // Recorre matriz superior (sin diagonal principal)
    for (int i = 0; i < N - 1; i++)
        for (int j = i + 1; j < N; j++)
        {
            matriz[i][j] = distancia(ciudades[i], ciudades[j]);
            matriz[j][i] = matriz[i][j];
        }
}

/**
 * @brief Busca en un unordered_map si una determinada clave existe o no
 * 
 * @param clave Clave a buscar
 * @param mapa Unordered_map donde se busca
 * @return true Si encuentra la clave
 * @return false Si no encuentra la clave
 */
bool encuentraClave(int clave, const std::unordered_map<int, std::vector<int>> &mapa)
{
    // Buscar en el map
    std::unordered_map<int, std::vector<int>>::const_iterator it;
    it = mapa.find(clave);
    // Si encuentra true
    return (it != mapa.end());
}

/**
 * @brief Calcula mediante Programacion Dinamica la distancia minima entre un numero 
 * determinado de ciudades evitando repetir secuencias de ciudades ya calculadas anteriormente
 * mediante el uso de un unordered_map y una matriz de distancias.
 * 
 * @param nodo_ini Nodo inicial de la ruta
 * @param nodo_actual Nodo que esta visitando el viajante
 * @param matriz Matriz de distancias entre ciudades
 * @param clave Clave que indica la/s distancia/s minima/s para una/s determinadas secuencias de ciudades
 * @param mapa Unordered_map que almacena secuencias de ciudades ya visitadas
 * @return int La distancia optima en cada nodo
 */
int pd(int nodo_ini, int nodo_actual, int **matriz, int clave, std::unordered_map<int, std::vector<int>> &mapa)
{

    // Nodo hoja, calcula hasta nodo hoja y vuelta
    if (clave == 0) return matriz[nodo_actual][nodo_ini];
    
    int nodo = 0;
    int clave_p = clave;
    int aux = 0;
    int min = 999999;
    int pos = 0; 
    bool encontrado = encuentraClave(clave, mapa); 

    // Mientras la clave indique que quedan ciudades
    while (clave_p > 0) { 
        // Si la clave es impar
        if (clave_p % 2) {
            // Obtiene la distancia ya calculada u obtiene el minimo de la distancia recursiva
            aux = (encontrado) ? mapa[clave][pos++] : pd(nodo_ini, nodo, matriz, (clave - pow(2, nodo)), mapa);
            // Si no ha encontrado la clave, añade la distancia a una nueva clave
            if(!encontrado) mapa[clave].push_back(aux);
            // Suma a la distancia obtenida la distancia al nodo padre
            aux += matriz[nodo_actual][nodo];
            // Si la distancia mejora
            if (min > aux) min = aux;
        }
        // Pasa al siguiente nodo recursivo
        nodo++;
        // Reajusta la clave de nodos
        clave_p /= 2;
    }   
    return min;
}

/**
 * @brief Obtiene la ruta optima a partir de las distancias optimas de cada ciudad previamente calculadas
 * y almacenadas en un unordered_map de forma que solo avanza por la rama que le asegura la distancia optima
 * 
 * @param matriz Matriz de distancias
 * @param mapa Unordered_map que almacena la/s distancia/s minima/s para cada nodo ciudad identificada/s por una clave
 * @param clave Clave que indica la/s distancia/s minima/s para una/s determinadas secuencias de ciudades
 * @param nodo_ant Ciudad padre (ciudad de la que proviene el nodo ciudad visitado)
 * @param solucion Vector que almacena la ruta optima
 */
void obtenerRuta(int **matriz, std::unordered_map<int, std::vector<int>> &mapa, int clave, int nodo_ant, std::vector<int> &solucion)
{
    int clave_p = clave;
    int pos = 0;
    int aux = 0;
    int nodo = 0, nodo_min;
    int min = 999999;

    // Mientras la clave indique que quedan ciudades
    while (clave_p > 0) {
        // Si la clave es impar
        if (clave_p % 2) {
            // Busca el nodo hijo con la distancia optima (para desechar ramas no optimas)
            aux = mapa[clave][pos++] + matriz[nodo_ant][nodo];
            // Si encuentra un hijo mas optimo, actualiza
            if (min > aux) {
                min = aux;
                nodo_min = nodo;
            }
        }
        // Pasa al siguiente hijo a comprobar
        nodo++;
        // Reajusta la clave 
        clave_p /= 2;
    }
    // Añade el nodo optimo
    solucion.push_back(nodo_min + 1);
    // Actualiza la clave
    clave -= pow(2, nodo_min);
    // Si quedan ciudades que comprobar, sigue buscando el nodo optimo
    if (clave) obtenerRuta(matriz, mapa, clave, nodo_min, solucion);
}

int main(int argc, char *argv[])
{

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
    matriz = new int *[N];
    for (int i = 0; i < N; i++) matriz[i] = new int[N];

    // Generar matriz de distancias
    generarMatrizDistancias(ciudades, N, matriz);

    // Vector que almacena la solucion, se inicializa con la ciudad inicial
    std::vector<int> solucion(1, 1);

    // Map que almacena las distancias de bloques del arbol, evita recursividades ya generadas
    std::unordered_map<int, std::vector<int>> mapa;

    // Almacena la clave inicial
    // Como se trata de bits, se marca todo 1 salvo el bit mas a la derecha
    /*
        pow(2, 4) = 16 = 1 0000
        (16) 1 0000 - 1 = (15) 1111   (se obtiene el max)
        (15)   1111 - 1 = (14) 1110   (se resta la ciudad inicial) --> (-2)
    */
    int clave = pow(2, N) - 2;
    // Almacena la distancia optima
    int d = 0;

    // Obtiene el tiempo antes del algoritmo
    high_resolution_clock::time_point tantes, tdespues;
    tantes = high_resolution_clock::now();

    // Genera un unordered_map de distancias, obteniendo la distancia minima
    d = pd(0, 0, matriz, clave, mapa);

    // Obtiene la ruta a partir del map de distancias ya calculadas
    obtenerRuta(matriz, mapa, clave, 0, solucion);

    // Obtiene el tiempo despues del algoritmo
    tdespues = high_resolution_clock::now();

    // Añade la ciudad origen
    solucion.push_back(1);

    // Calcula el tiempo de ejecucion
    duration<double> transcurrido = duration_cast<duration<double>>(tdespues - tantes);

    // Muestra la distancia
    std::cout << "Distancia: " << d << std::endl;

    // Muestra la ruta
    std::cout << "Ruta: ";
    mostrarVector(solucion);

    // Muestra el tiempo transcurrido
    std::cout << "Tiempo: " << transcurrido.count() << std::endl;

    // Elimina matriz de memoria
    for (int i = 0; i < N; i++)
        delete[] matriz[i];
    delete[] matriz;

    return 0;
}