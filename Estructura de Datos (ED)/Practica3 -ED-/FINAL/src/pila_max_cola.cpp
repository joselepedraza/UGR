#include "pila_max_cola.h"

/*template<class T>
Pila_max_Cola<T>::Pila_max_Cola(){
	//NO HACE FALTA
}*/
/*
template<class T>
Pila_max_Cola<T>::Pila_max_Cola(int tama){
	//NO HACE FALTA
}
*/



/*Con esta forma obtenemos ordenamos los elementos de cola y
 y los metemos una otra cola pero sus elementos se disponen como estuvieran una pila .
*/

/*
template<class T>
T& Pila_max_Cola<T>::top(){
	Cola<T> c1,c2,borra,cola_pila;
	int cont=0;
	c1=col;
	//recorrer todos de la cola original para conseguir el ultimo en cada caso
	while(cont<col.num_elementos()){
		while(!c1.vacia()){	//Vamos a llegar  hasta el final
			if(c1.num_elementos()>1){
				c2.poner(c1.frente());//En la cola c2 nos quedamos con todos los elementos de c1 menos el ultimo.
				c1.quitar();

			}else{
				cola_pila.poner(c1.frente());
				c1.quitar();
			}
		}
		c1=c2;
		c2 = borra;
		cont++;
	}
	return cola_pila.frente();
}*/


Pila_max_Cola::Pila_max_Cola(const Pila_max_Cola & pmc){
	col=pmc.col;
}

Pila_max_Cola& Pila_max_Cola::operator=(const Pila_max_Cola & pmc){
	if(this != &pmc){
		col=pmc.col;
	}
	return *this;
}

elemento Pila_max_Cola::top(){
	Cola<elemento> c1,c2,borra,cola_pila;
	c1=col;
	while(!c1.vacia()){	//Vamos a llegar  hasta el final
		if(c1.num_elementos()==1){
			cola_pila.poner(c1.frente());
		}
		c1.quitar();
	}
	return ((cola_pila.frente()));
}

void Pila_max_Cola::pop(){
	Cola<elemento> aux;
	while(col.num_elementos()>1){
		aux.poner(col.frente());
		col.quitar();
	}
	col=aux;
}

void Pila_max_Cola::push(int elem){
	if(col.num_elementos()==0){
		elemento e(elem,elem);
		col.poner(e);
	}else{
		if(top().maximo>elem){
			elemento e(elem,top().maximo);
			col.poner(e);
		}else{
			elemento e(elem,elem);
			col.poner(e);
		}
	}
}

int Pila_max_Cola::size(){
	return col.num_elementos();
}

bool Pila_max_Cola::empty(){
	return (col.num_elementos()==0);
}
