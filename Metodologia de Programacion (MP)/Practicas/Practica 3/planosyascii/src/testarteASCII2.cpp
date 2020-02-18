//lee imagenes/gio.pgm y la convierte en ascii con los caracteres "@%#*+=-:. "
#include<iostream>
#include<imagen.h>

using namespace std;

int main(){
    char grises[100];
    char arteASCII[1000000]; // 4500 + el \0
    char nombre[100];
    char caracter;
    int contador = 0;
    char TERMINADOR = 'F';
    Imagen origen;

    cout << "Introduce la ruta de la imagen a leer: ";
    cin >> nombre;

    cout << "Introduce los caracteres con los que imprimir la imagen: ";
    cin >> caracter;

    while(caracter != TERMINADOR && contador < 100){
      grises[contador] = caracter;
      contador++;
      cin >> caracter;
    }


    // Leer la imagen gio.pgm

    if (!origen.leerImagen(nombre)){
	   cerr << "error leyendo la imagen\n";
	   return 1;
    }


    cout << "\nLa imagen en arte ASCII es:\n";
    if(origen.aArteASCII(grises, arteASCII, 1000000))
        cout << arteASCII;
    else
        cout << "La conversi�n no ha sido posible" << endl;

    cout << "Ahora Forzamos que no quepa. Debe aparecer un mensaje de error\n";
    if(origen.aArteASCII(grises, arteASCII, 4199))
        cout << arteASCII;
    else
        cout << "La conversi�n no ha sido posible" << endl;
}
