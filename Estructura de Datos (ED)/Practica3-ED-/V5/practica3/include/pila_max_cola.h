#ifndef __PILA_MAX_H__
#define __PILA_MAX_H__

#include "cola.h"
#include <fstream>
#include <istream>
#include <iostream>
using namespace std;


template <class T>
class Pila_max_Cola{

private:
	Cola<T> col;
public:
	bool empty();
	int size();
	T top();
	//~ T& top();
	void push(const T &elem);
	void pop();
	Pila_max_Cola& operator=(const Pila_max_Cola<T>& pmc);
	Pila_max_Cola(const Pila_max_Cola<T>& pmc);
	Pila_max_Cola(){}
};

#include "../src/pila_max_cola.cpp"

#endif
