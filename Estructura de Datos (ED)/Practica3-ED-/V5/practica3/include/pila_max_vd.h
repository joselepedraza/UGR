#ifndef __PILA_MAX_VD_H__
#define __PILA_MAX_VD_H__

#include "VDG.h"
#include <fstream>
#include <istream>
#include <iostream>
using namespace std;

template <class T>
class Pila_max_VD{

private:
	/*Creamos VD minimo de una posicion. Porque si no, no podemos redimensionar.*/
	VectorDinamico<T> vec;
	int usados;
public:
	bool empty();
	int size();
	//~ T top();
	T& top();
	void push(const T &elem);
	void pop();
	Pila_max_VD& operator=(const Pila_max_VD<T>& pmv);
	Pila_max_VD(const Pila_max_VD<T>& pmv);
	Pila_max_VD(int tama);
	Pila_max_VD();
};

#include "../src/pila_max_vd.cpp"

#endif
