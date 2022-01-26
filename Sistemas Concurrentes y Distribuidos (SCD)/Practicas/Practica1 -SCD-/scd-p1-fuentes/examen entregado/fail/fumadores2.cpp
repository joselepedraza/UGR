#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "Semaphore.h"

using namespace std ;
using namespace SEM ;

Semaphore puede_fumar[2] = {0,0};
Semaphore puede_producir = 0;
Semaphore suministradora = 1;
Semaphore p = 1;
int producto;


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


    while(true){
        sem_wait(puede_producir);
	
	for(int i=0; i<10; i++){
		sem_wait(p);
        	producto = aleatorio<0,1>();
        	cout << "se ha generado el producto " << producto << endl;
        	cout << endl;
        	sem_signal(puede_fumar[producto]);
    	}
	sem_signal(suministradora);
     }
}

void funcion_hebra_suministradora( ){
	
    while(true){
	sem_wait(suministradora);
	cout << "\n\n\nha llegado un nuevo lote de suministros " << flush << endl;
	sem_signal(puede_producir);
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
    cout << endl;

}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador( int num_fumador )
{
  
   while( true ){
    sem_wait(puede_fumar[num_fumador]);
    cout << "El fumador " << num_fumador << " ha recogido el ingrediente " << endl;
    //cout << endl;
    
    sem_signal(p);
    fumar(num_fumador);
   }
}

//----------------------------------------------------------------------

int main(){

   thread Estanquero(funcion_hebra_estanquero),
          Fumador0(funcion_hebra_fumador,0),
          Fumador1(funcion_hebra_fumador,1),
          Suministradora(funcion_hebra_suministradora);

    Estanquero.join();
    Fumador0.join();
    Fumador1.join();
    Suministradora.join();
}
