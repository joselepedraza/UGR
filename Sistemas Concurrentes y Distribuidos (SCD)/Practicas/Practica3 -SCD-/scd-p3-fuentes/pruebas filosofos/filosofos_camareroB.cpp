/*
  Alumno: Raul Del Pozo Moreno
  Grupo D-1
  Ejercicio: Productor-Consumidor con varios productores y consumidores
*/

#include <iostream>
#include <time.h>      // incluye "time"
#include <unistd.h>    // incluye "usleep"
#include <stdlib.h>    // incluye "rand" y "srand"
#include <mpi.h>

#define Filosofo_Sienta 0
#define Filosofo_Levanta 3
#define Filosofo 4
#define Tenedor 1
#define Camarero 10

using namespace std;

void filosofo( int id, int nprocesos);
void tenedor ( int id, int nprocesos);
void camarero();

// ---------------------------------------------------------------------

int main( int argc, char** argv ){
   int rank, size;

   srand(time(0));
   //Iniciamos los procesos
   MPI_Init( &argc, &argv );
   //Obtenemos el proceso que se va a ejecutar
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   //Obtenemos el total de procesos
   MPI_Comm_size( MPI_COMM_WORLD, &size );

   //Si el total de procesos no es correcto terminamos
   if(size!=11)
   {
      cout<<"El numero de procesos debe ser 11" << endl << flush ;
      MPI_Finalize( );
      return 0;
   }
   //Si el numero de procesos es correcto
   else{
     //Si el proceso es par el proceso es un filosofo
     if (rank == 10)
        camarero();
     else if ((rank%2) == 0)
        filosofo(rank,size-1);
    //Si el proceso es impar el proceso es un tenedor
     else
        tenedor(rank,size-1);
    }
   //Terminamos los procesos
   MPI_Finalize( );
   return 0;
}

// ---------------------------------------------------------------------

void filosofo( int id, int nprocesos ){
  int izq = (id+1) % nprocesos;
  int der = ((id+nprocesos)-1) % nprocesos;

  while(true){
    // Piensa (espera bloqueada aleatorio del proceso)
    cout << "filosofo " << id << " PENSANDO" << endl << flush;
    // espera bloqueado durante un intervalo de tiempo aleatorio
    // (entre una décima de segundo y un segundo)
    usleep( 1000U * (100U+(rand()%900U)) );

    //Pide permiso al camarero para sentarse
    MPI_Ssend(NULL, 0, MPI_INT, Camarero, Filosofo_Sienta, MPI_COMM_WORLD);

    // Solicita tenedor izquierdo
    //filosofo envia peticion al tenedor izq y se bloquea hasta que el tenedor lo recibe
    //NULL porque no envia nada
    cout << "filosofo "<<id<< " solicita tenedor izq ..." << izq << endl << flush;
    MPI_Ssend(NULL, 0, MPI_INT, izq, 0, MPI_COMM_WORLD);

    // Solicita tenedor derecho
    //filosofo envia peticion al tenedor der y se bloquea hasta que el tenedor lo recibe
    cout <<"filosofo "<<id<< " coge tenedor der ..." << der << endl << flush;
    MPI_Ssend(NULL, 0, MPI_INT, der, 0, MPI_COMM_WORLD);

    //Duerme x tiempo
    cout<<"filosofo "<<id<< " COMIENDO"<<endl<<flush;
    sleep((rand() % 3)+1);  //comiendo

    // Suelta el tenedor izquierdo
    //filosofo avisa a tenedor izquierdo que deja de usarlo
    cout <<"filosofo "<<id<< " suelta tenedor izq ..." << izq << endl << flush;
    MPI_Ssend(NULL, 0, MPI_INT, izq, 0, MPI_COMM_WORLD);

    // Suelta el tenedor derecho
    //filosofo avisa a tenedor derecho que deja de usarlo
    cout <<"filosofo "<<id<< " suelta tenedor der ..." << der << endl << flush;
    MPI_Ssend(NULL, 0, MPI_INT, der, 0, MPI_COMM_WORLD);

    //Se levanta
    MPI_Ssend(NULL, 0, MPI_INT, Camarero, Filosofo_Levanta, MPI_COMM_WORLD);

  }
}

// ---------------------------------------------------------------------

void tenedor(int id, int nprocesos){
  int buf;  //No se usa
  MPI_Status status;
  int Filo; //Aqui almacenamos el filosofo que pide y suelta el tenedor

  while( true ) {
    // Espera una peticion desde cualquier filosofo vecino
    MPI_Recv(NULL, 0, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

    // Recibe la peticion del filosofo ...
    cout << "Ten. " << id << " recibe petic. de " << status.MPI_SOURCE << endl << flush;

    // Espera a que el filosofo suelte el tenedor...
    //Se usa MPI_SOURCE porque el MPI_Recv tiene que tener el mismo origen que el anterior
    MPI_Recv(NULL, 0, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD, &status);
    cout << "Ten. " << id << " recibe liberac. de " << status.MPI_SOURCE << endl << flush;
  }
}

// ---------------------------------------------------------------------

void camarero(){
  int cantidad_filosofos = 0;
  int rama;
  MPI_Status status;
  while(true){

    //Comprobamos si hay algun filosofo preguntando al camarero
    MPI_Probe( MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
    //En funcion de lo que quiera el filosofo, se sienta o se levanta
    //Si se quiere sentar y hay al menos 1 hueco, se sienta
    if((status.MPI_TAG == Filosofo_Sienta) && (cantidad_filosofos <= 3)){
      cout << "filosofo " << status.MPI_SOURCE << "quiere sentarse" << endl << flush;
      MPI_Recv(NULL, 0, MPI_INT, MPI_ANY_SOURCE, Filosofo_Sienta, MPI_COMM_WORLD, &status);
      cantidad_filosofos++;
    }
    //Si no quiere sentarse (se quiere levantar)
    else{
      cout << "filosofo " << status.MPI_SOURCE << "quiere levantarse" << endl << flush;
      MPI_Recv(NULL, 0, MPI_INT, MPI_ANY_SOURCE, Filosofo_Levanta, MPI_COMM_WORLD, &status);
      cantidad_filosofos--;
    }
  }
}
