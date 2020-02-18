#include <cstring>
#include <iostream>
#include <imagen.h>
#include <pgm.h>
using namespace std;

int main(int argc, char * argv[]){
  if(argc != 5){
    cerr << "Introduce los 4 argumentos" << endl;
    return 1;
  }
  else{
    Imagen img1, img2;
    if(!img1.leerImagen(argv[1])){
      cerr << "Error leyendo la imagen " << argv[1] << endl;
      return 1;
    }
    if(!img2.leerImagen(argv[2])){
      cerr << "Error leyendo la imagen " << argv[2] << endl;
      return 1;
    }

    Imagen img_out;
    /*Imagen*/ img_out = img1 + img2;     //p1 = p2 + p3; // equivalente a p1 = p2.operator+(p3);

    /*Imagen img_out;
    img_out = img1.operator+(img2);*/
    //llamada operador suma

    if(*argv[4] == 't'){
      img_out.escribirImagen(argv[3], false);
    }
    else if(*argv[4] == 'b'){
      img_out.escribirImagen(argv[3], true);
    }
    else{
      cerr << "Caracter " << argv[3] << " no valido (t= texto; b= binario).";
      return 1;
    }
  }
}
