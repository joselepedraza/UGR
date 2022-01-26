#include "pila_max.h"

//#include "pila_max_vd.h"
//#include "pila_max_cola.h"
#include <iostream>

using namespace std;

ostream& operator<<(ostream& os, const elemento& e){
	os<<"{"<<e.elem<<","<<e.maximo<<"}"<<endl;
}


int main(){

cout<<"********** Pila **********"<<endl;
		pila_max p1;

		//~ for(int i=0;i<10;i++)
			//~ p1.push(i);

		p1.push(2);
		p1.push(7);
		p1.push(6);
		p1.push(9);


		while(!p1.empty()){
			cout<<p1.top()<<endl;
			p1.pop();
		}


/*
cout<<"********** VECTOR DINAM. **********"<<endl;
	Pila_max_VD p1(4);

	//~ for(int i=0;i<10;i++)
		//~ p1.push(i);

	p1.push(2);
	p1.push(7);
	p1.push(6);
	p1.push(9);


	while(!p1.empty()){
		cout<<p1.top()<<endl;
		p1.pop();
	}


cout<<"********** COLA **********"<<endl;
	Pila_max_Cola p2;

	//for(int i=0;i<10;i++)
		//p2.push(i);

	p2.push(2);
	p2.push(7);
	p2.push(6);
	p2.push(9);

	while(!p2.empty()){
		cout<<p2.top()<<endl;
		p2.pop();
	}
	*/
}
