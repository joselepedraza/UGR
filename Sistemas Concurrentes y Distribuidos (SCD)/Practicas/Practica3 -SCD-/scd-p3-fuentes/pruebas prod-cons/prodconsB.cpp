/*
  Alumno: Raul Del Pozo Moreno
  Grupo D-1
  Ejercicio: Productor-Consumidor con varios productores y consumidores
*/


#include <mpi.h>
#include <iostream>
#include <math.h>
#include <time.h>      // incluye "time"
#include <unistd.h>    // incluye "usleep"
#include <stdlib.h>    // incluye "rand" y "srand"


#define Productor    4
#define Buffer       5
#define Consumidor   6
#define ITERS       20
#define TAM          5

using namespace std;

// ---------------------------------------------------------------------

//Decaracion de funcion
void buffer();
void consumidor(int proceso);
void productor(int proceso);

// ---------------------------------------------------------------------

//Funcion Main
int main(int argc, char *argv[]){
   int rank,size;

   //inicializar MPI, leer identif. de proceso y número de procesos
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   MPI_Comm_size( MPI_COMM_WORLD, &size );

   //inicializa la semilla aleatoria
   srand ( time(NULL) );

   //Comprobamos que se inicializan 10 procesos
   if ( size != 10 ) {
      cout<< "El numero de procesos debe ser 10 "<<endl;
      MPI_Finalize( );
      return 0;
   }
   else{
     //Si el proceso esta entre 0 y 4 es productor
     if (rank <= Productor)
        productor(rank);
     //Si el proceso es el 5 se llama al buffer
     else if ( rank == Buffer )
        buffer();
     //Si no, esta entre 6 y 9, se llama al consumidor
     else
        consumidor(rank);
   }
   //finaliza MPI
   MPI_Finalize( );
   return 0;
}

// ---------------------------------------------------------------------

//Funcion buffer (server)
//Gestiona la interaccion entre los procesos productor-consumidor
void buffer(){
   int        value[TAM] ,
              peticion ,
              pos  =  0,
              rama ;
   MPI_Status status ;

   for( unsigned int i=0 ; i < ITERS*2 ; i++ ){
      if ( pos==0 )      // el consumidor no puede consumir
         rama = 0 ;
      else if (pos==TAM) // el productor no puede producir
         rama = 1 ;
      else{               // ambas guardas son ciertas
         // leer 'status' del siguiente mensaje (esperando si no hay)
         MPI_Probe( MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );

         // calcular la rama en función del origen del mensaje
         //Si el origen va de 0 a 4 es un productor
         if ( status.MPI_SOURCE <= Productor )
            rama = 0 ;
         //Si no es un consumidor
         else
            rama = 1 ;
      }
      switch(rama){
         case 0:
            //Recibimos de cualquier productor y lo diferenciamos por el source
            MPI_Recv( &value[pos], 1, MPI_INT, MPI_ANY_SOURCE, Productor, MPI_COMM_WORLD, &status );
            cout << "Buffer recibe " << value[pos] << " de Productor " << status.MPI_SOURCE << endl << flush;
            pos++;
            break;
         case 1:
            //Recibimos peticion de cualquier consumidor
            MPI_Recv( &peticion, 1, MPI_INT, MPI_ANY_SOURCE, Consumidor, MPI_COMM_WORLD, &status );
            //Enviamos el elemento al consumidor correspondiente
            MPI_Ssend( &value[pos-1], 1, MPI_INT, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD);
            cout << "Buffer envía " << value[pos-1] << " a Consumidor " << status.MPI_TAG << endl << flush;
            pos--;
            break;
      }
   }
}

// ---------------------------------------------------------------------

//Funcion consumidor
//Pide un elemento al buffer para consumirlo
//Se bloquea hasta que recibe el elemento del buffer
void consumidor(int proceso){
   int         value,
               peticion = 1 ;
   float       raiz ;
   MPI_Status  status ;

   //Consumimos la parte proporcional a cada productor
   //si hay que consumir 20 elementos en total, cada consumidor
   //consume 5 elementos (4 consumidores)
   for (unsigned int i=0 ; i<(ITERS/4) ; i++){
      //Pedimos el dato al buffer
      MPI_Send( &peticion, 1, MPI_INT, Buffer, Consumidor, MPI_COMM_WORLD );
      cout << "Consumidor " << proceso << " pide valor al buffer" << endl << flush;
      //Recibimos el dato del buffer al consumidor correspondiente
      MPI_Recv ( &value, 1, MPI_INT, Buffer, Consumidor, MPI_COMM_WORLD,&status );
      cout << "Consumidor " << proceso << " recibe valor " << value << " de Buffer " << endl << flush ;

      // espera bloqueado durante un intervalo de tiempo aleatorio
      // (entre una décima de segundo y un segundo)
      usleep( 1000U * (100U+(rand()%900U)) );

      raiz = sqrt(value) ;
   }
}

// ---------------------------------------------------------------------

//Funcion productor
//Produce un valor y se lo envia a l buffer
//Se bloquea para no saturar el comunicador
void productor(int proceso){
   int value ;

   //Producimos la parte proporcional a cada productor
   //si hay que producir 20 elementos en total, cada productor
   //produce 4 elementos (5 productores)
   for ( unsigned int i=0; i < (ITERS/5) ; i++ ){
      value = i ;
      cout << "Productor " << proceso << " produce valor " << value << endl << flush ;

      // espera bloqueado durante un intervalo de tiempo aleatorio
      // (entre una décima de segundo y un segundo)
      usleep( 1000U * (100U+(rand()%900U)) );

      // enviar 'value'
      //Enviamos el tag del productor al buffer
      MPI_Ssend( &value, 1, MPI_INT, Buffer, Productor, MPI_COMM_WORLD );
   }
}

// ---------------------------------------------------------------------
