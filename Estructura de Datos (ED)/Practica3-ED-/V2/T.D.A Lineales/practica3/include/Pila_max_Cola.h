#ifndef __PILA_MAX_H__
#define __PILA_MAX_H__

#include "cola.h"
#include <fstream>
#include <istream>

using namespace std;


template <class T>
class Pila_max_Cola{
	
private:
	cola<T> col;
public:
	Pila_max_Cola();
	
	/*Relmente no haria falta, si el resize funciona ok. No nos preocupariamos en el tamaño
	 * ya que por defecto cuando creemos un objeto le podemos dar un tamaño especifico por ejemplo 10.
	 * y si nos va haciendo falta vamos duplicando el espacio. Si no lo usamos lo eliminamos 
	 * (Ver metodo push y pop en .cpp para verlo mas claro)
	 * */
	Pila_max_Cola(int tama);
	/**/
	
	bool empty();
	int size();
	T top();
	void push(const T &elem);
	void pop();
	//void emplace(elemento &e);
	//void swap();
};


/**
 * @brief Sobrecarga del operador de flujo de salida
 * @param[in] os [Tipo ostream] Objeto de flujo de salida
 * @param[in] e [Tipo cronologia] Objeto a enviar al flujo de salida
 * @return ostream Flujo de salida
 */
//ostream& operator<<(ostream& os, const T & c);

#include <Pila_max_Cola.cpp>

#endif
