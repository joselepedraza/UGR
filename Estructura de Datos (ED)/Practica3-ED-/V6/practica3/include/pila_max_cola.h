#ifndef __PILA_MAX_H__
#define __PILA_MAX_H__

#include "cola.h"
#include <fstream>
#include <istream>
#include <iostream>
using namespace std;


struct elemento{
	int elem;///<elemento a almacenar
	int maximo;///<el maximo
	elemento(int ele ,int max){
		maximo=max;
		elem=ele;		
	}
	elemento(){}
	
	elemento& operator=(const elemento& e){
		if(this != &e){
			maximo=e.maximo;
			elem=e.elem;
		}
		return *this;
	}
};
	
class Pila_max_Cola{
private:
	Cola<elemento> col;
public:
	bool empty();
	int size();
	elemento top();
	void push(int elem);
	void pop();
	Pila_max_Cola& operator=(const Pila_max_Cola& pmc);
	Pila_max_Cola(const Pila_max_Cola& pmc);
	Pila_max_Cola(){}
};

#include "../src/pila_max_cola.cpp"

#endif
