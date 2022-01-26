// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: prodcons2.cpp
// Implementación del problema del productor-consumidor con
// un proceso intermedio que gestiona un buffer finito y recibe peticiones
// en orden arbitrario
// (versión con multiples prod/cons)
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
    num_prods = 4,
    num_cons = 5,
   ETIQ_BUFFER             = 5,  //numero del proceso buffer
   ETIQ_CONSUMIDOR         = 2, //las etiquetas no son el numero de orden del proceso
   ETIQ_PRODUCTOR          = 1, //sino el identificador de cada rol

   num_procesos_esperados = 10,
   num_items              = 20,  //numero de items a producir
   tam_vector             = 10;

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
int producir()
{
   int contador=0;

   sleep_for( milliseconds( aleatorio<10,100>()) );
   contador++ ;
   //cout << "Productor ha producido valor " << contador << endl << flush;
   return contador ;
}
// ---------------------------------------------------------------------

void funcion_productor(int proc_prod)
{
  int valor;
  //cada productor produce num_items/num_prods
   for ( unsigned int i= 0 ; i < 5/*num_items/num_prods*/; i++ )//cada productor produce 4 elementos (*5 productores)
   {
      //producir
      valor = producir();
      //enviar valor
      cout << "Productor " << proc_prod << " envia el valor " << valor << endl << flush;
      //enviamos el tag del productor al buffer para identificar quien envia el valor
      MPI_Ssend( &valor/*&i*/, 1, MPI_INT, ETIQ_BUFFER, ETIQ_PRODUCTOR, MPI_COMM_WORLD ); //el tag identifiaca al productor y lo enviamos al buffer
   }
}
// ---------------------------------------------------------------------

void consumir( int valor_cons )
{
   // espera bloqueada
   sleep_for( milliseconds( aleatorio<110,200>()) );
   cout << "Consumidor ha consumido valor " << valor_cons << endl << flush ;
}
// ---------------------------------------------------------------------

void funcion_consumidor(int proc_cons)
{
   int         peticion = 1,
               valor_rec;
   MPI_Status  estado;

   //cada consumidor consume num_items/num_cons que le corresponden
   for( unsigned int i=0 ; i < 4/*num_items/num_cons*/; i++ )
   {
     //el cons envia peticion al buffer junto con su etiqueta
      MPI_Ssend( &peticion,  1, MPI_INT, ETIQ_BUFFER, ETIQ_CONSUMIDOR , MPI_COMM_WORLD);
      cout << "Consumidor " << proc_cons << " pide valor al buffer" << endl << flush;
      //pedimos al buffer que envie valor producido al consumidor
      //y la etiqueta de envio del buffer al consumidor sería 0????
      MPI_Recv ( &valor_rec, 1, MPI_INT, ETIQ_BUFFER, 0/*ETIQ_CONSUMIDOR*/, MPI_COMM_WORLD,&estado );
      cout << "Consumidor " << proc_cons << " ha recibido valor " << valor_rec << endl << flush ;
      consumir( valor_rec );
   }
}
// ---------------------------------------------------------------------

void funcion_buffer()
{
   int        buffer[tam_vector],      // buffer con celdas ocupadas y vacías
              valor,  // valor recibido o enviado
              num_celdas_ocupadas = 0, // número de celdas ocupadas
              id_emisor_aceptable ;    // identificador de emisor

   MPI_Status estado ;                 // metadatos del mensaje recibido
/*

MPI_Status es un tipo estructura con los metadatos de los mensajes:
	- status.MPI_SOURCE: proceso fuente.
	- status.MPI_TAG: etiqueta del mensaje.
*/
   for( unsigned int i=0 ; i < 40/*num_items*2*/; i++ )  //ya que se producen 20 y se consumen 20
   {
      // 1. determinar si puede enviar solo prod., solo cons, o todos

      if ( num_celdas_ocupadas == 0 )// si buffer vacío, el consumidor no puede consumir
         id_emisor_aceptable = 0 ;       // $~~~$ solo prod.
      else if ( num_celdas_ocupadas ==tam_vector /*> 0*/ ) // si buffer lleno
         id_emisor_aceptable = 1 ;      // $~~~$ solo cons.
      else{ // si no vacío ni lleno
          // $~~~$ se puede consumir ó producir
          MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);//espera bloqueado hasta que haya algo
          //comprobamos qué emisor es (prod o cons) en funcion del orgigen del mensaje
          //if( estado.MPI_SOURCE <= ETIQ_PRODUCTOR) //si esta entre 0 y num_prods
          if(estado.MPI_TAG == ETIQ_PRODUCTOR)        //recibiremos del productor
            id_emisor_aceptable = 0;
          else                                      //sino, recibiremos peticion del consumidor
            id_emisor_aceptable = 1;
      }


      // 2. recibir un mensaje del emisor aceptables

      switch (id_emisor_aceptable) {
        case 0:{//recibimos del productor
          //recibimos de cualquier productor
          MPI_Recv(&buffer[num_celdas_ocupadas], 1, MPI_INT, MPI_ANY_SOURCE, ETIQ_PRODUCTOR, MPI_COMM_WORLD, &estado);
          cout << "Recibido por buffer el valor " << buffer[num_celdas_ocupadas] << " del productor " << estado.MPI_SOURCE << endl << flush; //identificamos al productor
          num_celdas_ocupadas++;
          break;
        }
        case 1:{//enviamos al consumidor
          //esperamos la peticicion de algun consumidor
          MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, ETIQ_CONSUMIDOR, MPI_COMM_WORLD, &estado);
          //enviamos el valor al consumidor del que hemos recibido la peticion
          MPI_Ssend(&buffer[num_celdas_ocupadas-1], 1, MPI_INT, estado.MPI_SOURCE, 0/*estado.MPI_TAG*/, MPI_COMM_WORLD);
          cout << "Enviado por buffer el valor " << buffer[num_celdas_ocupadas-1] << " al consumidor " << estado.MPI_SOURCE << endl << flush; //identifica al consumidor
          num_celdas_ocupadas--;
          break;
        }
      }
    }
}

// ---------------------------------------------------------------------

int main( int argc, char *argv[] )
{
   int id_propio, num_procesos_actual;

   // inicializar MPI, leer identif. de proceso y número de procesos
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio ); //yo, proceso actual
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual ); //numero de procesos en el comunicador
/*
   if ( num_procesos_esperados == num_procesos_actual )
   {
      // ejecutar la operación apropiada a 'id_propio'
      if ( id_propio < ETIQ_BUFFER) //desde 0 hasta num_prods-1 = productores
         funcion_productor(id_propio);
      else if ( id_propio == ETIQ_BUFFER)
         funcion_buffer();
      else  //es el consumidor hasta el num_prods + num_cons -1
         funcion_consumidor(id_propio);
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_procesos_esperados << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }
*/
  if(num_procesos_actual != num_procesos_esperados){
    if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
    { cout << "el número de procesos esperados es:    " << num_procesos_esperados << endl
           << "el número de procesos en ejecución es: " << num_procesos_actual << endl
           << "(programa abortado)" << endl ;
    }
  }
  else{
    if ( id_propio < ETIQ_BUFFER) //desde 0 hasta num_prods-1 = productores
       funcion_productor(id_propio);
    else if ( id_propio == ETIQ_BUFFER)
       funcion_buffer();
    else  //es el consumidor hasta el num_prods + num_cons -1
       funcion_consumidor(id_propio);
  }

   // al terminar el proceso, finalizar MPI
   MPI_Finalize();
   return 0;
}
