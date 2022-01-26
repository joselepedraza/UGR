// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: prodcons2.cpp
// Implementación del problema del productor-consumidor con
// un proceso intermedio que gestiona un buffer finito y recibe peticiones
// en orden arbitrario
// (versión con un único productor y un único consumidor)
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <mpi.h>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
   num_productores       = 4 ,
   num_consumidores      = 5 ,
   id_buffer             = num_productores,
   num_procesos_esperado = num_productores + num_consumidores + 1 ,
   num_items             = 20,
   num_items_prod        = num_items/num_productores,
   num_items_cons        = num_items/num_consumidores,
   tam_vector            = 10;

int resultado;

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
// ---------------------------------------------------------------------
// ptoducir produce los numeros en secuencia (1,2,3,....)
// y lleva espera aleatorio
int producir(int id_prod)
{
   static int contador = 0 ;
   sleep_for( milliseconds( aleatorio<10,100>()) );
   resultado = id_prod*num_items_prod + contador;
   contador++ ;
   cout << "[" << id_prod << "]produce: " << resultado << endl << flush;
   return resultado ;
}
// ---------------------------------------------------------------------

void funcion_productor(int prod)
{
   for ( unsigned int i=0 ; i < num_items_prod ; i++ )
   {
      // producir valor
      int valor_prod = producir(prod);
      // enviar valor
      cout << "Produc[" << prod << "]enviar: " << valor_prod << endl << flush;
      MPI_Ssend( &valor_prod, 1, MPI_INT, id_buffer, 0, MPI_COMM_WORLD );
      //LA ETIQUETA 0 DICE QUE EL MENSAJE VIENE DE UN PRODUCTOR
   }
   cout << "*****Se recoge productor " << prod << endl << flush ;
}
// ---------------------------------------------------------------------

void consumir( int valor_cons )
{
   // espera bloqueada
   sleep_for( milliseconds( aleatorio<100,200>()) );
   cout << "			Consumido: " << valor_cons << endl << flush ;
}
// ---------------------------------------------------------------------

void funcion_consumidor(int cons)
{
   int         peticion = 1,
               valor_rec = 1 ;
   MPI_Status  estado ;

   for( unsigned int i=0 ; i < num_items_cons; i++ )
   {
      cout << "ITERACION " << i << "de consumidor" << cons << endl << flush ;
      MPI_Ssend( &peticion,  1, MPI_INT, id_buffer, 1, MPI_COMM_WORLD);
      cout << "			Cons[" << cons << "]recibe respuesta" << endl << flush ;
      MPI_Recv ( &valor_rec, 1, MPI_INT, id_buffer, 1, MPI_COMM_WORLD, &estado );
      cout << "			Cons[" << cons << "]recibido valor: " << valor_rec << endl << flush ;
      consumir( valor_rec );
      //LA ETIQUETA 1 DICE QUE EL MENSAJE VIENE DE UN RECEPTOR
   }
   cout << "*****Se recoge consumidor " << cons << endl << flush ;
}
// ---------------------------------------------------------------------

void funcion_buffer()
{
   int        buffer[tam_vector],      // buffer con celdas ocupadas y vacías
              valor,                   // valor recibido o enviado
              primera_libre       = 0, // índice de primera celda libre
              primera_ocupada     = 0, // índice de primera celda ocupada
              num_celdas_ocupadas = 0, // número de celdas ocupadas
              id_emisor_aceptable ;    // identificador de emisor aceptable
   MPI_Status estado, est ;                 // metadatos del mensaje recibido

   for( unsigned int i=0 ; i < num_items*2 ; i++ )
   {
      // 1. determinar si puede enviar solo prod., solo cons, o todos

      if ( num_celdas_ocupadas == 0 ){               // si buffer vacío
         MPI_Probe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &est);
         id_emisor_aceptable = est.MPI_SOURCE;
         cout << "Prod["<< id_emisor_aceptable << "]debe escribir pues celdas ocupadas = 0" << endl << flush;
      }
      else if ( num_celdas_ocupadas == tam_vector ){ // si buffer lleno
         MPI_Probe(MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &est) ;      // $~~~$ solo cons.
         id_emisor_aceptable = est.MPI_SOURCE;
      }
      else{
         MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &est);                                        // si no vacío ni lleno
         id_emisor_aceptable = est.MPI_SOURCE ;     // $~~~$ cualquiera
         cout << "Cualquier prcoceso es aceptable: " << id_emisor_aceptable << " ( el numero de celdas ocupadas es: " << num_celdas_ocupadas << endl << flush ;
      }

      // 2. recibir un mensaje del emisor o emisores aceptables

      MPI_Recv( &valor, 1, MPI_INT, id_emisor_aceptable, MPI_ANY_TAG, MPI_COMM_WORLD, &estado );
      cout << "Se recibe un mensaje de proceso : " << id_emisor_aceptable << endl << flush;

      // 3. procesar el mensaje recibido

      if( estado.MPI_SOURCE < num_productores ){ // leer emisor del mensaje en metadatos
            buffer[primera_libre] = valor ;
            primera_libre = (primera_libre+1) % tam_vector ;
            num_celdas_ocupadas++ ;
            cout << "--------Buffer recibe: " << valor << endl << flush ;
      }

      else{ // si ha sido el consumidor: extraer y enviarle
            valor = buffer[primera_ocupada] ;
            primera_ocupada = (primera_ocupada+1) % tam_vector ;
            num_celdas_ocupadas-- ;
            cout << "--------Buffer enviar: " << valor << endl << flush ;
            MPI_Ssend( &valor, 1, MPI_INT, id_emisor_aceptable, 1, MPI_COMM_WORLD);
      }
   }
}

// ---------------------------------------------------------------------

int main( int argc, char *argv[] )
{
   int id_propio, num_procesos_actual;

   // inicializar MPI, leer identif. de proceso y número de procesos
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );

   if ( num_procesos_esperado == num_procesos_actual )
   {
      // ejecutar la operación apropiada a 'id_propio'
      if ( id_propio < num_productores ){
         cout << "Se lanza un productor con id: " << id_propio << endl;
         funcion_productor(id_propio);
      }
      else if ( id_propio == num_productores ){
         cout << "Se lanza el proceso buffer" << endl;
         funcion_buffer();
      }
      else if((id_propio > num_productores) && (id_propio < num_procesos_esperado) ){
         cout << "Se lanza un consumidor con id: " << id_propio << endl ;
         funcion_consumidor(id_propio - num_productores);
      }
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_procesos_esperado << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   // al terminar el proceso, finalizar MPI
   MPI_Finalize( );
   return 0;
}
