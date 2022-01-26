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

const int num_items = 60 ,   // número de items
	       tam_vec   = 10;   // tamaño del buffer

unsigned cont_prod[num_items] = {0}, // contadores de verificación: producidos
         cont_cons[num_items] = {0}; // contadores de verificación: consumidos
		
int utilizados = 0,	//contador de items producidos pero pendientes de leer
	buffer[tam_vec];


SEM::Semaphore produce = 1;
SEM::Semaphore consume = 0;
//Semaphore(&consume);
//Semaphore(&produce);

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
      // completar ........
	bool insertado = false;
	sem_wait(produce); //si se esta consumiendo, esperamos (inicializado a 1, decrementa y pasa) 
	while(utilizados < tam_vec && !insertado){	//mientras utilizados no supere el tamaño del buffer
		if(insertado==false){	//para poder salir del while, porque solo queremos insertar 1 por vez
			buffer[utilizados] = dato;	//insertamos el dato en la posicion del buffer
			utilizados++;			//aumentamos a la siguiente vacia para el siguiente dato
			insertado = true;		//salida permitida
			cout << "\n\tSe ha insertado un dato. 'Produce: " << dato << "'" << endl << flush;
		}
	}
	
	sem_signal(consume);	//se acepta consumir
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int dato ;
      // completar ......
	sem_wait(consume); 	//esperar a que el productor produzca para consumir

	utilizados--; //para consumir el ultimo dato insertado (tb para la primera iteracion)
	bool extraido = false;	//para controlar que no se lee algo inexistente
	while(utilizados>=0 && !extraido){	//si el buffer no está vacio, entra y extrae
		dato = buffer[utilizados];
        	consumir_dato( dato );
		extraido = true;		//si extrae, sale y continua
		cout << "\n\tSe ha extraido un dato. 'Consume: " << dato << "'"<< endl << flush;
	}
	sem_signal(produce);	//habilita al productor
    }
}
//----------------------------------------------------------------------

int main()
{
   cout << "--------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución LIFO)." << endl
        << "--------------------------------------------------------" << endl
        << flush ;
	
	//Semaphore produce = 1;
	//Semaphore consume = 0;

	//Semaphore(&consume);
	//Semaphore(&produce);
		
	
   thread hebra_productora ( funcion_hebra_productora ),
          hebra_consumidora( funcion_hebra_consumidora );

   hebra_productora.join() ;
   hebra_consumidora.join() ;

   test_contadores();
	cout << "\n\nTHE END" << endl;
	return 0;
}
