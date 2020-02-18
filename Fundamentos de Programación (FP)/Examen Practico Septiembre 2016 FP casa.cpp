/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACION
// GRADO EN INGENIERIA INFORMATICA
//
// CURSO 2015-2016
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACION E INTELIGENCIA ARTIFICIAL
//
// Examen Septiembre 2016
// Examen practico
//
// Busqueda por interpolacion
//
// APELLIDOS: 
// NOMBRE: 
// GRUPO: 
//
// ORDENADOR: 
//
/***************************************************************************/
/*
Preguntas
1.Implementa el metodo BusquedaPorInterpolacion
2.Llama en el main al metodo BusquedaPorInterpolacion comprobando los datos
3.Muestra la llamada al metodo
4.Muestra el numero de busquedas, numero de fracasos y aciertos (% incluido) y la repeticion de la busqueda si se desea
*/
/***************************************************************************/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
/////////////////////////////////////////////////////////////////////////////
class SecuenciaEnteros
{
	private:
		static const int TAMANIO = 100; // Numero de casillas disponibles
		int vector_privado[TAMANIO];
		//PRE: 0 <= total_utilizados <= TAMANIO
		int total_utilizados; // Numero de casillas ocupadas
	public:
/***********************************************************************/
// Constructor sin argumentos
		SecuenciaEnteros (void)
		{
			total_utilizados = 0;
		}
/***********************************************************************/
// Metodos de lectura (Get) de los datos individuales
// Devuelve el numero de casillas ocupadas
	int TotalUtilizados (void)
	{
		return (total_utilizados);
	}
// Devuelve el numero de casillas disponibles
	int Capacidad (void)
	{
		return (TAMANIO);
	}
/***********************************************************************/
// A~nade un elemento al vector.
// Recibe: nuevo, el elemento que se va a a~nadir.
//
// PRE: total_utilizados < TAMANIO
// La adicion se realiza si hay espacio para el nuevo elemento.
// El nuevo elemento se coloca al final del vector.
// Si no hay espacio, no se hace nada.
	void Aniade (int nuevo)
	{
		if (total_utilizados < TAMANIO) {
			vector_privado[total_utilizados] = nuevo;
			total_utilizados++;
		}
	}
/***********************************************************************/
// Devuelve el elemento de la casilla "indice"
//
// PRE: 0 <= indice < total_utilizados
	int Elemento (int indice)
	{
		return vector_privado[indice];
	}
/***********************************************************************/


	int BusquedaPorInterpolacion(int buscado, int izda, int dcha){
		int pos;
		//Si los extremos no estan bien la busqueda no se realiza (fracaso)
		if(izda > dcha)
			return -1;
		else{
			bool noEncontrado = true;
			while(noEncontrado){
				pos = ((buscado-vector_privado[izda])/(vector_privado[dcha]-vector_privado[izda]))*(dcha-izda)+izda;
				//En el caso de que al calcular pos se encuentre el buscado se sale del bucle (exito)
				if((vector_privado[izda] == buscado)||(vector_privado[dcha] == buscado))
					noEncontrado = false;
				//Si no se ha encontrado al calcular pos se comprueban unas condiciones
				if(buscado != vector_privado[pos]){
					//Si los extremos no tienen numeros en medio se sale del bucle (fracaso)
					if(izda == dcha-1){
						noEncontrado = false;
						pos = -1;
					}
					//si no,se mueven los extremos
					else{
						izda++;
						dcha--;
					}
					//Una vez aumentados los extremos hay que comprobar que no se de el caso de que los extremos sean el mismo numero, 
					//puesto que en la siguiente interaccion se dividiria entre 0 y eso es un error de ejecucion
					//ESTA COMPROBACION SE HACE AQUI PARA QUE NO SE ENTRE EN EL BUCLE SI SE DIERA ESTA CONDICION
					//SE HACE JUSTO DESPUES DE MOVER LOS EXTREMOS PARA EVITAR EL a/0;
					if(izda == dcha){
						noEncontrado = false;
						if(vector_privado[izda] != buscado)
							pos = -1;
						else
							pos = izda;
					}
				}
				
			}
		}
		return pos;
	}
	
	
	
};
/////////////////////////////////////////////////////////////////////////////
/***************************************************************************/
/***************************************************************************/
int main (void)
{
// Array del que se tomaran los datos para formar la secuencia
	const int NUM_DATOS = 36;
	int datos[]={1,3,5,7,9,10,11,12,13,15,17,19,20,21,23,25,27,29,30,
33,35,37,38,39,41,43,46,47,49,51,53,55,57,58,59,60};
// Formar la secuencia v
	SecuenciaEnteros v;
	for (int i=0; i< NUM_DATOS; i++)
	v.Aniade(datos[i]);
// Mostrar el contenido de v
	for (int i=0; i< v.TotalUtilizados(); i++)
		cout << "Elemento num. " << setw(3) << i
<< ": " << setw(3) << v.Elemento(i) << endl;
		cout << endl;
// EL EXAMEN EMPIEZA AQUI //
	
	int buscado, izda, dcha;
	int numFracasos = 0, numExitos = 0;
	//numBusquedas se pone a 0 porque si no al calcular los porcentajes coje el valor 0 del 0.5 (ej)
	double numBusquedas = 0;
	double porcentajeExito, porcentajeFracaso;
	int posicionEncontrada;
	char tecla;

	do{
		do{
			cout << "Introduce el numero a buscar: ";
			cin >> buscado;
		}
		while(buscado < 0);
		
		do{
			cout << "Introduce el extremo inferior del array: ";
			cin >> izda;
		}
		while(izda < 0);
		
		do{
			cout << "Introduce el extremos superior del array: ";
			cin >> dcha;
		}
		while(dcha < 0);
		
		posicionEncontrada = v.BusquedaPorInterpolacion(buscado,izda,dcha);
		
		if(posicionEncontrada == -1){
			numFracasos++;
			cout << "\nNo se ha encontrado el numero" << endl << endl;
		}
		else{
			numExitos++;
			cout << "\nSe ha encontrado en la posicion: " << posicionEncontrada << endl << endl;
		}
		numBusquedas++;
		
		cout << "Pulsa s para repetir la busqueda, otra tecla para salir: ";	
		cin >> tecla;	
	}
	while((tecla == 'S')||(tecla == 's'));

	porcentajeExito = (numExitos/numBusquedas)*100;
	porcentajeFracaso = (numFracasos/numBusquedas)*100;
	
	cout << "\n\nSe han realizado: " << numBusquedas << " busquedas" << endl;
	cout << "Se han realizado: " << numExitos << " busquedas exitosas (" << porcentajeExito << "%)" << endl;
	cout << "Se han realizado: " << numFracasos << " busquedas fracasadas (" << porcentajeFracaso << "%)" << endl;

	return (0);
}
