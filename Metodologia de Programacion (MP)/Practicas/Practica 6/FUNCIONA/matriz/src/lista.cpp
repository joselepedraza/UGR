#include <string>
#include <cstring>
#include <fstream>
#include "lista.h"

using namespace std;

Lista::Lista(){
  cabecera = 0;
}

Lista::Lista(string valor){
  cabecera = new Celda;
  cabecera -> datos = valor;
  cabecera -> siguiente = 0;
}

/*Lista::~Lista(){
  if(cabecera != 0){
    Celda *p = cabecera->siguiente;
    while(p != 0){
      Celda *p_siguiente = p->siguiente;
      delete p;
      p = p_siguiente;
    }
  delete cabecera;
  cabecera = 0;
  }
}*/

/*Lista::Lista(const Lista &l){
  cabecera = new Celda;
  for(int i=0; i <= l.longitud(); i++){
      cabecera[i] = l.cabecera[i];
  }
}*/

Lista &Lista::operator=(const Lista &l){
    if(&l != this) {
        delete[] this->cabecera;
        this->cabecera = new Celda;
        for (int i = 0; i <= l.longitud(); i++)
            this->cabecera[i] = l.cabecera[i];
    }
    return *this;
}
/*Lista &Lista::operator=(const Lista &l){
    if(&l != this){
      destruir();
      cabecera = l.cabecera;
    }
  return *this;
}*/


void Lista::destruir(){
  if(cabecera != 0){
    Celda *p = cabecera->siguiente;
    while(p != 0){
      Celda *p_siguiente = p->siguiente;
      delete p;
      p = p_siguiente;
    }
  delete cabecera;
  cabecera = 0;
  }
}

void Lista::insertar(string valor){
  if(cabecera != 0){    //para lista no vacia
    Celda *p = cabecera;
    while(p->siguiente !=0){
      p = p->siguiente;
    }
    p->siguiente = new Celda;
    p->siguiente->datos = valor;
    p->siguiente->siguiente = 0;
  }
  else{
    cabecera = new Celda;
    cabecera->siguiente = 0;
    cabecera->datos = valor;
  }
}

string Lista::getCelda(int pos) const{
  Celda *p = cabecera;
  string cadena;

  for (int i = 0; i < pos; i++) {
      p = p->siguiente;
  }

  cadena = p->datos;

  return cadena;
}

int Lista::longitud() const{
  Celda *p = cabecera;
  int numero_celdas = 0;

  while (p != 0) {
    p = p->siguiente;
    numero_celdas++;
  }
  return numero_celdas;
}

/**
 * @brief Construye una lista de celdas enlazadas a partir de la informacion
 * contenida en un fichero.
 * @param nombreFichero ruta del fichero de texto con el contenido de las datoss
 * a insertar en la lista
 * @retval true si ha tenido éxito en la lectura y el formato es el correcto
 * @retval false si se ha producido algún error en la lectura
 *
 * Lee desde disco los elementos almacenados en @a nombreFichero y los guarda
 * en la lista. La función debe asegurarse de que la estructura sigue un patron
 * determinado, y se ha de crear la lista con el numero de elementos que contenga.
 */
bool Lista::leerLista(const char nombrefichero[]){
	ifstream fin;
	fin.open(nombrefichero);
	if(!fin){
		return false;
	}else{
		string grises;
		int lineas;
		getline(fin,grises); //la primera linea se ignora
		fin >> lineas; //leo el numero de datos de grises
		getline(fin,grises); //leer salto de linea
		if (!fin){
			return false;
		}else {
			int i = 0;
			getline(fin,grises); //leer cadena de caracteres
			while ((i < lineas)&&(fin)){
				if (grises != ""){
					insertar(grises);
					i++;
				}
				getline(fin,grises); //leer cadena de caracteres
			}
		}
		fin.close();
	}
	return true;
}
