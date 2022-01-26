// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: prodcons2.cpp
// Implementación del problema del productor-consumidor con
// un proceso intermedio que gestiona un buffer finito y recibe peticiones
// en orden arbitrario
// (versión con un varios productores y un varios consumidores)
// -----------------------------------------------------------------------------

/*
Partiendo del algoritmo desarrollado durante la Práctica 3 para resolver el problema de múltiples
Productores-Consumidores usando paso de mensajes MPI, se pide realizar los siguientes cambios.
*El valor que los procesos productores envían al buffer deberá ser un valor aleatorio entre 0 y 9 generado
mediante la función rand() en lugar de uno secuencial como hasta ahora. Así mismo,
*el productor deberá enviar un mensaje al buffer pidiendo permiso para enviar el valor, y el buffer deberá responder
al productor autorizando a enviar el mensaje antes de hacerlo (al igual que ya hace el consumidor).
*Realiza los cambios necesarios para que, en el caso de que en el buffer se almacenen dos valores
iguales consecutivos (independientemente del productor que los envíe), el buffer finalice. Antes de
finalizar deberá avisar a todos los productores y consumidores para que estos finalicen enviando un
valor especial en los mensajes de autorización. (Por ejemplo, un valor negativo). Sólo cuando todos
los procesos hayan finalizado el buffer terminará. Implementa esta condición de forma que cuando
cualquier proceso vaya a finalizar, imprima un mensaje en pantalla informando de ello.
*/


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
     id_buffer             = num_prods,
     num_procesos_esperado = num_prods + num_cons + 1,
     num_items             = 20,
     num_items_prod     = num_items/num_prods,
     num_items_cons     = num_items/num_cons,
     tam_vector            = 10;

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
   int res;
   sleep_for( milliseconds( aleatorio<10,100>()) );
   res = aleatorio<0,9>();
   cout << "Productor " << id_prod << " ha producido valor " << res << endl << flush;
   return res;
}
// ---------------------------------------------------------------------

void funcion_productor(int proc_prod)
{

  int         peticion = 1,
              valor_res_pet = 1 ;
  MPI_Status  estado ;

   for ( unsigned int i= 0 ; i < num_items_prod ; i++ )
   {
      // producir valor
      int valor_prod = producir(proc_prod);
      // enviar valor

      //enviar peticion antes de enviar valor
      MPI_Ssend( &peticion,  1, MPI_INT, id_buffer, 0, MPI_COMM_WORLD);//la etiq 0=prod manda mensaje
      cout << "Productor " << proc_prod << " envia peticion al buffer antes de insertar" << endl << flush;
      //recibir respuesta de peticion
      MPI_Recv ( &valor_res_pet, 1, MPI_INT, id_buffer, 0, MPI_COMM_WORLD, &estado );//prod recibe respuesta
      cout << "Productor " << proc_prod << " ha recibido respuesta del buffer " << valor_res_pet << endl << flush ;
        //si es <0 finalizo
        if(valor_res_pet<0){
          cout << " Productor no puede producir porque hay 2 valores consecutivos iguales en el buffer " << endl << flush;
          break;  //finalizo
        }
        //si es >0 envio valor
        else{
          cout << "Productor " << proc_prod << " va a enviar valor " << valor_prod << endl << flush;
          MPI_Ssend( &valor_prod, 1, MPI_INT, id_buffer, 0, MPI_COMM_WORLD );//la etiq 0= prod manda mensaje
        }
   }

   cout << "\tProceso Productor " << proc_prod << " termina." << endl;
}
// ---------------------------------------------------------------------

void consumir( int valor_cons, int id_cons )
{
   // espera bloqueada
   sleep_for( milliseconds( aleatorio<110,200>()) );
   cout << "Consumidor " << id_cons << " ha consumido valor " << valor_cons << endl << flush ;
}
// ---------------------------------------------------------------------

