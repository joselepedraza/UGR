/**
   @file C�lculo del coste de los caminos m�nimos. Algoritmo de Floyd.
*/

   
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

static int const MAX_LONG  = 10;
            
/**********************************************************************/

/**
   @brief Reserva espacio en memoria dinamica para una matriz cuadrada.
   
   @param dim: dimension de la matriz. dim > 0.

   @returns puntero a la zona de memoria reservada.
*/
int ** ReservaMatriz(int dim);


/**********************************************************************/

/**
   @brief Libera el espacio asignado a una matriz cuadrada.
   
   @param M: puntero a la zona de memoria reservada. Es MODIFICADO.
   @param dim: dimension de la matriz. dim > 0.

   Liberar la zona memoria asignada a M y lo pone a NULL.
*/
void LiberaMatriz(int ** & M, int dim);

/**********************************************************************/

/**
   @brief Rellena una matriz cuadrada con valores aleaotorias.
   
   @param M: puntero a la zona de memoria reservada. Es MODIFICADO.
   @param dim: dimensi�n de la matriz. dim > 0.

   Asigna un valor aleatorio entero de [0, MAX_LONG - 1] a cada
   elemento de la matriz M, salvo los de la diagonal principal
   que quedan a 0..
*/
void RellenaMatriz(int **M, int dim);

/**********************************************************************/	
/**
   @brief Calculo de caminos minimos.
   
   @param M: Matriz de longitudes de los caminos. Es MODIFICADO.
   @param dim: dimension de la matriz. dim > 0.

   Calcula la longitud del camino minimo entre cada par de nodos (i,j),
   que se almacena en M[i][j].
*/
void Floyd(int **M, int dim);

/**********************************************************************/


/**
   Implementacion de las funciones
**/


int ** ReservaMatriz(int dim)
{
  int **M;
  if (dim  <= 0)
    {
      cerr<< "\n ERROR: Dimension de la matriz debe ser mayor que 0" << endl;
      exit(1);
    }
  M = new int * [dim];
  if (M == NULL)
    {
      cerr << "\n ERROR: No puedo reservar memoria para un matriz de "
	   << dim << " x " << dim << "elementos" << endl;
      exit(1);
    }
  for (int i = 0; i < dim; i++)
    {
      M[i]= new int [dim];
      if (M[i] == NULL)
	{
	  cerr << "ERROR: No puedo reservar memoria para un matriz de "
	       << dim << " x " << dim << endl;
	  for (int j = 0; j < i; j++)
	    delete [] M[i];
	  delete [] M;
	  exit(1);
	} 
    }
  return M;
}	


/**********************************************************************/

void LiberaMatriz(int ** & M, int dim)
{
  for (int i = 0; i < dim; i++)
    delete [] M[i];
  delete [] M;
  M = NULL;
}		


/**********************************************************************/
void RellenaMatriz(int **M, int dim)
{
  for (int i = 0; i < dim; i++)
    for (int j = 0; j < dim; j++)
      if (i != j)
	M[i][j]= (rand() % MAX_LONG);
}			


/**********************************************************************/	
void Floyd(int **M, int dim)
{
  for (int k = 0; k < dim; k++)
    for (int i = 0; i < dim;i++)
      for (int j = 0; j < dim;j++)
      {
        int sum = M[i][k] + M[k][j];    	
        M[i][j] = (M[i][j] > sum) ? sum : M[i][j];
      }
}	     	


/**********************************************************************/	
int main (int argc, char **argv)
{

  //Lectura de los parametros de entrada
  if (argc != 2){
    cout << "Indica el tamaño del vector" << endl;
    return 0;
  }

  int dim = atoi(argv[1]);	
  int ** M = ReservaMatriz(dim);

  RellenaMatriz(M,dim);

  duration<double> suma = steady_clock::duration::zero();
  
  for(int p = 0 ; p < 10 ; p++) {
    high_resolution_clock::time_point tantes, tdespues;
    tantes = high_resolution_clock::now();
    Floyd(M,dim);
    tdespues = high_resolution_clock::now();
    suma += duration_cast<duration<double>>(tdespues - tantes);
  }
  
  cout << dim << " " << suma.count()/10 << endl;
  LiberaMatriz(M,dim);

  return 0;
}	
	
