/*COMO FUNCIONAN LAS OPCIONES PRECOMPILACION?*/
/*#dfine CUAL_COMPILA=2
#if CUAL_COMPILA==1
	#include "pila_max_vd.h"
#else
	#include "pila_max_cola.h"
#endif*/

#include "pila_max_vd.h"
#include "pila_max_cola.h"
#include <iostream>

using namespace std;

struct elemento{
	int ele;///<elemento a almacenar
	int maximo;///<el maximo
	elemento(int a ,int b){
		ele=a;
		maximo=b;
	}
};

ostream& operator<<(ostream& os, const elemento& e){
	os<<e.ele<<", "<<e.maximo<<endl;
}



int main(){
//Hay que dejar uno comentado, porque los dos a la vez dan core . Hay que solucionarlo.
/*
cout<<"********** VECTOR DINAM. **********"<<endl;
	Pila_max_VD<int> p1;

	for(int i=0;i<10;i++)
		p1.push(i);

	while(!p1.empty()){
		int x = p1.top();
		cout<<x<<endl;
		p1.pop();
	}
*/
cout<<"********** COLA **********"<<endl;
	Pila_max_Cola<int> p2;

	for(int i=0;i<10;i++)
		p2.push(i);


	while(!p2.empty()){
		int x = p2.top();
		cout<<x<<endl;
		p2.pop();
	}
}
