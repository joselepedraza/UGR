template <class T>
Pila_max_VD<T>::Pila_max_VD(const Pila_max_VD<T>& pmv){
	vec=pmv.vec;
	usados=pmv.usados;
}

template<class T>
Pila_max_VD<T>& Pila_max_VD<T>::operator=(const Pila_max_VD<T> & pmv){
	if(this != &pmv){
		vec=pmv.vec;
		usados=pmv.usados;
	}
	return *this;
}

template <class T>
Pila_max_VD<T>::Pila_max_VD(){
  usados = 0;
  VectorDinamico<T> aux(1);
  vec=aux;  
}


template <class T>
Pila_max_VD<T>::Pila_max_VD(int tama){
  usados = 0;
  VectorDinamico<T> aux(tama);
  vec=aux;  
}

template <class T>
bool Pila_max_VD<T>::empty(){
	return (usados==0);
}

template <class T>
int Pila_max_VD<T>::size(){
  return vec.dimension();
}
/*
template<typename T>
T Pila_max_VD<T>::top(){
	if(usados<0)	//para mostrar el 0 si solo tiene 1 elemento
		return vec[0];
	return vec[usados];
}*/

template<typename T>
T& Pila_max_VD<T>::top(){
	if(usados<0)	//para mostrar el 0 si solo tiene 1 elemento
		return vec[0];
	return vec[usados];
}

template<typename T>
void Pila_max_VD<T>::push(const T &elem){
	usados++;//incrementamos el num. de elementos
	if(vec.dimension()>usados){//Si hay espacio , insertarmos
		vec.asignar_componente(usados,elem);//insertamos
	}else{//si no hay espacio , ampliamos memoria e insertamos
		vec.redimensionar(vec.dimension()*2);//A falta de espacio redimensionamos
		vec.asignar_componente(usados,elem);//insertamos
	}
}

template <class T>
void Pila_max_VD<T>::pop(){
	if(usados<=0){//Como no hay elementos...	si es igual a 0 quiere decir que hay 1 elemento no? REPASAR
		usados=0;
		//delete vec;//... borramos el espacio reservado
	}else{
		usados--;
	}
}