void funcion_consumidor(int proc_cons)
{
   int         peticion = 1,
               valor_rec = 1 ;
   MPI_Status  estado ;

   for( unsigned int i=0 ; i < num_items_cons; i++ )
   {
      MPI_Ssend( &peticion,  1, MPI_INT, id_buffer, 1, MPI_COMM_WORLD);//la etiq 1=cons manda mensaje
      cout << "Consumidor " << proc_cons << " pide valor al buffer(it=" << i << ")" << endl << flush;
      MPI_Recv ( &valor_rec, 1, MPI_INT, id_buffer, 1, MPI_COMM_WORLD, &estado );//cons recibe respuesta
      if(valor_rec<0){
        cout << " Consumidor no puede consumir porque hay 2 valores consecutivos iguales en el buffer " << endl << flush;
        break;  //finalizo
      }

      cout << "Consumidor "<< proc_cons << " ha recibido valor " << valor_rec << endl << flush ;
      consumir( valor_rec, proc_cons );
   }

   cout << "\tProceso Consumidor " << proc_cons << " termina." << endl << flush;
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
   MPI_Status estado,         //estado del mensaje recibido del prod o cons
              est ;            // estado del mensaje del proceso
/*

MPI_Status es un tipo estructura con los metadatos de los mensajes:
	- status.MPI_SOURCE: proceso fuente.
	- status.MPI_TAG: etiqueta del mensaje.
*/
   for( unsigned int i=0 ; i < num_items*2 ; i++ )
   {
      // 1. determinar si puede enviar solo prod., solo cons, o cualquiera

      if ( num_celdas_ocupadas == 0 ){// si buffer vacío
         MPI_Probe(MPI_ANY_SOURCE,0,MPI_COMM_WORLD, &est);//etiq 0 = mensaje de prod
         id_emisor_aceptable = est.MPI_SOURCE;     // $~~~$ solo prod.
         cout << "\t\tBuffer(vacio): Aceptado = Productor " << id_emisor_aceptable << " solo puede escribir" << endl;
      }
      else if( num_celdas_ocupadas == tam_vector ){ // si buffer lleno
          MPI_Probe(MPI_ANY_SOURCE,1,MPI_COMM_WORLD, &est);//etiq 1 = mensaje de cons
          id_emisor_aceptable = est.MPI_SOURCE;      // $~~~$ solo cons.
          cout << "Buffer(lleno): Aceptado = Consumidor " << id_emisor_aceptable << " solo puede leer" << endl;
      }
      else{                                   // si no vacío ni lleno
         MPI_Probe(MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD, &est);// $~~~$ cualquiera
         id_emisor_aceptable = est.MPI_SOURCE;
         cout << "\t\tBuffer(semiocupado[" << num_celdas_ocupadas << "]): Aceptado cualquier proceso(" << id_emisor_aceptable << ")" << endl;
      }


      // 2. recibir un mensaje del emisor o emisores aceptables (peticion)

      MPI_Recv( &valor, 1, MPI_INT, id_emisor_aceptable, MPI_ANY_TAG, MPI_COMM_WORLD, &estado );
      cout << "\t\tRecibido mensaje del proceso " << id_emisor_aceptable << endl;

      // 3. procesar el mensaje recibido
        //leemos el emisor del mensaje a traves del estado
      if(estado.MPI_SOURCE < num_prods){ // si ha sido el productor: RESPONDER PETICION, RECIBIR VALOR E insertar en buffer


        //dar permiso respondiendo a peticion
        MPI_Ssend(&valor,1,MPI_INT,id_emisor_aceptable,0,MPI_COMM_WORLD);
        //recibir valor
        MPI_Recv(&valor, 1, MPI_INT, id_emisor_aceptable, 0, MPI_COMM_WORLD, &estado);


        buffer[primera_libre] = valor ;
        primera_libre = (primera_libre+1) % tam_vector ;
        num_celdas_ocupadas++ ;
        cout << "\t\tBuffer ha recibido valor " << valor << endl ;

        //CODIGO PARA FINALIZAR SI EL VALOR INTRODUCIDO ES IGUAL AL ANTERIOR

        //si el valor introducido es igual al anterior, mandar respet a todos prod/cons y finalizar buffer
        int respet = -1;//valor de finalizacion
        if(buffer[num_celdas_ocupadas] == buffer[num_celdas_ocupadas-1]){
          for(unsigned int i=0 ; i < num_prods; i++){  //menos el buffer
            MPI_Ssend(&respet,1,MPI_INT,i,0,MPI_COMM_WORLD);
            break;
          }
          for(unsigned int i=num_prods+1 ; i <= num_prods+1+num_cons; i++){  //menos el buffer
            MPI_Ssend(&respet,1,MPI_INT,i,0,MPI_COMM_WORLD);
            break;
          }
          cout << "DOS VALORES CONSECUTIVOS IDENTICOS ---> FINALIZO" << endl << flush;
          break;
        }

      }
      else{ // si ha sido el consumidor: extraer y enviarle
/*
        //CODIGO PARA FINALIZAR SI EL VALOR INTRODUCIDO ES IGUAL AL ANTERIOR
          int respet = -1;//valor de finalizacion
        if(buffer[num_celdas_ocupadas] == buffer[num_celdas_ocupadas-1]){
          for(unsigned int i=0 ; i < num_prods; i++){  //menos el buffer
            MPI_Ssend(&respet,1,MPI_INT,i,0,MPI_COMM_WORLD);
            break;
          }
          for(unsigned int i=num_prods+1 ; i <= num_prods+1+num_cons; i++){  //menos el buffer
            MPI_Ssend(&respet,1,MPI_INT,i,0,MPI_COMM_WORLD);
            break;
          }
          cout << "DOS VALORES CONSECUTIVOS IDENTICOS ---> FINALIZO" << endl << flush;
          break;
        }
*/
            valor = buffer[primera_ocupada] ;
            primera_ocupada = (primera_ocupada+1) % tam_vector ;
            num_celdas_ocupadas-- ;
            cout << "\t\tBuffer va a enviar valor " << valor << endl ;
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
      if ( id_propio < num_prods ){
        cout << "Proceso Productor " << id_propio << " comienza." << endl;
         funcion_productor(id_propio);
      }
      else if ( id_propio == num_prods ){
        cout << "Proceso Buffer " << id_propio << " comienza." << endl;
         funcion_buffer();
      }
      else if((id_propio > num_prods)&&(id_propio<num_procesos_esperado)){
        cout << "Proceso Consumidor " << id_propio << " comienza." << endl;
         funcion_consumidor(id_propio-num_prods); //equilibramos la cuenta (en vez de  cons 6,7,8... seria cons 0,1,2...)
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
