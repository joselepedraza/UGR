#ifndef __FECHAHISTORICA
#define __FECHAHISTORICA

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class fechahistorica{


	private:
		int anio;
		vector<string> acontecimientos;
		

		/**
		 * @brief Funcion auxiliar que recorre los acontecimientos y los concatena
		 * @return [Tipo string] cadena de acontecimientos
		*/
		string recorrerAcontecimientos()const;

		

	public:
		/**
		 * @brief Constructor vacio
		 * @note Construye un objeto de tipo fechahistorica sin datos
		 */
		fechahistorica();

		/**
		 * @brief Constructor con parametros
		 * @param anio [Tipo int] anio de los acontecimientos
		 * @param acontecimientos [vector<string>] cadenas que describen acontecimientos
		 */
		fechahistorica(int anio, const vector<string> &acontecimientos);

		/**
		 * @brief Constructor con parametros
		 * @param anio [Tipo int] anio de los acontecimientos
		 * @param cad [string] cadena que describe un acontecimiento
		 */
		fechahistorica(int an, string cad);

		/**
		 * @brief Constructor por copia
		 * @param fh objeto de la clase fechahistorica a copiar
		*/
		fechahistorica(const fechahistorica &fh);

		/**
		 * @brief Retorna el parametro anio del objeto fechahistorica
		 * @return [Tipo int] Parametro anio
		 */
		int getAnio()const;
		
		/**
		 * @brief Retorna el numero de acontecimientos
		 * @return Entero, numero de acontecimientos
		 */
		int size();

		/**
		 * @brief Retorna el parametro acontecimientos del objeto fechahistorica
		 * @return [Tipo vector<string>] Parametro acontecimientos
		 */
		vector<string> getAcontecimientos()const;

		/**
		 * @brief Modifica el parametro anio
		 * @param a [Tipo int] Nuevo anio
		 * @return void
		 */
		void setAnio(int a);

		/**
		 * @brief Modifica el parametro acontecimientos
		 * @param v [Tipo vector<string>] Nueva coleccion de acontecimientos
		 * @return void
		 */
		void setAcontecimientos(const vector<string> &v);


		/**
		 * @brief Aniade un acontecimiento en la fecha
		 * @param str tipo string, acontecimiento a introducir
		 * @return void
		*/
		void aniadirAcontecimiento(string str);
		
		/**
		 * @brief Aniade un acontecimiento en la fecha
		 * @param str tipo string, acontecimiento a introducir
		 * @return void
		*/
		void aniadirAcontecimientos(vector<string> str);
		
		/**
		 * @brief Elimina un acontecimiento a traves de una palabra clave
		 * @param busqueda es la palabra clave para buscar el acontecimiento
		 * @return void
		*/
		void eliminarAcontecimiento(string busqueda);
		
		
		/**
		 * @brief Sobrecarga del operador de asignacion
		 * @note Toma los datos de un objeto fechahistorica y los incluye en el actual
		 * @param  e [Tipo fechahistorica] Objeto a asignar al actual
		 * @return [Tipo fechahistorica] Objeto
		 */
		fechahistorica& operator=(const fechahistorica& e);

		/**
		 * @brief Convierte el objeto en una cadena
		 * @return [Tipo string] Cadena de datos del objeto fechahistorica
		 */
		string toString()const;

		/**
		 * @brief Sobrecarga del operador de igualdad
		 * @note Compara los datos de dos objetos de tipo fechahistorica y determina si son iguales
		 * @param e [Tipo fechahistorica] Objeto a comparar con el actual
		 * @retval true Si ambos objetos son iguales
		 * @retval false Si ambos objetos no son iguales
		 */
		bool operator==(const fechahistorica& e) const;

		/**
		 * @brief Sobrecarga del operador de desigualdad
		 * @param e [Tipo fechahistorica] Objeto a comparar con el actual
		 * @retval true Si ambos objetos no son iguales
		 * @retval false Si ambos objetos son iguales
		 */
		bool operator!=(const fechahistorica& e) const;

		/**
		 * @brief Sobrecarga del operador menor que
		 * @param e [Tipo fechahistorica] Objeto a comparar con el actual
		 * @retval true Si el objeto this es menor
		 * @retval false Si el objeto this es mayor o igual
		 */
		bool operator<(const fechahistorica& e) const;
		
		/**
		 * @brief Sobrecarga del operador menor que
		 * @param e [Tipo fechahistorica] Objeto a comparar con el actual
		 * @retval true Si el objeto this es menor
		 * @retval false Si el objeto this es mayor o igual
		 */
		bool operator>(const fechahistorica& e) const;
		
		/**
		 * @brief Busca un acotencimiento por una palabra clave
		 * @param busqueda [String] cadena a buscar
		 * @return true si esta la palabra en el acontecimiento, false en caso contrario.
		 */
		bool buscarAcontecimiento(string busqueda);
		
		/**
		 * @brief Elimina los datos de un objeto fecha
		 * @return void
		 */
		void clear();
		
		/**
		 * @brief Funcion que comprueba el invariante. Se comprueba que el anio tenga 4 cifras.
		 * @param anio a comprobar
		 * @return [Tipo bool] Si se cumple = true, si no false
		*/
		//~ bool comp_invariante(int anio);
		bool comp_invariante()const;
};

/**
 * @brief Sobrecarga del operador de flujo de salida
 * @param[in] os [Tipo ostream] Objeto de flujo de salida
 * @param[in] e [Tipo fechahistorica] Objeto a enviar al flujo de salida
 * @return ostream Flujo de salida
 */
ostream& operator<<(ostream& os, const fechahistorica& e);

/**
 * @brief Sobrecarga del operador de flujo de entrada
 * @param[in] os [Tipo istream] Objeto de flujo de entrada
 * @param[in] e [Tipo fechahistorica] Objeto a enviar al flujo de salida
 * @return istream Flujo de entrada
 */
istream& operator>> (istream& is, fechahistorica& r);

#endif
