#include "pila_max_vd.h"

Pila_max_VD::Pila_max_VD(const Pila_max_VD& pmv){
	vec=pmv.vec;
	usados=pmv.usados;
}


Pila_max_VD& Pila_max_VD::operator=(const Pila_max_VD& pmv){
	if(this != &pmv){
		vec=pmv.vec;
		usados=pmv.usados;
	}
	return *this;
}


Pila_max_VD::Pila_max_VD(){
  usados = 1;
  VectorDinamico<elemento> aux(1);
  vec=aux;
}


Pila_max_VD::Pila_max_VD(int tama){
  usados = 0;
  VectorDinamico<elemento> aux(tama);
  vec=aux;
}


bool Pila_max_VD::empty(){
	return (usados==0);
}


int Pila_max_VD::size(){
  return vec.dimension();
}


elemento Pila_max_VD::top(){
	if(usados<=0)	//para mostrar el 0 si solo tiene 1 elemento
		return vec[1];
	return vec[usados];
}

int Pila_max_VD::top_max(){
	if(usados<=0)	//Si llegamos al cero , siempre haremos referencia al elemento primero
		return vec[1].maximo;//Nuestro cero es el primero. Ya que en VDG no podemos insertar en la posicion cero, no la usamos.
	else if (usados-1 > 0)
		return vec[usados-1].maximo;
}


void Pila_max_VD::push_max(int elem){
	if(top_max()>elem){
		elemento e(elem,top_max());
		vec.asignar_componente(usados,e);//insertamos
	}else{
		elemento e(elem,elem);
		vec.asignar_componente(usados,e);//insertamos
	}
}

void Pila_max_VD::push(int elem){
	usados++;//Siempre insertamos a partir de la posicion 1º(incluida) , no trabajamos con la pos 0 de VDG.
	if(usados==1){
		elemento e(elem,elem);
		vec.asignar_componente(usados,e);//insertamos
	}else{
		if(vec.dimension()>usados){//Si hay espacio , insertarmos
			push_max(elem);
		}else{//si no hay espacio , ampliamos memoria e insertamos
			vec.redimensionar(vec.dimension()*2);//A falta de espacio redimensionamos
			push_max(elem);
		}
	}
}

void Pila_max_VD::pop(){
	if(usados<=0){//Como no hay elementos...	si es igual a 0 quiere decir que hay 1 elemento no? REPASAR
		usados=0;
		//delete vec;//... borramos el espacio reservado
	}else{
		usados--;
	}
}
/*
ostream& operator<<(ostream& os, const elemento& e){
	os<<"{"<<e.elem<<","<<e.maximo<<"}"<<endl;
}
*/
