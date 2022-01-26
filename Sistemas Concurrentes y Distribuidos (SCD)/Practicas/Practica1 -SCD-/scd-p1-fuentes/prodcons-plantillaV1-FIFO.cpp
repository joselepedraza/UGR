#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "Semaphore.h"

using namespace std ;
using namespace SEM ;

//**********************************************************************
// variables compartidas

const int num_items = 1000 ,   // número de items
	       tam_vec   = 15 ;   // tamaño del buffer
unsigned  cont_prod[num_items] = {0}, // contadores de verificación: producidos
          cont_cons[num_items] = {0}; // contadores de verificación: consumidos
		

int buffer[tam_vec];	//items del buffer
int c_prod = 0,	//contador de items producidos para saber el que se va a producir 
	c_cons = 0;	//contador de items consumidos para saber el que se va a consumir

SEM::Semaphore produce = tam_vec;	//lo inicializamos a 1 para poder producir el primero
SEM::Semaphore consume = 0;	//"	"	a 0 para que no vaya a leer primero (no habria nada que leer)
SEM::Semaphore sec_crit = 1;	//para asegurar que no accede a var compartidas (ni prod ni cons) simultaneamente

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
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

int producir_dato()
{
   static int contador = 0 ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "producido: " << contador << endl << flush ;

   cont_prod[contador] ++ ;
   return contador++ ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned dato )
{
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "                  consumido: " << dato << endl ;
   
}


//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

//----------------------------------------------------------------------

void  funcion_hebra_productora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int dato = producir_dato() ;
      // completar .....
	sem_wait(produce);	//si se esta consumiendo, esperamos (inicializado a 1, decrementa y pasa)
		sem_wait(sec_crit);	
		buffer[c_prod]=dato;	//al añadir el dato en el buffer, incrementamos contador para la siguiente introducción si es posible
		c_prod++;
		//cout << "\n\tSe ha insertado un dato. 'Produce: " << dato << "'" << endl << flush;
		
		cout << "'Insertado = " << dato << " ' " << endl;
		if(c_prod >= tam_vec){	//si llegamos al final volvemos al principio (donde ya se ha consumido en teoria)
			c_prod = 0;
		}

		sem_signal(sec_crit);
	sem_signal(consume);	//se acepta consumir una vez se haya producido y accedido al buffer
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int dato ;
      // completar ......
	sem_wait(consume);	//esperar a que el productor produzca para consumir 
		sem_wait(sec_crit);	//aseguramos que se haya producido antes de consumir, por lo
		
		dato = buffer[c_cons];
		c_cons++;	//para poder consumir el siguiente
		//cout << "\n\tSe ha extraido un dato. 'Consume: " << dato << "'"<< endl << flush;
		cout << "\t\t'Extraido = " << dato << " ' " << endl;
		if(c_cons >= tam_vec){	//si se consumiera el ultimo, volveriamos al principio(donde ya se ha producido en teoria)	
			c_cons = 0;
		}
		sem_signal(sec_crit);
	sem_signal(produce);	//el productor puede producir
	consumir_dato(dato);
    }
}
//----------------------------------------------------------------------

int main()
{
   cout << "--------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución FIFO)." << endl
        << "--------------------------------------------------------" << endl
        << flush ;

   thread hebra_productora ( funcion_hebra_productora ),
          hebra_consumidora( funcion_hebra_consumidora );

   hebra_productora.join() ;
   hebra_consumidora.join() ;

   test_contadores();
	cout << "\n\nTHE END FIFO" << endl;
	return 0;
}
