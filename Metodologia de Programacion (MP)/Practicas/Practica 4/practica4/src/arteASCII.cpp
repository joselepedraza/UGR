//lee imagenes/gio.pgm (formato texto) y la convierte en ascii con los caracteres "@%#*+=-:. "
#include<iostream>
#include <fstream>
#include<imagen.h>
#include <string.h>

using namespace std;

int main() {
  char arteASCII[4501];
  char grises[100];
  char ruta_img[] = "imagenes/";
  char nombrefichero[100];
  char nombrefichero_salida[100];
  Imagen origen;
  char nombre[100];
  string linea_principio;
  string nombrefin;
  int numero_lineas;
  ifstream fentrada;
  ofstream fsalida;


  cout << "Introduce el nombre de la imagen a leer: ";
  cin >> nombre;
  cout << "Introduce el nombre del fichero de cadenas: ";
  cin >> nombrefichero;
  cout << "Introduce el nombre del fichero de salida: ";
  cin >> nombrefichero_salida;

  strcpy(&ruta_img[strlen(ruta_img)], nombre);

  fentrada.open(nombrefichero);

  if (!origen.leerImagen(ruta_img)){
   cerr << "error leyendo la imagen " << ruta_img;
   return 1;
 }

  if(fentrada){
    getline(fentrada, linea_principio);

    fentrada >> numero_lineas;

    for (int i = 1; i <= numero_lineas; i++) {
      fentrada >> grises;

      //strncpy(grises, linea.c_str(), sizeof(grises));

      nombrefin = nombrefichero_salida + to_string(i) + ".txt";

      fsalida.open(nombrefin);

      if(origen.aArteASCII(grises, arteASCII, 4500))
          fsalida << arteASCII;
      else
          fsalida << "La conversi�n no ha sido posible" << endl;

      fsalida.close();
    }
  }

  fentrada.close();
}
