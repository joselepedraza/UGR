/**
 * @file quienesquien.h
 * @brief Fichero cabecera del QuienEsQuien.
 *
 * Almacena el árbol de preguntas para jugar al ¿Quién es quién?.
 */
 
/*	Grupo A-2
 * 	Alumnos: Angel Barrilao Bensrhir, Jose Luis Pedraza Roman, Jorge Garcia Moreno (Grupo A-1).
*/

#ifndef _QUIENESQUIEN_H_
#define _QUIENESQUIEN_H_

#define DEBUG_QUIENESQUIEN 0

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <cassert>
#include <set>
#include <sstream>
#include <utility>
#include <algorithm>
#include <stack>

#include "pregunta.h"
#include "bintree.h"

using namespace std;


/**
 * @brief T.D.A. QuienEsQuien
 *
 * Conjunto de personajes con sus atributos.
 */
class QuienEsQuien{
private:
	/**
	  * @brief Almacena el nombre de los personajes. Su índice en 
	  *        este vector corresponde con el índice de su 
	  *        descripción en el tablero.
	  */
	vector<string> personajes;

	/**
	  * @brief Almacena los atributos.  Su índice en este vector 
	  *        corresponde con el índice correspondiente de cada 
	  *        vector del tablero.
	  */
	vector<string> atributos;

	/**
	  * @brief Matriz que almacena para cada personaje su valor para 
	  *        cada atributo.
	  */
	vector<vector<bool>> tablero;

	/**
	  * @brief Arbol de preguntas para adivinar personajes.
	  */
	bintree<Pregunta> arbol;

	/**
	  * @brief Nodo del arbol de preguntas correspondiente a la jugada 
	  *        actual.
	  */
	bintree<Pregunta>::node jugada_actual;

/*======================================================================
=============================== FUNCIONES ==============================
======================================================================*/
	/**
	* @brief Calcula el numero de hojas que dispone el arbol
	* @param nodo
	* @return numero de hojas
	*/
	int numero_hojas(bintree<Pregunta>::node n);
	
	/**
	* @brief Funcion de entrada que se encarga de ajustar los nodos nulos y finalmente recalcular sus hijos 
	* @param nodo
	*/
	void eliminar_nodos_redundantes(bintree<Pregunta>::node n);
	
	/**
	* @brief Comprueba si un nodo es pregunta
	* @param nodo
	* @return true si se cumple , false en caso contrario
	*/
	bool esPregunta(bintree<Pregunta>::node n);
	
	/**
	* @brief Comprueba si un nodo es hoja
	* @param nodo
	* @return true si se cumple , false en caso contrario
	*/
	bool esHoja(bintree<Pregunta>::node n);
	
	/**
	* @brief Comprueba si un nodo es persona
	* @param nodo
	* @return true si se cumple , false en caso contrario
	*/
	bool esPersona(Pregunta per);
	
	/**
	* @brief Recorre cada nodo del arbol y asigna el numero de jugadores activos (hojas que dispone)
	* @param nodo
	*/
	void actualizar_numero_jugadores_activos(bintree<Pregunta>::node n);
	
	/**
	* @brief Poda y promociona los nodos que tienen algun hijo nulo
	* @param nodo
	* @return true si se cumple , false en caso contrario
	*/
	bool ajuste_nodos_nulos(bintree<Pregunta>::node n);
	
	/**
	* @brief Comprueba si alguno de sus hijos es nulo
	* @param nodo
	* @return true si se cumple , false en caso contrario
	*/
	bool tengoHijosNulos(bintree<Pregunta>::node n);
	
	/**
	* @brief Calcula la profundidad de cada hoja del arbol y la acumula 
	* @param nodo
	* @param variable float en donde se guarda la suma total de la profundidad de cada hoja
	*/
	void profundidad_promedio_hojas(bintree<Pregunta>::node n, float &sum_total_profundidad);
	
	
	/**
	* @brief Calcula la profundidad de un nodo dado
	* @param nodo
	* @return int nivel de profundidad
	*/
	int profundidad(bintree<Pregunta>::node n);
	
	/**
	* @brief Nos devuelve que personajes estan aun activos en el nodo actual
	* @param personajes_levantados es un set<string> donde guardamos el nombre de los personajes
	* @param nodo
	*/
	void informacion_jugada(set<string> &personajes_levantados,bintree<Pregunta>::node n);
	
	/**
	* @brief Devuelve en la pila la secuencia de preguntas formuladas hasta el nodo actual
	* @param pila de <pair<string,bool> en donde string es la pregunta y bool es la contestacion(o camino)
	* @param nodo
	*/
	void preguntas_formuladas(stack<pair<string,bool>>& pila_preguntas,bintree<Pregunta>::node jugada);
	
	/**
	* @brief Funcion que recorre una pila y muestra las preguntas formuladas de forma descendente (mas intuitivo)
	* @param nodo
	*/
	void preguntas_formuladas(bintree<Pregunta>::node jugada);
	
	/**
	* @brief Elimina del ABB un personaje a traves del string proporcionado
	* @param string nombre
	*/
	void elimina_personaje(string nombre);
	
	/**
	* @brief Aniade un personaje en al ABB segun el camino que nos indique sus caracteristicas
	* @param string <nombre> del personaje
	* @param caracteristicas vector booleano que contiene la descripcion del personaje
	*/
	void aniade_personaje(string nombre,vector<bool> caracteristicas);
	
