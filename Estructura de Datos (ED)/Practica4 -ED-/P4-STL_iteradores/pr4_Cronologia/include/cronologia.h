#ifndef __CRONOLOGIA
#define __CRONOLOGIA

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm> 
#include <assert.h>
#include <utility> //para el pair
#include <map>
#include "fechahistorica.h"



using namespace std;

class cronologia{


	private:
		map<int,fechahistorica> fechas;
	/**
	 * @brief Funcion auxiliar que recorre los acontecimientos y los concatena
	 * @return [Tipo string] cadena de fechas historicas
	*/
	string concatenarFechas()const;

	public:
		typedef map<int,fechahistorica>::iterator iterator;
		typedef map<int,fechahistorica>::const_iterator const_iterator;


		/**
		 * @brief Constructor vacio
		 * @note Construye un objeto de tipo cronologia sin datos
		 */
		cronologia();

		/**
		 * @brief Constructor con parametros
		 * @param fechas [Tipo map<int,fechahistorica> ] donde int es el anio y fechahistorica es el objeto .
		 */
		cronologia(const map<int,fechahistorica> &fechas);

		/**
		 * @brief Constructor por copia
		 * @param cr objeto de la clase cronologia a copiar
		*/
		cronologia(const cronologia &cr);

		/**
		 * @brief Retorna el conjunto de fechas de una cronologia
		 * @return [Tipo int] coleccion de objs de tipo fecha
		 */
		map<int,fechahistorica> getFechas()const;

		/**
		 * @brief Modifica el conjunto completo de fechas de una cronologia
		 * @param mapa de <entero(anio), fechahistorica>
		 */
		void setFechas(map<int,fechahistorica>& m);


		/**
		 * @brief Sobrecarga del operador de asignacion
		 * @note Toma los datos de un objeto cronologia y los incluye en el actual
		 * @param e [Tipo cronologia] Objeto a asignar al actual
		 * @return [Tipo cronologia] Objeto
		 */
		cronologia& operator=(const cronologia& e);

		/**
		 * @brief Convierte el objeto en una cadena
		 * @return [Tipo string] Cadena de datos del objeto cronologia
		 */
		string toString()const;

		/**
		 * @brief Sobrecarga del operador de igualdad
		 * @note Compara los datos de dos objetos de tipo cronologia y determina si son iguales
		 * @param e [Tipo cronologia] Objeto a comparar con el actual
		 * @retval true Si ambos objetos son iguales
		 * @retval false Si ambos objetos no son iguales
		 */
		bool operator==(const cronologia& e) const;

		/**
		 * @brief Sobrecarga del operador de desigualdad
		 * @param e [Tipo cronologia] Objeto a comparar con el actual
		 * @retval true Si ambos objetos no son iguales
		 * @retval false Si ambos objetos son iguales
		 */
		bool operator!=(const cronologia& e) const;

		/**
		 * @brief Sobrecarga del operador suma. Realiza la union de dos cronologias (this y otra)
		 * @param e [Tipo cronologia] Objeto tipo cronologia a unir.
		 * @return Objeto con la union de dos cronologias
		 */
		cronologia operator+(const cronologia& e) const;

		/**
		 * @brief Busca un evento segun el anio especificado
		 * @param anio de tipo entero
		 * @return Cadena con los eventos de ese anio
		 */
		fechahistorica buscarEventosAnio(int anio);

		/**
		 * @brief Obtiene un subconjunto de cronologia de un rango de anios
		 * @param ini -> anio desde
		 * @param fin -> anio hasta
		 * @note (se incluyen en la busqueda ambos anios)
		 * @return Objeto cronologia con los eventos acontecidos en el rango de anios.
		 */
		cronologia buscarEventosRangoAnios(int ini,int fin);


		/**
		 * @brief Obtiene un subconjunto de cronologia a partir de una palabra clave
		 * @param pal cadena clave a buscar entre los eventos
		 * @return Objeto cronologia con todas las fechas relacionadas con la clave
		 */
		cronologia buscarEventosPalabra(string pal);


		/**
		 * @brief Inserta una fecha al conjunto de cronologia
		 * @param e de tipo fechahistorica
		 * @return void
		*/
		void insertar(const fechahistorica& e);

		/**
		 * @brief Elimina una fecha del conjunto de cronologia
		 * @param e de tipo fechahistorica
		 * @return void
		*/
		void eliminar(const fechahistorica& e);


		/**
		 * @brief Devuelve un iterador apuntando al primer elemento del rango [primero,ultimo)
		 * @param fh , obj. fechahistorica
		 * @return Un iterador al límite inferior de fh en el intervalo. Si todo el elemento en el rango compara menos que fh, la función devuelve la última.
		*/
		cronologia::const_iterator lower_bound (const fechahistorica& fh)const;

		/**
		 * @brief Borra el conjuto cronologia
		 * @return void
		*/
		void clear();


		/**
		 * @brief Numero de fechas en la cronologia
		 * @return numero de fechas en la cronologia
		*/
		int size();


		/******************** Iteradores begin - end **************************/
		iterator begin();
		iterator end();

		const_iterator begin() const;
		const_iterator end() const;

};


/**
 * @brief Corta la cadena segun un delimitador
 * @param s cadena a cortar
 * @param delim delimitador por el que vamos a ir dividiendo
 * @return vector de strings con la cadena cortada
*/
vector<string> explode(const string& s, char delim);

/**
 * @brief Sobrecarga del operador de flujo de salida
 * @param[in] os [Tipo ostream] Objeto de flujo de salida
 * @param[in] e [Tipo cronologia] Objeto a enviar al flujo de salida
 * @return ostream Flujo de salida
 */
ostream& operator<<(ostream& os, const cronologia& c);

/**
 * @brief Sobrecarga del operador de flujo de entrada
 * @param[in] os [Tipo istream] Objeto de flujo de entrada
 * @param[in] e [Tipo cronologia] Objeto a enviar al flujo de salida
 * @return istream Flujo de entrada
 */
ifstream& operator>> (ifstream& is, cronologia& c);

#endif
