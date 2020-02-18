#include <iostream>
#include <cstring>
#include <string>
#include "byte.h"
#include "imagen.h"
#include "codificar.h"

using namespace std;

const int MAXNOMBRE = 100;
const int MAXTAM = 256;

void lee_linea(char c[], int tam){
	do{
		cin.getline(c,tam,'\n');
	}while(c[0]=='\0');
}

int main(){
	int opcion;
	Imagen img;
	string nombre_imagen_entrada;
	string localizacion;
	char nombre_imagen[MAXNOMBRE];
	char mensaje[MAXTAM];
	do{
		cout << "Escoge:" << endl;
		cout << " 1-Ocultar" << endl;
		cout << " 2-Revelar" << endl;
		cout << " 3-Salir" << endl;
		cin >> opcion;
		switch(opcion){
			case 1:
				cout << "Introduzca el nombre de la imagen de entrada:" << endl;
				cin >> nombre_imagen_entrada;
				localizacion = "imagenes/";
				localizacion += nombre_imagen_entrada;
				if(img.leerImagen(localizacion.c_str())){
					cout << "Introduzca el nombre de la imagen de salida:" << endl;
					cin >> nombre_imagen;
					cout << "Introduzca el mensaje:";
					lee_linea(mensaje, MAXTAM-1);
					cout << "Ocultando..." << endl;
					if(ocultar(img,mensaje)){
						img.escribirImagen(nombre_imagen);
						cout << "Imagen correctamente ocultada" << endl;
					}else{
						cout << "Error al ocultar" << endl;
					}
				}else{
					cout << "No se pudo obtener imagen de entrada" << endl;
				}
				break;
			case 2:
				cout << "Introduzca el nombre de la imagen de entrada:" << endl;
				cin >> nombre_imagen;
				if(img.leerImagen(nombre_imagen)){
					if(revelar(img,mensaje,MAXTAM)){
						cout << "El mensaje oculto es: ''" << mensaje << "''" << endl;
					}else{
						cout << "Error al revelar" << endl;
					}
				}else{
					cout << "No se pudo obtener imagen de entrada" << endl;
				}
				break;
			case 3:
				cout << "Salió del programa";
				break;
			default:
				cout << "Opción no encotrada" << endl;
				break;
		}
	}while(opcion !=3);
}
