#ifndef __PILA_MAX_VD_H__
#define __PILA_MAX_VD_H__

#include "VectorDinamico.h"
#include <fstream>
#include <istream>

using namespace std;

template <class T>
class Pila_max_VD{

private:
	VectorDinamico<T> vec;
	int usados;
public:
	Pila_max_VD();
	Pila_max_VD(int tama);
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

//ostream& operator<<(ostream& os, const T & c);		ECHAR UN OJO

#include <Pila_max_VD.cpp>


#endif
