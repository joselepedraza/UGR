/*Partiendo del algoritmo que has usado durante la Práctica 1 para resolver el problema de los
fumadores, abre éste y ejecuta los siguientes cambios propuestos en el problema. Queremos
añadir una nueva hebra a nuestro problema llamada proveedor, que genera un ingrediente en
bucle. Una vez ha generado uno, el proveedor despierta al estanquero y le pasa el ingrediente,
el cual lo colocará en el mostrador y despertará al fumador correspondiente. La hebra
proveedora no generará nuevos ingredientes hasta que se haya retirado del mostrador el
ingrediente ya producido. Las hebras de los fumadores no cambian con respecto al problema
original. Recuerda controlar la sincronización entre todas las hebras mediante el uso de
semáforos para evitar incoherencias en la salida o interbloqueos.*/


#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "Semaphore.h"

using namespace std ;
using namespace SEM ;

SEM::Semaphore proveedor=1;
SEM::Semaphore estanquero=0;
SEM::Semaphore fuma[3]=0;

int ingrediente;

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
	//int ingrediente;
	
	while(true){ 	//no para de poner en la mesa cuando el proveedor actualice el ingrediente

		sem_wait(estanquero); //una vez que le llega el ingrediente, lo dispensa y lo bloqueamos
			cout << "\t\tEl estanquero pone el ingrediente " << ingrediente << " en el mostrador." << endl;
		
			sem_signal(fuma[ingrediente]);	//envia señal al fumador por si le falta el ingrediente	
				cout << "\t\tEstanquero esperando hasta que cogen lo del mostrador" << endl;
			sem_wait(estanquero);	//esperando a que a algun fumador le falte el ingrediente y lo recoja de la mesa
		sem_signal(proveedor);	//una vez recogido de la mesa, el estanquero espera un ingrediente del proveedor
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
	sem_signal(estanquero);	//cuando coge lo que le dispensa, el estanquero puede volver a pedir al proveedor para poner en la mesa 
		cout << "El estanquero pide al proveedor otro ingrediente..." << endl;
	fumar(num_fumador);	//el fumador fuma hasta que le falta un ingrediente
   }
}

//---------------------------------------------------------------------
void funcion_hebra_proveedor(){
	
	while (true){
		sem_wait(proveedor);	//inicializado a 1, produce el primer ingrediente y bloquea
			ingrediente = aleatorio<0,2>();	//genera ingrediente para el estanco
			cout << "<\t\tProvee ingrediente al estanquero: " << ingrediente << endl;
		sem_signal(estanquero);	//una vez producido, el proveedor despierta al estanquero
	}
}

//----------------------------------------------------------------------

int main()
{
   //declarar hebras y ponerlas en marcha
	thread hebra_proveedor;
	thread hebra_fumadores[3], hebra_estanco;

	hebra_proveedor = thread(funcion_hebra_proveedor);	//inicializamos la hebra del proveedor	
	hebra_estanco = thread(funcion_hebra_estanquero);//inicializamos la hebra del estanco
	for(int i=0; i<3;i++){//inicializamos las 3 hebras (una por fumador)
		hebra_fumadores[i] = thread(funcion_hebra_fumador, i);
	}
	
	//esperando a que finalicen las hebras
	hebra_proveedor.join();
	hebra_estanco.join();		
	for(int i=0; i<3; i++){	
		hebra_fumadores[i].join();
	}

	return 0;
}