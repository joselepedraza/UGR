#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "Semaphore.h"

using namespace std ;
using namespace SEM ;

SEM::Semaphore estanquero=0;
SEM::Semaphore fuma[3]=0;

//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero

void funcion_hebra_estanquero(  ){
	int ingrediente;
	//int existenciast = 50;
	while(/*existenciast != 0*/true){ 	//no para de producir
		ingrediente = aleatorio<0,2>();//estanquero selecciona ingrediente aleatoriamente
		//ingrediente = rand()%3;
		cout << "<\t\tingrediente: " << ingrediente << endl;	//y lo pone en el mostrador
		//existenciast--;
		sem_signal(fuma[ingrediente]);	//envia señal al fumador por si le falta el ingrediente	
		cout << "\t\tEstanquero: Fumador, le falta algo? (espera...)" << endl;
		sem_wait(estanquero);	//esperando a que a algun fumador le falte el ingrediente y lo recoja de la mesa
	}
	
		

}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra

void fumar( int num_fumador )
{
   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

   // informa de que comienza a fumar

    cout << "Fumador " << num_fumador << "  :"
          << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar

    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;

}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador( int num_fumador )
{
   while( true )
   {
	sem_wait(fuma[num_fumador]);	//el fumador coge el ingrediente que le falta
	cout << "\t\tFumador" << num_fumador << ": Coge el ingrediente que le falta..." << endl;
	sem_signal(estanquero);	//cuando coge lo que le dispensa, el estanquero puede reponer
	cout << "El estanquero pone otro ingrediente en el mostrador..." << endl;
	fumar(num_fumador);	//el fumador fuma hasta que le falta un ingrediente
   }
}

//----------------------------------------------------------------------

int main()
{
   // declarar hebras y ponerlas en marcha

	//int n_fum[3];
	thread hebra_fumadores[3], hebra_estanco;	//inicializamos la hebra del estanco
	hebra_estanco = thread(funcion_hebra_estanquero);
	for(int i=0; i<3;i++){//inicializamos las 3 hebras (una por fumador)
		hebra_fumadores[i] = thread(funcion_hebra_fumador, i);
			
	}
	hebra_estanco.join();
	for(int i=0; i<3; i++){	//esperando a que finalicen las hebras
		hebra_fumadores[i].join();

	}
	
	
	return 0;
}
