#include <iostream>
#include <set>
#include <ctime>
#include <cstdlib>
using namespace std;

/**
 * @brief Imprime un conjunto de tipo T sobre el flujo de salida
 * @param s: flujo de salida. Es MODIFICADO
 * @param l: el conjunto con los elementos a imprimi
 * */
template <class T>
ostream & operator<<(ostream & s, const set<T> & c){

  typename set<T>::const_iterator i;
  
  for (i=c.begin(); i != c.end(); i++)
      s << (*i) << " ";
  
  return s;
}

/**
 * @brief Inicializar el generador de numero aleatorios
 *        Esta funcion debe ser llamada antes de usar rand
**/

void InicializarSemilla(){
  srand(time(0));
}

/**
 * @brief Genera numero enteros positivos aleatorios en el rango [min,max]
**/

int generaEntero(int min, int max){
    int tam= max -min+1;
    return ((rand()%tam)+min);
}

set<int> unionc(set<int> &c, set<int> &otro){
	set<int> res;
	set<int>::iterator itc;	//tb se podria declarar con auto dentro del for
	
	for(itc=c.begin(); itc!=c.end(); ++itc){
		if(otro.count(*itc))
			res.insert(*itc);
	}

	return res;
}

set<int> difsim(set<int> &c, set<int> &otro){	//elementos que estan en c o cotro pero no en los dos
	set<int> res;
	set<int>::iterator itc;

	for(itc=c.begin(); itc!=c.end();++itc){
		if(otro.find(*itc)==otro.end())		//si esta en c y no en otro, insertar
			res.insert(*itc);
	}

	for(itc=otro.begin(); itc!=otro.end();++itc){
		if(c.find(*itc)==c.end())		//si esta en otro y no en c, insertar
			res.insert(*itc);
	}

	return res;
}
/*
set<int> nmayores(set<int> &c, set<int> &otro, int n){
	set<int> cunion = unionc(c,otro);
	set<int> res;
	set<int>::iterator ituni;
	for(
}*/


int main(){
  
  set<int> c;
  set<int> cotro;
  set<int> res_union, res_difsim;

  InicializarSemilla();

  for (int i=0;i<10;i++)
    cotro.insert(generaEntero(1,100)); //inserta un entero generado aleatoriamente en el rango 1-100
  cout<<endl<<cotro;  

  for (int i=0;i<10;i++)
    c.insert(generaEntero(1,100)); //inserta un entero generado aleatoriamente en el rango 1-100
  cout<<endl<<c;


//prueba union
res_union = unionc(c,cotro);
cout<<"\n\tEl resultado de la unión de los dos conjuntos es: "<<endl<<res_union<<endl;

//prueba intersección
res_difsim = difsim(c,cotro);
cout<<"\n\tEl resultado de la difsim de los dos conjuntos es: "<<endl<<res_difsim<<endl;


}  
