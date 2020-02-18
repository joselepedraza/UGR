// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 2. Introducción a los monitores en C++11.
//
// archivo: monitor_Barberia

//SU -> Señalar y Espera urgente : problema del barbero (monitor Barberia Hoare) VARIANTE 2
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
void EsperarFueraBarberia(int num_cliente)   //funcion esperar a que crezca pelo
{
    // calcular milisegundos aleatorios de duración de la acción de cortar el pelo)
    chrono::milliseconds duracion_crecepelo( aleatorio<20,200>() );
     mtx.lock();
      cout << "\t...Esperando el cliente " << num_cliente <<  " a que crezca pelo..." << "(durante: " << duracion_crecepelo.count() << " milisegundos.) \n" << endl << flush ;
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
  cout << "...Cortando pelo durante " << duracion_corte.count() << " milisegundos..." << endl;
   // espera bloqueada un tiempo igual a ''duracion_corte" milisegundos
  this_thread::sleep_for( duracion_corte );
}

// *****************************************************************************
//CLASE PARA MONITOR BARBERIA, SEMÁNTICA SU, 1 BARBERO Y N CLIENTES

class Barberia : public HoareMonitor  //DEFINIR LA CLASE COMO DERIVADA DE TIPO PUBLIC DE HOAREMONITOR
{
 private:
   //Variables permanentes:
   CondVar sillaCorte[num_hebras];  //cola donde esperan los clientes a que se les corte el pelo
   CondVar colaClientes;//cola donde esperan los clientes (silla_corte != -1)
   CondVar colaBarbero[num_hebras];//cola donde espera el barbero (silla_corte == -1 (esta vacío))

 public:                    // constructor y métodos públicos
   Barberia(  ) ;           // constructor
   void cortarPelo(int num_cliente, int num_barbero);   // cortar el pelo a un cliente
   void siguienteCliente(int num_barbero);
   void finCliente(int num_barbero);
} ;
// -----------------------------------------------------------------------------

Barberia::Barberia(  )    //constructor
{

  colaClientes = newCondVar();
  for(int i = 0; i< num_hebras; i++){
   sillaCorte[i] = newCondVar();
   colaBarbero[i] = newCondVar();
  }
}
// -----------------------------------------------------------------------------
// función llamada por el consumidor para extraer un dato
void Barberia::cortarPelo(int num_cliente, int num_barbero)
{
  cout << "El cliente " << num_cliente << " entra en la barbería." << endl;

  if(!colaBarbero[num_barbero].empty()){ //el cliente despierta al barbero si el barbero está dormido(si su cola esta vacia)
    cout << "El cliente " << num_cliente << " se sienta en la silla " << colaClientes.get_nwt() << " y despierta al barbero."  << endl;
    colaBarbero[num_barbero].signal();//avisamos a barbero de que puede pelar
  }

  if(!sillaCorte[num_barbero].empty()){  //el cliente se espera si el barbero esta ocupado
    cout << "El cliente " << num_cliente << " espera en la silla " << colaClientes.get_nwt() << " su turno." << endl;
    colaClientes.wait();
  }
  //cuando la silla esté vacia, el cliente se sienta en la silla
  cout << "\tEl cliente " << num_cliente << " esta sentado en la silla de corte." << endl;
    //el cliente pasa y libera su silla de la sala de espera
  sillaCorte[num_barbero].wait();  //espera hasta que el barbero acabe de cortar el pelo al cliente

  cout << "\tEl cliente " << num_cliente << " se levanta de la silla. " << endl;
}
// -----------------------------------------------------------------------------

void Barberia::siguienteCliente(int num_barbero)
{
  if(colaClientes.empty() && sillaCorte[num_barbero].empty()){
    //si la silla de corte y la cola de clientes estan vacias, el barbero se duerme (espera)
    cout << "\t...El barbero " << num_barbero << " duerme..." << endl;
    colaBarbero[num_barbero].wait();
  }

  //cuando haya al menos un cliente el barbero le dice que pase
  cout << "\tEl barbero avisa al siguiente cliente." << endl;
  colaClientes.signal();

}
// -----------------------------------------------------------------------------
void Barberia::finCliente(int num_barbero)
{
  //el barbero termina de pelar y avisa de que puede pasar el siguiente a la silla de corte
  cout << "\n\tBarbero termina con el cliente actual. " << endl;
  sillaCorte[num_barbero].signal();
}
// *****************************************************************************
// Funciones de Hebras:

void funcion_hebra_barbero( MRef<Barberia> monitor, int num_barbero)
{
  while(true){
    monitor->siguienteCliente(num_barbero);
    CortarPeloACliente();
    monitor->finCliente(num_barbero);
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
      thread hebra_barbero[num_hebras], hebras_clientes[num_hebras];

      //inicializamos las hebras
      for(int i=0; i<num_hebras;i++){
          hebra_barbero[i] = thread(funcion_hebra_barbero, monitor,i);
      }

      //hebra_barbero = thread(funcion_hebra_barbero, monitor);
      for(int i=0; i<num_hebras;i++){
        	hebras_clientes[i] = thread(funcion_hebra_clientes, monitor, i);
      }

      //esperando a que finalicen las hebras(no ocurre nunca)
      //hebra_barbero.join();
     	for(int i=0; i<num_hebras; i++){
     		 hebras_clientes[i].join();
         hebra_barbero[i].join();
     	}

      return 0;
}
