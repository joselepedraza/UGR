/**
   @file Ordenacion por seleccion
*/
   
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>

using namespace std;
using namespace std::chrono;

/* ************************************************************ */ 
/*  Metodo de ordenacion por seleccion  */

/**
   @brief Ordena un vector por el metodo de seleccion.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: numero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de seleccion.
*/
inline static void seleccion(int T[], int num_elem);

/**
   @brief Ordena parte de un vector por el metodo de seleccion.

   @param T: vector de elementos. Tiene un numero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posicion que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posicion detras de la ultima de la parte del
                   vector a ordenar. 
		            inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de seleccion.
*/
static void seleccion_lims(int T[], int inicial, int final);



/**
   Implementacion de las funciones
**/

void seleccion(int T[], int num_elem)
{
  seleccion_lims(T, 0, num_elem);
}

static void seleccion_lims(int T[], int inicial, int final)
{
  int i, j, indice_menor;
  int menor, aux;
  for (i = inicial; i < final - 1; i++) {
    indice_menor = i;
    menor = T[i];
    for (j = i; j < final; j++)
      if (T[j] < menor) {
        indice_menor = j;
        menor = T[j];
      }
    aux = T[i];
    T[i] = T[indice_menor];
    T[indice_menor] = aux;
  };
}


int main(int argc, char * argv[])
{

  if (argc != 2){
    cout << "Indica el tamaño del vector" << endl;
    return 0;
  }

  int n = atoi(argv[1]);
  int * T = new int[n];
  assert(T);
  srandom(time(0));
  duration<double> suma = steady_clock::duration::zero();

  for(int p = 0 ; p < 10 ; p++) { 
    for (int i = 0; i < n; i++) T[i] = random();

    const int TAM_GRANDE = 2000;
    const int NUM_VECES = 100;
    high_resolution_clock::time_point tantes, tdespues, tantes_vacio, tdespues_vacio;

    if (n > TAM_GRANDE)
    {
      tantes = high_resolution_clock::now();
      seleccion(T, n);
      tdespues = high_resolution_clock::now();
      suma += duration_cast<duration<double>>(tdespues - tantes);
    } else {
      int * U = new int[n];
      assert(U);

      for (int i = 0; i < n; i++)
        U[i] = T[i];

      tantes_vacio = high_resolution_clock::now();
      for (int veces = 0; veces < NUM_VECES; veces++)
      {
        for (int i = 0; i < n; i++)
          U[i] = T[i];
      }
      tdespues_vacio = high_resolution_clock::now();

      tantes = high_resolution_clock::now();
      for (int veces = 0; veces < NUM_VECES; veces++)
      {
        for (int i = 0; i < n; i++)
          U[i] = T[i];
        seleccion(U, n);
      }
      tdespues = high_resolution_clock::now();
      suma += (duration_cast<duration<double>>((tdespues - tantes) - (tdespues_vacio - tantes_vacio))/NUM_VECES);
      
      delete [] U;
    }

  }

  cout << n << " " << suma.count()/10 << endl;

  delete [] T;
  return 0;
};