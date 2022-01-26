/*
Se desea modificar el algoritmo dado del problema de los filósofos con camarero para dar
servicio a 7 filósofos y 7 tenedores en lugar de a 5. También se desea cambiar el identificador de los procesos para que los filósofos sean los procesos con rank 0, 1, 2, …, 6 y los tenedores sean los procesos 7, 8, …, 13. Describe brevemente qué cambios debes realizar en el código proporcionado y en qué líneas.
*/



#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int ETIQ_SOLTAR_TEN = 0;
const int ETIQ_COGE_TEN = 1;
const int ETIQ_SENTARSE = 2;
const int ETIQ_LEVANTARSE = 3;
const int ETIQ_CAMARERO = 14;

const int
   num_filosofos = 7 ,
   num_procesos  = (2*num_filosofos) +1 ; //+ el camarero


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
void funcion_camarero(){
  int valor,
      fsentad2=0;
  MPI_Status estado;

  while(true){

    //camarero espera a que le pidan permiso
    if(fsentad2<5)//max filo sentados
      MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);//puede sentarse/levantarse
    else
      MPI_Probe(MPI_ANY_SOURCE, ETIQ_LEVANTARSE, MPI_COMM_WORLD, &estado);//solo levantarse

    if(estado.MPI_TAG == ETIQ_SENTARSE){  //le sentamos
      valor=estado.MPI_SOURCE;  //identificamos al filosofo para sentarlo
      MPI_Recv(NULL, 0, MPI_INT, valor, ETIQ_SENTARSE, MPI_COMM_WORLD, &estado);
      fsentad2++;
      MPI_Ssend(NULL, 0, MPI_INT, valor, ETIQ_SENTARSE, MPI_COMM_WORLD);
      cout << "\t**El filosofo " <<  valor  << " se Sienta. Fsentados = " << fsentad2 << endl;
    }
    //else{ //le levantamos
    if(estado.MPI_TAG == ETIQ_LEVANTARSE){
      valor=estado.MPI_SOURCE;
      MPI_Recv(NULL, 0, MPI_INT, valor, ETIQ_LEVANTARSE, MPI_COMM_WORLD, &estado);
      fsentad2--;
      cout << "\t**El filosofo " << valor << " se Levanta. Fsentados = " << fsentad2 << endl;
    }
  }
}
//....................................................................................................

void funcion_filosofos( int id )
{

//  int id_ten_izq = (id+1) % (num_procesos-1), //id. tenedor izq.
//      id_ten_der = ((id+num_procesos)-2) % (num_procesos-1); //id. tenedor der.
  int id_ten_izq = (id+num_procesos-1)-num_filosofos % (num_procesos-1); //id. tenedor izq.
  int id_ten_der;
      if(id == 0)
        id_ten_der = num_procesos-2;
      else
        id_ten_der = ((id+num_filosofos-1)+num_procesos-1)%(num_procesos-1); //id. tenedor der.
  int peticion;//con el camarero simplemente null  y fuera
  MPI_Status estado;
  while ( true )
  {
    //filosofo pide permiso al camarero para sentarse
    cout << "Filosofo " << id << " pide permiso para sentarse" << endl;
    MPI_Ssend(NULL,0,MPI_INT, ETIQ_CAMARERO, ETIQ_SENTARSE, MPI_COMM_WORLD);
    //espera a que el camarero le diga que puede sentarse
    MPI_Recv(NULL,0,MPI_INT, ETIQ_CAMARERO, ETIQ_SENTARSE, MPI_COMM_WORLD, &estado);
    cout << "Filosofo " << id << " se sienta." << endl;

    // ... solicitar tenedor izquierdo (completar)
    cout <<"Filósofo " <<id << " solicita ten. izq." <<id_ten_izq <<endl;
    MPI_Ssend(&peticion, 0, MPI_INT, id_ten_izq, ETIQ_COGE_TEN, MPI_COMM_WORLD );

    // ... solicitar tenedor derecho (completar)
    cout <<"Filósofo " <<id <<" solicita ten. der." <<id_ten_der <<endl;
    MPI_Ssend(&peticion, 0, MPI_INT, id_ten_der, ETIQ_COGE_TEN, MPI_COMM_WORLD );

    cout <<"FILOSOFO " <<id <<" COME" <<endl ;
    sleep_for( milliseconds( aleatorio<10,100>() ) );

    cout <<"Filósofo " <<id <<" suelta ten. izq. " <<id_ten_izq <<endl;
    // ... soltar el tenedor izquierdo (completar)
    MPI_Ssend(&peticion, 0, MPI_INT, id_ten_izq, ETIQ_SOLTAR_TEN, MPI_COMM_WORLD);

    cout<< "Filósofo " <<id <<" suelta ten. der. " <<id_ten_der <<endl;
    // ... soltar el tenedor derecho (completar)
    MPI_Ssend(&peticion, 0, MPI_INT, id_ten_der, ETIQ_SOLTAR_TEN, MPI_COMM_WORLD);

    //El filosofo pide permiso al camarero para levantarse (siempre se lo da)
    cout << "Filosofo pide permiso para levantarse al camarero y se levanta." << endl;
    MPI_Ssend(NULL, 0, MPI_INT, ETIQ_CAMARERO, ETIQ_LEVANTARSE, MPI_COMM_WORLD);

    cout << "FILOSOFO " << id << " PIENSA" << endl;
    sleep_for( milliseconds( aleatorio<10,100>() ) );
 }
}
// ---------------------------------------------------------------------

void funcion_tenedores( int id )
{
  int valor, id_filosofo;  // valor recibido(no se usa), identificador del filósofo
  MPI_Status estado ;       // metadatos de las dos recepciones

  while ( true )
  {
     // ...... recibir petición de cualquier filósofo vecino (completar)
     MPI_Recv(&valor,1,MPI_INT, MPI_ANY_SOURCE, ETIQ_COGE_TEN, MPI_COMM_WORLD, &estado);
     // ...... guardar en 'id_filosofo' el id. del emisor (completar)
     id_filosofo = estado.MPI_SOURCE;
     cout <<"Ten. " <<id << " cogido por filo. " << id_filosofo <<endl;

     // ...... recibir liberación de filósofo 'id_filosofo' (completar)
     MPI_Recv(&id_filosofo,1,MPI_INT, id_filosofo, ETIQ_SOLTAR_TEN, MPI_COMM_WORLD, &estado);
     cout <<"Ten. "<< id<< " liberado por filo. " << id_filosofo <<endl ;
  }
}
// ---------------------------------------------------------------------

int main( int argc, char** argv )
{
   int id_propio, num_procesos_actual ;

  // cout << "\tCENA DE LOS FILOSOFOS CON CAMARERO\n" << endl;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );

   if ( num_procesos == num_procesos_actual )
   {
      // ejecutar la función correspondiente a 'id_propio'
      if (id_propio == 14)
          funcion_camarero();
      else if ( id_propio<6 )          // si esta entre 0 y 6 (hay 7 filosofos)
         funcion_filosofos( id_propio ); //   es un filósofo
      else                               // si esta entre 7 y 13 (hay 7 tenedores)
         funcion_tenedores( id_propio ); //   es un tenedor
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_procesos << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   MPI_Finalize( );
   return 0;
}

// ---------------------------------------------------------------------