	/**
	* @brief Busca un personaje por el arbol
	* @param nodo; El nodo actual
	* @param nombre; El nombre del personaje a buscar
	* @param nodoPersonaje; nodo en donde hemos encontrado al personaje
	*/
	void buscarPersonaje(bintree<Pregunta>::node n, const string & nombre,bintree<Pregunta>::node & nodoPersonaje);	
	
	/**
	* @brief funcion que obtiene el nombre o pregunta de un nodo
	* @param nodo
	* @return string nombre o pregunta
	*/
	string obtenerString(bintree<Pregunta>::node n);
	
/*====================================================================*/
/*======================== FIN FUNCIONES =============================*/
/*====================================================================*/
	
public:
	/**
	  * @brief Constructor básico de la clase
	  */
	QuienEsQuien();
	/**
	  * @brief Constructor de copia.
	  * @param quienEsQuien QuienEsQuien a copiar.
	  */
	QuienEsQuien(const QuienEsQuien &quienEsQuien);
	/**
	* @brief Destructor del pregunta.
	*/
	~QuienEsQuien();
	/**
	  * @brief Vacia todos los datos del QuienEsQuien receptor.
	  */
	void limpiar();
	/**
	* @brief Sobrecarga del operador de asignación.
	* @param quienEsQuien objeto a copiar.
	* @return Referencia al objeto copiado.
	*/
	QuienEsQuien& operator = (const QuienEsQuien &quienEsQuien);
	
	/**
	* @brief Operador de extracción de flujo.
	* @param is Stream de entrada
	* @param quienEsQuien Quien es quien a leer.
	* @return Referencia al stream de entrada.
	* 
	* Lee de @e is un quien es quien y lo almacena en @e 
	* quienEsQuien. El formato aceptado para la lectura es un TSV 
	* (tab-separated values) en el que las columnas tienen cabecera y 
	* son las preguntas. La última columna corresponde al nombre del 
	* personaje. Tras la cabecera se especifica en cada línea un 
	* personaje, teniendo el valor 1 o 0 si tiene/no tiene el 
	* atributo de la columna. En la última columna se da el 
	* nombre del personaje.
	*/
	friend istream& operator >> (istream& is, QuienEsQuien &quienEsQuien);
	
	/**
	* @brief Operador de inserción de flujo.
	* @param os Stream de salida
	* @param quienEsQuien Quien es quien a escribir.
	* @return Referencia al stream de salida.
	* 
	* Escribe en @e is un quien es quien.
	* El formato usado para la escritura es un TSV 
	* (tab-separated values) en el que las columnas tienen cabecera y 
	* son las preguntas. La última columna corresponde al nombre del 
	* personaje. Tras la cabecera se especifica en cada línea un 
	* personaje, teniendo el valor 1 o 0 si tiene/no tiene el 
	* atributo de la columna. En la última columna se da el 
	* nombre del personaje.
	*/
	friend ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien);

	/**
	  * @brief Escribe en la salida estandard las estructuras atributos, personajes y tablero.
	  */
	void mostrar_estructuras_leidas();

	/**
	  * @brief Este método construye el árbol de preguntas para todos los personajes del tablero.
	  */
	bintree<Pregunta> crear_arbol();
	
	/**
	  * @brief Sustituye el árbol actual por el árbol pasado por parámetro.
	  * 
	  * @param arbol_nuevo Arbol de preguntas que sustituye al actual.
	  * 
	  */
	void usar_arbol(bintree<Pregunta> arbol_nuevo);

	/**
	  * @brief Escribe el arbol generado en la salida estandard.
	  */
	void escribir_arbol_completo() const;

	/**
	   @brief Método que modifica el árbol de preguntas para que haya
	          preguntas redundantes.
	   @post El árbol de preguntas se modifica.
	*/
	void eliminar_nodos_redundantes();

	/**
	 * @brief Inicializa el juego.
	 * @post  Si la partida anterior no había terminado se 
	 *        pierde el progreso.
	 */
	void iniciar_juego();

	/**
	  * @brief Dado un estado del tablero devuelve los nombres de 
	  *        los personajes que aún no han sido tumbados en el 
	  *        tablero.
	  *
	  * @param jugada_actual Nodo del estado del tablero.
	  * 
	  * @return Conjunto de personajes que no han sido tumbados en el tablero.
	  * 
	  * @pre El arbol del QuienEsQuien receptor debe haber sido construido previamente.
	  * @pre El nodo indicado debe ser un nodo del arbol del QuienEsQuien receptor.
	  */
	set<string> informacion_jugada(bintree<Pregunta>::node jugada_actual);
	
	/**
	  * @brief Este método permite calcular la media de la profundidad de las hojas del árbol. Este valor representa el número (promedio) de preguntas necesarias para adivinar cada personaje. A menor profundidad promedio, mejor solución. Esta métrica es un indicador para evaluar la calidad de vuestra solución.
	  *
	  * @return Profundidad media del arbol de preguntas.
	  *
	  * @pre El arbol de preguntas debe haber sido construido previamente.
	  */
	float profundidad_promedio_hojas(); 

	/**
	  * @brief Rellena los datos del QuienEsQuien con un tablero calculado aleatoriamente.
	  * 
	  * @param numero_de_personajes Número de personajes que tiene el tablero a crear.
	  */
	void tablero_aleatorio(int numero_de_personajes);
};

#endif

