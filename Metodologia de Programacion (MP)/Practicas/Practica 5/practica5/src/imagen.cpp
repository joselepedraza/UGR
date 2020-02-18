#include <iostream>
#include <imagen.h>
#include <pgm.h>
#include <lista.h>
#include <byte.h>
#include <fstream>
#include <cstring>
using namespace std;

Imagen::Imagen() {
  nfilas = 0;
  ncolumnas = 0;
  datos = 0;
}

Imagen::Imagen(int filas, int columnas) {
  datos = 0;
  crear(filas, columnas);
}

void Imagen::crear(int filas, int columnas) {
  if(datos !=0){				//antes de crear una imagen debemos destruirla
			destruir();
	}
	nfilas = filas;
	ncolumnas = columnas;
	datos = new byte[filas*columnas];

	for(int i = 0; i<filas*columnas; i++){
		datos[i] = 0;
	}
}

void Imagen::destruir(){
	nfilas = ncolumnas = 0;

	if (datos != 0){
		delete [] datos;
	}
}

int Imagen::filas() {
  return nfilas;
}

int Imagen::columnas() {
  return ncolumnas;
}

void Imagen::set(int y, int x, byte v) {
  //int columnas = columnas();
  int pos_v = y*ncolumnas+x;

  setPos(pos_v, v);
}

byte Imagen::get(int y, int x) {
  byte valor;
  //int columnas = Imagen.columnas();

  valor = getPos(y*ncolumnas+x);

  return valor;

}

void Imagen::setPos(int i, byte v) {
  datos[i] = v;
}

byte Imagen::getPos(int i){
  byte valor;
  valor = datos[i];
  return valor;
}

bool Imagen::leerImagen(const char nombreFichero[]) {
  bool imagen_leida = false;
  if (infoPGM(nombreFichero, nfilas, ncolumnas) == IMG_PGM_BINARIO) {
    crear(nfilas, ncolumnas);
    if (leerPGMBinario(nombreFichero, datos, nfilas, ncolumnas)) {
      imagen_leida = true;
    }
  }
  else if(infoPGM(nombreFichero, nfilas, ncolumnas) == IMG_PGM_TEXTO){
    crear(nfilas, ncolumnas);
    if(leerPGMTexto(nombreFichero, datos, nfilas, ncolumnas)){
      imagen_leida = true;
    }

  }

  return imagen_leida;
}

bool Imagen::escribirImagen(const char nombreFichero[], bool esBinario) {
  if(esBinario == true) {
    if(escribirPGMBinario(nombreFichero, datos, nfilas, ncolumnas)){
      esBinario = true;
    }
    else esBinario = false;
  }
  else if (esBinario == false){
    if(escribirPGMTexto(nombreFichero, datos, nfilas, ncolumnas)){
      esBinario = true;
    }
    else esBinario = false;
  }
  return esBinario;
}

Imagen Imagen::plano(int k) {
  Imagen nueva;

  nueva.crear(nfilas, ncolumnas);
  for (int i = 0; i < (nfilas*ncolumnas); i++){
    if (getbit(getPos(i),k)){
      nueva.setPos(i, 0x80);
    } else {
      nueva.setPos(i,0);
    }
  }
  return nueva;
}
bool Imagen::aArteASCII(const char grises[], char arteASCII[], int maxlong){  //maxlong: numero de caracteres maximo que puede almacenar arteASCII
  int cuantos_g = strlen(grises);     //cuenta cuantos hay, numero cardinal
  int contador_c = 0;
  bool leido = true;
    for(int i = 0; i < filas(); i++){
      for(int j= 0; j < columnas() + 1; j++){
        arteASCII[contador_c]=grises[(get(i,j)*cuantos_g)/256];    //256 para que quepa el \0 final, que cierra la imagen
        if(j == columnas()){
          arteASCII[contador_c] = '\n';
        }
        if(i == filas()*columnas()){
          arteASCII[contador_c + 1] = '\0';
        }
        contador_c++;
      }
    }
    if(contador_c >= maxlong){
      leido = false;
    }
    return leido;
  }

  bool Imagen::listaAArteASCII(const Lista celdas) {
    bool convertidos = true;
    char *arteASCII = new char [nfilas * (ncolumnas+1)+1];
    string nombrefichero;

    ofstream fsalida;

    for (int i = 0; i < celdas.longitud(); i++) {
      nombrefichero = "ascii" + to_string(i) + ".txt";

      fsalida.open(nombrefichero);

      if(fsalida){
        aArteASCII(celdas.getCelda(i).c_str(), arteASCII, nfilas * (ncolumnas+1)+1);
        fsalida << arteASCII;
      }
      else {
          fsalida << "La conversi�n no ha sido posible" << endl;
          convertidos = false;
          return 1;
      }

      fsalida.close();
    }
    delete [] arteASCII;
    return convertidos;
  }
