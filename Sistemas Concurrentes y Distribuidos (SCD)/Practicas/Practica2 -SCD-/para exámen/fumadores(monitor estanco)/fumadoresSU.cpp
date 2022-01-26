// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 2. Introducción a los monitores en C++11.
//
// archivo: fumadores_monitor_estanco

// Historial:
// Creado en Julio de 2017

//SU -> Señalar y Espera urgente : problema de los fumadore (monitor estanco Hoare)
// -----------------------------------------------------------------------------


#include <iostream>
#include <iomanip>
#include <cassert>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include "HoareMonitor.hpp"

using namespace std ;
using namespace HM;

   const int num_hebras = 3;  //3 porque es el numero de fumadores

mutex
   mtx ;                 // mutex de escritura en pantalla
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

//**********************************************************************

//----------------------------------------------------------------------
int ProducirIngrediente()
{
     int ing;
     this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
     ing = aleatorio<0,2>();
     mtx.lock();
      cout << "\t--producido-- : " << ing << endl << flush ;
     mtx.unlock();

     return ing;
}
//----------------------------------------------------------------------

void Fumar( int num_fumador )
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
// *****************************************************************************
// clase para monitor fumadores, version LIFO, semántica SU, 3 fumadores y 1 estanquero

class Estanco : public HoareMonitor  //DEFINIR LA CLASE COMO DERIVADA DE TIPO PUBLIC DE HOAREMONITOR
{
 private:
 int mostrador;               // variables permanentes
 // colas condicion:
   CondVar colaFum[3];        //  cola donde esperan los fumadores (mostrador == 0,1,2)
   CondVar colaEstanquero;    //  cola donde espera el estanquero (mostrador == -1 (esta vacío))

 public:                    // constructor y métodos públicos
   Estanco(  ) ;           // constructor
   void poner_ingrediente(int ing);   // poner un ingrediente concreto en el mostrador
   void obtener_ingrediente( int ing); // insertar un valor (sentencia E) (productor)
   void esperar_recogida(); //espera del estanquero a que se retire el ingrediente del mostrador
} ;
// -----------------------------------------------------------------------------

Estanco::Estanco(  )
{
   mostrador = -1;
   colaFum[0] = newCondVar();
   colaFum[1] = newCondVar();
   colaFum[2] = newCondVar();
   colaEstanquero = newCondVar();
}
// -----------------------------------------------------------------------------
// función llamada por el consumidor para extraer un dato
void Estanco::poner_ingrediente(int ing)
{
    mostrador = ing;    //pone un ingrediente en el mostrador
    colaFum[ing].signal();  //habilita al un fumador que le corresponda ese ingrediente
}
// -----------------------------------------------------------------------------

void Estanco::obtener_ingrediente( int num_fum)
{
    if(mostrador != num_fum)    //aseguramos que lo coja el fumador que esta esperando ese ingrediente
      colaFum[num_fum].wait();  //hacemos esperar al estanqero que no necesita ese ingrediente en su cola
    mostrador=-1; //indicamos que ya se ha cogido el ing y que mostrador esta vacio
    colaEstanquero.signal();  //indicamos al estanquero que puede reponer ingrediente en el mostrador
}
// -----------------------------------------------------------------------------
void Estanco::esperar_recogida()
{
    if(mostrador!=-1)
      colaEstanquero.wait();
}
// *****************************************************************************
// funciones de hebras

void funcion_hebra_estanquero( MRef<Estanco> monitor)
{

  while(true){
    int ingrediente = ProducirIngrediente();
    monitor->poner_ingrediente(ingrediente);
    cout << "\tEstanquero espera a que retiren ingrediente: " << ingrediente << endl;
    monitor->esperar_recogida();
  }
}
// -----------------------------------------------------------------------------

void funcion_hebra_fumadores( MRef<Estanco> monitor, int num_fum)
{
  while(true){
    monitor->obtener_ingrediente(num_fum);
    Fumar(num_fum);
  }
}
// -----------------------------------------------------------------------------

int main()
{
   cout << "-------------------------------------------------------------------------------" << endl
        << "Problema de los fumadores (1 estanquero/3fumadores, Monitor SU " << endl
        << "-------------------------------------------------------------------------------" << endl
        << flush ;

      MRef<Estanco> monitor = Create<Estanco>();
      //inicializamos las 5 hebras de cada uno
      thread hebra_estanc, hebras_fum[num_hebras];

      //inicializamos las hebras
      hebra_estanc = thread(funcion_hebra_estanquero, monitor);
      for(int i=0; i<num_hebras;i++){
        	hebras_fum[i] = thread(funcion_hebra_fumadores, monitor, i);
      }

      	//esperando a que finalicen las hebras(no ocurre nunca)
      hebra_estanc.join();
     	for(int i=0; i<num_hebras; i++){
     		 hebras_fum[i].join();
     	}

      return 0;
}
