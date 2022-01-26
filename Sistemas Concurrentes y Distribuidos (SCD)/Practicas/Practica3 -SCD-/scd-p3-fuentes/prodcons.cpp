// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: prodcons.cpp
// Implementación del problema del productor-consumidor con
// un proceso intermedio que recibe mensajes síncronos de forma alterna.
// (versión con un único productor y un único consumidor)
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------


#include <iostream>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <mpi.h>  // includes de MPI

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

// ---------------------------------------------------------------------
// constantes que determinan la asignación de identificadores a roles:
const int
   id_productor          = 0 , // identificador del proceso productor
   id_buffer             = 1 , // identificador del proceso buffer
   id_consumidor         = 2 , // identificador del proceso consumidor
   num_procesos_esperado = 3 , // número total de procesos esperado
   num_items             = 20 ; // numero de items producidos o consumidos

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
// produce los numeros en secuencia (1,2,3,....)

int producir()
{
   static int contador = 0 ;
   sleep_for( milliseconds( aleatorio<10,200>()) );
   contador++ ;
   cout << "Productor ha producido valor " << contador << endl << flush;
   return contador ;
}
// ---------------------------------------------------------------------

void funcion_productor()
{
   for ( unsigned int i= 0 ; i < num_items ; i++ )
   {
      // producir valor
      int valor_prod = producir();
      // enviar valor
      cout << "Productor va a enviar valor " << valor_prod << endl << flush;
      MPI_Ssend( &valor_prod, 1, MPI_INT, id_buffer, 0, MPI_COMM_WORLD );
   }
}
// ---------------------------------------------------------------------

void consumir( int valor_cons )
{
   // espera bloqueada
   sleep_for( milliseconds( aleatorio<10,200>()) );
   cout << "Consumidor ha consumido valor " << valor_cons << endl << flush ;
}
// ---------------------------------------------------------------------

void funcion_consumidor()
{
   int         peticion,
               valor_rec = 1 ;
   MPI_Status  estado ;

   for( unsigned int i=0 ; i < num_items; i++ )
   {
      MPI_Ssend( &peticion,  1, MPI_INT, id_buffer, 0, MPI_COMM_WORLD);
      MPI_Recv ( &valor_rec, 1, MPI_INT, id_buffer, 0, MPI_COMM_WORLD,&estado );
      cout << "Consumidor ha recibido valor " << valor_rec << endl << flush ;
      consumir( valor_rec );
   }
}
// ---------------------------------------------------------------------

void funcion_buffer()
{
   int         valor ,
               peticion ;
   MPI_Status  estado ;
/*

MPI_Status es un tipo estructura con los metadatos de los mensajes:
	- status.MPI_SOURCE: proceso fuente.
	- status.MPI_TAG: etiqueta del mensaje.
*/
   for ( unsigned int i = 0 ; i < num_items ; i++ )
   {
/*
int MPI_Recv( void *buf_rec, int num, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status )

	- Espera hasta recibir un mensaje del proceso source dentro del
	comunicador comm con la etiqueta tag, y escribe los datos en
	posiciones contiguas desde buf_rec.
	- Puesto que se espera a que el emisor envíe, es una recepción
	síncrona. Puesto que al acabar ya se pueden leer en buf_rec
	los datos transmitidos, es una recepción segura.
	- Se pueden dar valores especiales o comodín:
	- Si source es MPI_ANY_SOURCE, se puede recibir un
	mensaje de cualquier proceso en el comunicador
	- Si tag es MPI_ANY_TAG, se puede recibir un mensaje con
	cualquier etiqueta.
	-Los argumentos num y datatype determinan la longitud en
	bytes del mensaje. El objeto status es una estructura con el
	emisor (campo MPI_SOURCE), la etiqueta (campo MPI_TAG).
*/

/*
int MPI_Get_count( MPI_Status *status, MPI_Datatype dtype, int *num );		

	-Escribe en el entero apuntado por num el número de items
	recibidos en una llamada MPI_Recv previa. El receptor debe
	conocer y proporcionar el tipo de los datos (dtype).
*/

/*
int MPI_Ssend( void* buf_emi, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm );

	- Inicia un envío, lee datos y espera el inicio de la recepción
	- Envía los datos (num elementos de tipo datatype almacenados
	a partir de buf_emi) al proceso dest dentro del comunicador
	comm.
	- El entero tag (etiqueta) se transfiere junto con el mensaje, y
	suele usarse para clasificar los mensajes en distintas categorías
	o tipos, en función de sus etiquetas. Es no negativo.
	- Es síncrono y seguro. Tras acabar MPI_Ssend
	- ya se ha iniciado en el receptor una operación de recepción
	que encaja con este envío (es síncrono),
	- los datos ya se han leído de buf_emi y se han copiado a
	otro lugar. Por tanto se puede volver a escribir en buf_emi
	(es seguro)
	- Si la correspondiente operación de recepción usada es
	MPI_Recv, la semántica del paso de mensajes es puramente
	síncrona (existe una cita entre emisor y receptor).
*/
      MPI_Recv( &valor, 1, MPI_INT, id_productor,  0, MPI_COMM_WORLD, &estado );
      cout << "Buffer ha recibido valor " << valor << endl ;

      MPI_Recv ( &peticion, 1, MPI_INT, id_consumidor, 0, MPI_COMM_WORLD, &estado );

      cout << "Buffer va a enviar valor " << valor << endl ;
      MPI_Ssend( &valor,    1, MPI_INT, id_consumidor, 0, MPI_COMM_WORLD);
   }
}

// ---------------------------------------------------------------------

int main( int argc, char *argv[] )
{
  int id_propio, num_procesos_actual; // ident. propio, núm. de procesos

  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );	//escribe en id_propio el num de proc que llama(es el numero de orden dentro del comunicador (en este caso el universal), comienza en 0.
  MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );// escribe el numero de procesos actuales en el comunicador

  if ( num_procesos_esperado == num_procesos_actual )
  {
    if ( id_propio == id_productor )  // si mi ident. es el del productor
      funcion_productor();            //    ejecutar función del productor
    else if ( id_propio == id_buffer )// si mi ident. es el del buffer
      funcion_buffer();               //    ejecutar función buffer
    else                              // en otro caso, mi ident es consumidor
      funcion_consumidor();           //    ejecutar función consumidor
  }
  else if ( id_propio == 0 )  // si hay error, el proceso 0 informa
    cerr << "error: número de procesos distinto del esperado." << endl ;

  MPI_Finalize( );
  return 0;
}
// ---------------------------------------------------------------------
