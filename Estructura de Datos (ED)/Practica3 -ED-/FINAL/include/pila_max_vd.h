#ifndef __PILA_MAX_VD_H__
#define __PILA_MAX_VD_H__

#include "VDG.h"
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

class Pila_max_VD{

private:

	VectorDinamico<elemento> vec;
	int usados;
	int top_max();
	void push_max(int elem);
public:
	bool empty();
	int size();
	elemento top();
	void push(int elem);
	void pop();
	Pila_max_VD& operator=(const Pila_max_VD& pmv);
	Pila_max_VD(const Pila_max_VD& pmv);
	Pila_max_VD(int tama);
	Pila_max_VD();

};

//ostream& operator<<(ostream& os, const elemento& e);
//#include "../src/pila_max_vd.cpp"

#endif
