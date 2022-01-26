// -----------------------------------------------------------------------------
// Sistemas Concurrentes y Distribuidos.
// Práctica 2. Introducción a los monitores en C++11.
// Implementado por: Jose Luis Pedraza Román
// archivo: barberiaSU
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

const int num_hebras = 10;  //numero de clientes de la barberia

mutex
   mtx ;  // mutex de escritura en pantalla

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

void EsperarFueraBarberia(int num_cliente)   //funcion esperar a que crezca pelo
{
    // calcular milisegundos aleatorios de duración de la acción de cortar el pelo)
    chrono::milliseconds duracion_crecepelo( aleatorio<20,200>() );
     mtx.lock();
      cout << "\t...Esperando el cliente " << num_cliente <<  " a que crezca pelo..." << "(durante: " << duracion_crecepelo.count() << " milisegundos.)\n " << endl << flush ;
     mtx.unlock();
    // espera bloqueada un tiempo igual a ''duracion_crecepelo" milisegundos
    this_thread::sleep_for( duracion_crecepelo );
}
//----------------------------------------------------------------------

void CortarPeloACliente()   //función cortar pelo de cliente
{
  // calcular milisegundos aleatorios de duración de la acción de cortar el pelo)
  chrono::milliseconds duracion_corte( aleatorio<20,200>() );
  // informa de que comienza a cortar el pelo
  cout << "\t...Cortando pelo durante " << duracion_corte.count() << " milisegundos... " << endl;
  // espera bloqueada un tiempo igual a ''duracion_corte" milisegundos
  this_thread::sleep_for( duracion_corte );
}

// *****************************************************************************
//CLASE PARA MONITOR BARBERIA, SEMÁNTICA SU, 1 BARBERO Y N CLIENTES

class Barberia : public HoareMonitor  //DEFINIR LA CLASE COMO DERIVADA DE TIPO PUBLIC DE HOAREMONITOR
{
 private:
   //Variables permanentes:
   bool pasa; //indica al cliente si puede pasar o no
   //Variables condición
   CondVar sillaCorte;    //cola donde esperan los clientes a que se les corte el pelo
   CondVar colaClientes;  //cola donde esperan los clientes (silla_corte != -1)
   CondVar colaBarbero;   //cola donde espera el barbero (silla_corte == -1 (esta vacío))

 public:                    // constructor y métodos públicos
   Barberia(  ) ;           // constructor
   void cortarPelo(int num_cliente);   // cortar el pelo cliente (cliente)
   void siguienteCliente();     // llamar a siguiente cliente (barbero)
   void finCliente();     //avisar al cliente de que ha terminado (barbero)
} ;
// -----------------------------------------------------------------------------

Barberia::Barberia(  )    //constructor
{
   pasa = false;
   sillaCorte = newCondVar();
   colaClientes = newCondVar();
   colaBarbero = newCondVar();
}
// -----------------------------------------------------------------------------
// función llamada por el consumidor para extraer un dato
void Barberia::cortarPelo(int num_cliente)
{
  cout << "El cliente " << num_cliente << " entra en la barbería." << endl;

  if(!colaBarbero.empty()){ //el cliente despierta al barbero si el barbero está dormido(si su cola esta vacia)
    cout << "El cliente " << num_cliente << " se sienta en la silla " << colaClientes.get_nwt() << " y despierta al barbero."  << endl;
    colaBarbero.signal();
  }

  if(!pasa){  //el cliente se espera si el barbero no le dice que puede pasar
    cout << "El cliente " << num_cliente << " espera en la silla " << colaClientes.get_nwt() << " su turno." << endl;
    colaClientes.wait();
  }

  pasa=false; //cuando pasa, indica a los demas que no pueden pasar

  cout << "\tEl cliente " << num_cliente << " esta sentado en la silla de corte." << endl;
  //el cliente pasa y libera su silla de la sala de espera
  sillaCorte.wait();  //espera hasta que el barbero acabe de cortar el pelo al cliente

  cout << "\tEl cliente " << num_cliente << " se levanta de la silla. " << endl;

}
// -----------------------------------------------------------------------------
void Barberia::siguienteCliente()
{
  if(colaClientes.empty()){   //si no hay clientes el barbero se duerme
    cout << "\t...El barbero duerme..." << endl;
    colaBarbero.wait();
  }
  //cuando haya al menos un cliente el barbero le dice que pase
  cout << "\tEl barbero avisa al siguiente cliente." << endl;
  pasa = true;
  colaClientes.signal();
}
// -----------------------------------------------------------------------------
void Barberia::finCliente()
{
  //el barbero termina de pelar y avisa de que la silla de corte esta disponible
  cout << "\tBarbero termina con el cliente actual. " << endl;
  sillaCorte.signal();
}
// *****************************************************************************
// Funciones de Hebras:

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
        << "\tProblema de la barberia (1 barbero/n clientes, Monitor SU) " << endl
        << "-------------------------------------------------------------------------------" << endl
        << flush ;

      MRef<Barberia> monitor = Create<Barberia>();
      //inicializamos las hebras
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
      return 0;
}
