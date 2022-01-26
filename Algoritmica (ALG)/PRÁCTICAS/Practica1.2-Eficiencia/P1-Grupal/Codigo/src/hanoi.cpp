/**
   @file Resolucion del problema de las Torres de Hanoi
*/

   
#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

/**
   @brief Resuelve el problema de las Torres de Hanoi
   @param M: numero de discos. M > 1.
   @param i: numero de columna en que est�n los discos.
             i es un valor de {1, 2, 3}. i != j.
   @param j: numero de columna a que se llevan los discos.
             j es un valor de {1, 2, 3}. j != i.

   Esta funcion imprime en la salida estandar la secuencia de 
   movimientos necesarios para desplazar los M discos de la
   columna i a la j, observando la restriccion de que ningun
   disco se puede situar sobre otro de tamanio menor. Utiliza
   una unica columna auxiliar.
*/
void hanoi (int M, int i, int j);

void hanoi (int M, int i, int j)
{
  if (M > 0)
  {
    hanoi(M-1, i, 6-i-j);
    hanoi (M-1, 6-i-j, j);
  }
}

int main(int argc, char * argv[])
{
  if (argc != 2){
    cout << "Indica el numero de discos" << endl;
    return 0;
  }
  int M = atoi(argv[1]);
  duration<double> suma = steady_clock::duration::zero();

  for(int p = 0 ; p < 10 ; p++) {
    high_resolution_clock::time_point tantes, tdespues;
    tantes = high_resolution_clock::now();
    hanoi(M, 1, 2);
    tdespues = high_resolution_clock::now();
    suma += duration_cast<duration<double>>(tdespues - tantes);
  }
  cout << M << " " << suma.count()/10 << endl;

  return 0;
}
