// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Seminario 2. Introducción a los monitores en C++11.
//
// archivo: monitor_Barberia

//SU -> Señalar y Espera urgente : problema del barbero (monitor Barberia Hoare) VARIANTE
// -----------------------------------------------------------------------------

/*  VARIANTE:
Realiza los cambios necesarios en el algoritmo para que al llegar un cliente nuevo a la barbería,
si el barbero está ocupado pelando a otro cliente y la sala de espera no está vacía, entonces el cliente
salga a esperar a la calle en lugar de sentarse en la sala de espera. Para representar la espera en la
calle, basta indicar a la hebra que duerma un tiempo aleatorio y luego vuelva a entrar.

*/

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
      cout << "\t...Esperando el cliente " << num_cliente <<  " fuera de la barbería..." << "(durante: " << duracion_crecepelo.count() << " milisegundos.) \n" << endl << flush ;
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
   CondVar sillaCorte;  //cola donde esperan los clientes a que se les corte el pelo
   CondVar colaClientes;//cola donde esperan los clientes (silla_corte != -1)
   CondVar colaBarbero;//cola donde espera el barbero (silla_corte == -1 (esta vacío))

 public:                    // constructor y métodos públicos
   Barberia(  ) ;           // constructor
   void cortarPelo(int num_cliente);   // cortar el pelo a un cliente
   void siguienteCliente();
   void finCliente();
} ;
// -----------------------------------------------------------------------------

Barberia::Barberia(  )    //constructor
{
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
    colaBarbero.signal();//avisamos a barbero de que puede pelar
  }
//el cliente se espera fuera si el barbero está ocupado y la cola de clientes no está vacía
/*  if(!sillaCorte.empty() && !colaClientes.empty()){
    cout << "El barbero esta ocupado y la sala no esta vacia" << endl;
    EsperarFueraBarberia(num_cliente);
    //colaClientes.wait();
  }

  if(!sillaCorte.empty() && colaClientes.empty()){  //el cliente se espera si el barbero esta ocupado (en la sala de espera)
    cout << "El cliente " << num_cliente << " espera en la silla " << colaClientes.get_nwt() << " su turno." << endl;
    colaClientes.wait();
  }
*/
  if(!sillaCorte.empty()){  //si el barbero esta ocupado
    cout << "El barbero esta ocupado " << endl;
    if(!colaClientes.empty()){  //y la sala de espera no esta vacia
      cout << " y la sala no esta vacia " << endl;
      EsperarFueraBarberia(num_cliente);  //el cliente espera fuera durante un tiempo aleatorio
      colaClientes.wait();  //se incorpora a la sala de espera
    }
    else{ //si el barbero esta ocupado y la sala de espera está vacía
      cout << "El cliente " << num_cliente << " espera en la silla " << colaClientes.get_nwt() << " su turno." << endl;
      colaClientes.wait();  //el cliente pasa directamente a la sala de espera
    }
  }


  //cuando la silla esté vacia, el cliente se sienta en la silla
  cout << "\tEl cliente " << num_cliente << " esta sentado en la silla de corte." << endl;
    //el cliente pasa y libera su silla de la sala de espera
  sillaCorte.wait();  //espera hasta que el barbero acabe de cortar el pelo al cliente

  cout << "\tEl cliente " << num_cliente << " se levanta de la silla. " << endl;
}
// -----------------------------------------------------------------------------

void Barberia::siguienteCliente()
{
  if(colaClientes.empty() && sillaCorte.empty()){
    //si la silla de corte y la cola de clientes estan vacias, el barbero se duerme (espera)
    cout << "\t...El barbero duerme..." << endl;
    colaBarbero.wait();
  }

  //cuando haya al menos un cliente el barbero le dice que pase
  cout << "\tEl barbero avisa al siguiente cliente." << endl;
  colaClientes.signal();

}
// -----------------------------------------------------------------------------
void Barberia::finCliente()
{
  //el barbero termina de pelar y avisa de que puede pasar el siguiente a la silla de corte
  cout << "\n\tBarbero termina con el cliente actual. " << endl;
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
        << "\tProblema de la barberia (1 barbero/n clientes, Monitor SU) VARIANTE " << endl
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
