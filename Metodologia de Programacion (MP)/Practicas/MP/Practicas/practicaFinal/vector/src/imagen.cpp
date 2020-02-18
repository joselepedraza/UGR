#include <iostream>
#include "imagen.h"
#include "pgm.h"
using namespace std;
/// Construye una imagen vacía (0 filas, 0 columnas)
Imagen::Imagen(){
	datos=0;
	nfilas=0;
	ncolumnas=0;
}

//-------Destructor------------------------------------------------------------------------------------------------------------
void Imagen::destruir(){
	if(datos!=0){
		delete []datos;
		datos=0;
		nfilas=0;
		ncolumnas=0;
	}
}
Imagen::~Imagen(){
	destruir();
}
//-----------------------------------------------------------------------------------------------------------------------------

//-------Constructor de copia--------------------------------------------------------------------------------------------------	
	Imagen::Imagen(const Imagen& img){
		nfilas=img.nfilas;
		ncolumnas=img.ncolumnas;
		datos=new byte[nfilas*ncolumnas];
		for(int i=0; i < (nfilas*ncolumnas); i++){
			datos[i]=img.datos[i];
		}		
	}
//-----------------------------------------------------------------------------------------------------------------------------
//------Operador de asignación-------------------------------------------------------------------------------------------------	
	Imagen& Imagen::operator=(const Imagen& img){
		if(&img!=this){
			delete[] this-> datos;
			this->nfilas=img.nfilas;
			this->ncolumnas=img.ncolumnas;
			this-> datos= new byte[nfilas*ncolumnas];
			for(int i=0; i < nfilas*ncolumnas; i++){
				this->datos[i]=img.datos[i];
			}	
		}
		return *this;
	}
//-----------------------------------------------------------------------------------------------------------------------------
/**
@brief Construye una imagen negra de tamaño @a filas x @a columnas
@param filas 	número de filas de la imagen
@param columnas	número de columnas de la imagen

Construye una imagen de tamaño @a filas x @a columnas y pone todos 
sus elementos a 0.
*/
Imagen::Imagen(int filas, int columnas){
	crear(filas,columnas);
}
/**
@brief Crea una imagen negra de tamaño @a filas x @a columnas
@param filas 	número de filas de la imagen
@param columnas	número de columnas de la imagen

Dimensiona la imagen a tamaño @a filas x @a columnas y pone todos 
sus elementos a 0.
*/
void Imagen::crear(int filas, int columnas){
	destruir();
	nfilas = filas;
	ncolumnas = columnas;
	int maximo = filas*columnas;	
	datos = new byte [maximo];	
	for(int i=0; i < (filas*columnas); i++){
		datos[i]=0;
	}
}
/**
@brief Devuelve el número de filas de las imagen
@return el número de filas de la imagen
*/
int Imagen::filas(){
	return nfilas;
}   
/**
@brief Devuelve el número de columnas de las imagen
@return el número de columnas de la imagen
*/
int Imagen::columnas(){
	return ncolumnas;
}
/**
@brief Asigna el valor @a v a la posición (@a x,@a y) de la imagen
@param y 	fila de la imagen
@param x 	columna de la imagen 
@param v 	valor a asignar

Asigna el valor @a v a la posición (@a x,@a y) de la imagen. Dado que la imagen se guarda
como un vector, la posición (@a x,@a y) corresponde a la posición @a y * @c ncolumnas + @a x 
del vector.    
*/
void Imagen::set(int y, int x, byte v){
	int i;		
	i= y* ncolumnas + x;
	datos[i]=v;
}
/**
@brief Devuelve el valor de la posición (@a x,@a y) de la imagen
@param y	 fila de la imagen
@param x	 columna de la imagen 
@return el valor de la posición (@a x,@a y) de la imagen

Devuelve el valor de la posición (@a x,@a y) de la imagen. Dado que la imagen se guarda
como un vector, la posición (@a x,@a y) corresponde a la posición @a y * @c ncolumnas + @a x 
del vector.    
*/
byte Imagen::get(int y, int x){
	int i;		
	i= y* ncolumnas + x;
	return datos[i];
}   
/**
@brief Asigna el valor @a v a la posición @a i de la imagen considerada como vector
@param i 	posición de la imagen considerada como vector
@param v 	valor a asignar

Asigna el valor @a v a la posición @a i de la imagen considerada como vector. La posición @a i 
corresponde con la posición @c y * @c ncolumnas + @c x de la imagen donde @c y representa la 
fila y @c x representa la columna.    
*/
void Imagen::setPos(int i, byte v){
	datos[i]=v;
} 
/**
@brief Devuelve el valor de la posición @a i de la imagen considerada como vector
@param i 	posición de la imagen considerada como vector

Devuelve el valor de la posición @a i de la imagen considerada como vector. La posición @a i 
corresponde con la posición @c y * @c ncolumnas + @c x de la imagen donde @c y representa la 
fila y @c x representa la columna.    
*/
byte Imagen::getPos(int i){
	return datos[i];
}   
/**
@brief Carga una imagen desde un fichero 
@param nombreFichero nombre del fichero que contiene la imagen
@retval true 	si ha tenido éxito en la lectura
@retval false 	si se ha producido algún error en la lectura

Lee desde disco los datos de la imagen llamada @a nombreFichero y la guarda en la memoria. La función debe asegurarse de que la imagen es de un tipo de imagen conocido y de que su tamaño es menor del tamaño máximo permitido (@c MAXDATOS)
*/
bool Imagen::leerImagen(const char nombreFichero[]){
	bool ok=false;		
	if(infoPGM(nombreFichero,nfilas,ncolumnas)==IMG_PGM_BINARIO){
		crear(nfilas,ncolumnas);		
		if(leerPGMBinario(nombreFichero, datos, nfilas, ncolumnas)){
			ok = true;
		}
	}
	if(infoPGM(nombreFichero,nfilas,ncolumnas)==IMG_PGM_TEXTO){
		crear(nfilas,ncolumnas);
		if(leerPGMTexto(nombreFichero, datos, nfilas, ncolumnas)){
			ok = true;
		}
	}
	return ok;
}
/**
@brief Guarda una imagen desde un fichero 
@param nombreFichero nombre del fichero que contiene la imagen
@retval true 	si ha tenido éxito en la escritura
@retval false 	si se ha producido algún error en la escritura
*/
bool Imagen::escribirImagen(const char nombreFichero[]){
	bool ok=false;		
	if(escribirPGMTexto(nombreFichero, datos, nfilas, ncolumnas)){
		ok = true;
	}
	return ok;
}

void Imagen::rotar(){
	int maximo = nfilas*ncolumnas;
	byte* datos_rotar=new byte [maximo];
	int i=1;
	int j=0;
	for(int pos=nfilas*ncolumnas-1; pos>=0; pos--){
		if(j==nfilas){
			j=0;
			i++;
		}
		datos_rotar[pos]=get(j,ncolumnas-i);
		j++;
	}
	int aux = nfilas;
	nfilas = ncolumnas;
	ncolumnas = aux;	
	datos=0;
	datos=datos_rotar;
}
void Imagen::rotacion(int grados, bool sentidoHorario){
	int ngiros;
	switch(grados){
		case 90:
			if(sentidoHorario){	
				ngiros=1;
			}else{
				ngiros=3;
			}
			break;
		case 180:
			ngiros=2;
			break;
		case 270:
			if(sentidoHorario){	
				ngiros=3;
			}else{
				ngiros=1;
			}
			break;
		default:
			ngiros = 0;
			cout << "Nº incorrecto de grados" << endl;
	}
	for(int i=0; i< ngiros; i++){
		rotar();
	}	
}

