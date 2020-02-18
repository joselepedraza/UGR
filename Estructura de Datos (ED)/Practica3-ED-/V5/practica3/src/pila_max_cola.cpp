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

template<class T>
Pila_max_Cola<T>::Pila_max_Cola(const Pila_max_Cola<T> & pmc){
	col=pmc.col;
}

template<class T>
Pila_max_Cola<T>& Pila_max_Cola<T>::operator=(const Pila_max_Cola<T> & pmc){
	if(this != &pmc){
		col=pmc.col;
	}
	return *this;
}

template<class T>
T Pila_max_Cola<T>::top(){
	Cola<T> c1,c2,borra,cola_pila;
	c1=col;
	while(!c1.vacia()){	//Vamos a llegar  hasta el final
		if(c1.num_elementos()==1){
			cola_pila.poner(c1.frente());
		}
		c1.quitar();
	}
	return (cola_pila.frente());
}


//~ template<class T>
//~ T& Pila_max_Cola<T>::top(){
	//~ Cola<T> c1,c2,borra,cola_pila;
	//~ c1=col;
	//~ while(!c1.vacia()){	//Vamos a llegar  hasta el final
		//~ if(c1.num_elementos()==1){
			//~ cola_pila.poner(c1.frente());
		//~ }
		//~ c1.quitar();
	//~ }
	//~ return (cola_pila.frente());
//~ }

template<class T>
void Pila_max_Cola<T>::pop(){
	Cola<T> aux;
	while(col.num_elementos()>1){
		aux.poner(col.frente());
		col.quitar();
	}
	col=aux;
}

template<class T>
void Pila_max_Cola<T>::push(const T& elem){
	col.poner(elem);
}

template<class T>
int Pila_max_Cola<T>::size(){
	return col.num_elementos();
}

template<class T>
bool Pila_max_Cola<T>::empty(){
	return (col.num_elementos()==0);
}
