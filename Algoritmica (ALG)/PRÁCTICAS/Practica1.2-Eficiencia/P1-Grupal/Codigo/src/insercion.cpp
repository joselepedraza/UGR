/**
   @file Ordenacion por insercion
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
/*  Metodo de ordenacion por insercion  */

/**
   @brief Ordena un vector por el metodo de insercion.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: numero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de insercion.
*/
inline static void insercion(int T[], int num_elem);

/**
   @brief Ordena parte de un vector por el metodo de insercion.

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
   Aplica el algoritmo de insercion.
*/
static void insercion_lims(int T[], int inicial, int final);

/**
   Implementacion de las funciones
**/

inline static void insercion(int T[], int num_elem)
{
  insercion_lims(T, 0, num_elem);
}


static void insercion_lims(int T[], int inicial, int final)
{
  int i, j;
  int aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((T[j] < T[j-1]) && (j > 0)) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
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
    high_resolution_clock::time_point tantes, tdespues;
    tantes = high_resolution_clock::now();
    insercion(T, n);
    tdespues = high_resolution_clock::now();
    suma += duration_cast<duration<double>>(tdespues - tantes);
  }

  cout << n << " " << suma.count()/10 << endl;
  delete [] T;
  return 0;
};
