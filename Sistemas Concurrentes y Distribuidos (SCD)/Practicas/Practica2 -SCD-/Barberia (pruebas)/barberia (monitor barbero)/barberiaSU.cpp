// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 2. Introducción a los monitores en C++11.
//
// archivo: fumadores_monitor_Barberia

// Historial:
// Creado en Julio de 2017

//SU -> Señalar y Espera urgente : problema del barbero (monitor Barberia Hoare)
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

   const int num_hebras = 5;  //numero de clientes de la barberia
   //int iprod[num_hebras];
mutex
   mtx ;                 // mutex de escritura en pantalla
//unsigned
   //cont_prod[num_items], // contadores de verificación: producidos
   //cont_cons[num_items]; // contadores de verificación: consumidos

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
void EsperarFueraBarberia(int num_cliente)   //funcion esperar a que crezca pelo
{
    // calcular milisegundos aleatorios de duración de la acción de cortar el pelo)
    chrono::milliseconds duracion_crecepelo( aleatorio<20,200>() );
     mtx.lock();
      cout << "\t...Esperando a que crezca pelo...  " << "(durante: " << duracion_crecepelo.count() << " milisegundos.) " << endl << flush ;
      //cout << "Producido por productor: " << num_prod << "\tel numero:" << iprod[num_prod] << endl << flush ;
     mtx.unlock();

     // espera bloqueada un tiempo igual a ''duracion_crecepelo" milisegundos
    this_thread::sleep_for( duracion_crecepelo );
    //cout << "Ya le ha crecido el pelo al cliente."
}
//----------------------------------------------------------------------

void CortarPeloACliente()   //función cortar pelo de cliente
{
   // calcular milisegundos aleatorios de duración de la acción de cortar el pelo)
  chrono::milliseconds duracion_corte( aleatorio<20,200>() );

   // informa de que comienza a cortar el pelo
  cout << "El cliente se sienta en la silla de corte:"
          << "durante: " << duracion_corte.count() << " milisegundos. " << endl;

   // espera bloqueada un tiempo igual a ''duracion_corte" milisegundos
  this_thread::sleep_for( duracion_corte );

   // informa de que ha terminado de fumar

  //cout << "Cliente " << num_cliente << "  : ya tiene cortado el pelo, se levanta de la silla de corte y espera a que le vuelva a crecer." << endl;

}

// *****************************************************************************
// clase para monitor barberia, semántica SU, 1 barbero y n clientes

class Barberia : public HoareMonitor  //DEFINIR LA CLASE COMO DERIVADA DE TIPO PUBLIC DE HOAREMONITOR
{
 private:
   // variables permanentes
  //int silla_corte;
  //int sillas_esp;
 // colas condicion:
   CondVar sillaCorte;
   CondVar colaClientes;//[num_hebras];//cola donde esperan los clientes (silla_corte != -1)
   CondVar colaBarbero;//  cola donde espera el barber (silla_corte == -1 (esta vacío))

 public:                    // constructor y métodos públicos
   Barberia(  ) ;           // constructor
   void cortarPelo(int num_cliente);   // cortar el pelo a un cliente
   void siguienteCliente(); // insertar un valor (sentencia E) (productor)
   void finCliente(); //espera del estanquero a que se retire el ingrediente del mostrador
} ;
// -----------------------------------------------------------------------------

Barberia::Barberia(  )    //constructor
{
   //silla_corte = 0;    //indica que esta libre
   //sillas_esp = 0;     //indica que esta libre la sala de espera

   //for(int i=0; i < num_hebras;i++)
   //   colaClientes[i]=newCondVar();

   sillaCorte = newCondVar();
   colaClientes = newCondVar();
   colaBarbero = newCondVar();
}
// -----------------------------------------------------------------------------
// función llamada por el consumidor para extraer un dato
void Barberia::cortarPelo(int num_cliente)
{
  if(!sillaCorte.empty()){
    cout << "SillaCorte ocupada, el cliente" << num_cliente <<  " espera en la sala" << endl;
    colaClientes.wait();
  }
  //cuando la silla esté vacia, el cliente se sienta en la silla
  cout << "El Cliente " << num_cliente << " se sienta en la silla." << endl;
    colaBarbero.signal(); //avisamos a barbero de que puede pelar
    sillaCorte.wait();  //silla corte ocupada

}
// -----------------------------------------------------------------------------

void Barberia::siguienteCliente()
{
  if(colaClientes.empty() && sillaCorte.empty()){
    //si la silla de corte y la cola de clientes estan vacias, el barbero se duerme (espera)
    cout << "El Barbero se duerme porque no tiene clientes." << endl;
    colaBarbero.wait();
  }
  //cuando entra un cliente, despierta barbero
  cout << "Barbero despierta y se pone a cortar el pelo." << endl;
  colaClientes.signal();    //DUDA [num_cliente] ????????????
}
// -----------------------------------------------------------------------------
void Barberia::finCliente()
{
  //el barbero termina de pelar y avisa de que puede pasar el siguiente a la silla de corte
  cout << "Barbero termina con el cliente actual. " << endl;
  sillaCorte.signal();
}
// *****************************************************************************
// funciones de hebras

void funcion_hebra_barbero( MRef<Barberia> monitor)
{
  while(true){
    monitor->siguienteCliente();
    CortarPeloACliente();
    monitor->finCliente();
  }
}
// -----------------------------------------------------------------------------

void funcion_hebra_clientes( MRef<Barberia> monitor, int num_cliente)
{
  while(true){
    monitor->cortarPelo(num_cliente);
    EsperarFueraBarberia(num_cliente);
  }
}
// -----------------------------------------------------------------------------

int main()
{
   cout << "-------------------------------------------------------------------------------" << endl
        << "Problema de la barberia (1 barbero/n clientes, Monitor SU " << endl
        << "-------------------------------------------------------------------------------" << endl
        << flush ;
/*
      for(int i=0; i<num_hebras; i++)
        iprod[i]=0;
*/
      MRef<Barberia> monitor = Create<Barberia>();
      //inicializamos las 5 hebras de cada uno
      thread hebra_barbero, hebras_clientes[num_hebras];

      //inicializamos las hebras
      hebra_barbero = thread(funcion_hebra_barbero, monitor);
      for(int i=0; i<num_hebras;i++){
        	hebras_clientes[i] = thread(funcion_hebra_clientes, monitor, i);
      }

      	//esperando a que finalicen las hebras(no ocurre nunca)
      hebra_barbero.join();
     	for(int i=0; i<num_hebras; i++){
     		 hebras_clientes[i].join();
     	}

      // comprobar que cada item se ha producido y consumido exactamente una vez
      //test_contadores() ;

      return 0;
}
