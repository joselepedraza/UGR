// Lee la imagen imagenes/giotexto.pgm (formato binario) y extrae el plano 6 en plano6.pgm formato texto)
// y el plano 0 en plano.pgm (formato texto)
#include<iostream>
#include<imagen.h>

using namespace std;

int main(int argc, char *argv[]){

    Imagen origen, plano;

	// Leer la imagen giotexto.pgm (binario)
	if (!origen.leerImagen("imagenes/giotexto.pgm")){
		cerr << "error leyendo imagenes/giotexto.pgm\n";
		return 1;
	}

	plano = origen.plano(6);

	// Guardar la imagen plano en el fichero plano6.pgm (texto)
	if (plano.escribirImagen("plano6.pgm", false)){
		// si todo va bien
		cout << "plano6.pgm guardado correctamente \n";
		cout << "usa: display plano6.pgm para ver el resultado\n";
	} else { // si error
		cerr << "Error guardando la imagen plano6.pgm\n";
		return 1;
	}

	plano = origen.plano(0);

	// Guardar la imagen plano en el fichero plano0.pgm (texto)
	if (plano.escribirImagen("plano0.pgm", false)){
		// si todo va bien
		cout << "plano0.pgm guardado correctamente \n";
		cout << "usa: display plano0.pgm para ver el resultado\n";
	} else { // si error
		cerr << "Error guardando la imagen plano0.pgm\n";
		return 1;
	}

	return 0;
}
