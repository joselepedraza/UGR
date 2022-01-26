/**
   @file Ordenacion por montones
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
/*  Metodo de ordenacion por montones  */

/**
   @brief Ordena un vector por el metodo de montones.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: numero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de ordenacion por montones.
*/
inline static void heapsort(int T[], int num_elem);



/**
   @brief Reajusta parte de un vector para que sea un monton.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: numero de elementos. num_elem > 0.
   @param k: Indice del elemento que se toma com raiz
   
   Reajusta los elementos entre las posiciones k y num_elem - 1 
   de T para que cumpla la propiedad de un monton (APO), 
   considerando al elemento en la posicion k como la raiz.
*/
static void reajustar(int T[], int num_elem, int k);


/**
   Implementacion de las funciones
**/

static void heapsort(int T[], int num_elem)
{
  int i;
  for (i = num_elem/2; i >= 0; i--)
    reajustar(T, num_elem, i);
  for (i = num_elem - 1; i >= 1; i--)
  {
    int aux = T[0];
    T[0] = T[i];
    T[i] = aux;
    reajustar(T, i, 0);
  }
}
  
static void reajustar(int T[], int num_elem, int k)
{
  int j;
  int v;
  v = T[k];
  bool esAPO = false;
  while ((k < num_elem/2) && !esAPO)
  {
    j = k + k + 1;
    if ((j < (num_elem - 1)) && (T[j] < T[j+1]))
      j++;
    if (v >= T[j])
      esAPO = true;
    T[k] = T[j];
    k = j;
  }
  T[k] = v;
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
  
  for (int i = 0; i < n; i++)
  {
    T[i] = random();
  };

  for(int p = 0 ; p < 10 ; p++) {
    high_resolution_clock::time_point tantes, tdespues;
    tantes = high_resolution_clock::now();
    heapsort(T, n);
    tdespues = high_resolution_clock::now();
    suma = duration_cast<duration<double>>(tdespues - tantes);
  }
  cout << n << " " << suma.count()/10 << endl;

  delete [] T;

  return 0;
};
