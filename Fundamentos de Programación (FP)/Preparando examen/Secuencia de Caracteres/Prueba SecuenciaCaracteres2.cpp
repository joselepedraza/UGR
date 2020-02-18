#include <iostream>
using namespace std;

class SecuenciaCaracteres{
private:
   static const int TAMANIO = 50;
   char vector_privado[TAMANIO];
   int total_utilizados;

public:
   SecuenciaCaracteres()
      :total_utilizados(0) {
   }
   
   int TotalUtilizados(){
      return total_utilizados;
   }
   
   int Capacidad(){
      return TAMANIO;
   }
   
   void EliminaTodos(){
      total_utilizados = 0;
   }
   
   void Aniade(char nuevo){
      if (total_utilizados < TAMANIO){
         vector_privado[total_utilizados] = nuevo;
         total_utilizados++;
      }
   }
   
   void Modifica(int posicion, char nuevo){
      if (posicion >= 0 && posicion < total_utilizados)
         vector_privado[posicion] = nuevo;
   }

   char Elemento(int indice){
      return vector_privado[indice];
   }
   
   string ToString(){
      string cadena;
      
      for (int i=0; i < total_utilizados; i++)
         cadena = cadena + vector_privado[i];
      
      return cadena;
   }
   
   

   int PrimeraOcurrenciaEntre (int pos_izda, int pos_dcha, char buscado){
      int i = pos_izda;
      bool encontrado = false;

      while (i <= pos_dcha  &&  !encontrado)
         if (vector_privado[i] == buscado)
            encontrado = true;
         else
            i++;

      if (encontrado)
         return i;
      else
         return -1;
   }
   
   int PrimeraOcurrencia (char buscado){
      return PrimeraOcurrenciaEntre (0, total_utilizados - 1, buscado);
   }
   
//   int PosicionMinimo(){
//      int posicion_minimo;
//      char minimo;
//
//      minimo = vector_privado[0];
//      posicion_minimo = 0;
//
//      for (int i = 1; i < total_utilizados ; i++){
//         if (vector_privado[i] < minimo){
//            minimo = vector_privado[i];
//            posicion_minimo = i;
//         }
//      }
//
//      return posicion_minimo;
//   }


   /////////////////////////////////////////////////////////////
   // Búsquedas
   
   // Precond: 0 <= izda <= dcha < total_utilizados
   int PosicionMinimoEntre(int izda, int dcha){
      int posicion_minimo = -1;
      char minimo;

      minimo = vector_privado[izda];
      posicion_minimo = izda;

      for (int i = izda+1 ; i <= dcha ; i++)
         if (vector_privado[i] < minimo){
            minimo = vector_privado[i];
            posicion_minimo = i;
         }

      return posicion_minimo;
   }
   
   int PosicionMinimo(){
      return PosicionMinimoEntre(0, total_utilizados - 1);
   }
   
   int BusquedaBinaria (char buscado){
      int izda, dcha, centro;
      bool encontrado = false;

      izda = 0;
      dcha = total_utilizados - 1;
      centro = (izda + dcha) / 2;

      while (izda <= dcha  &&  !encontrado){
         if (vector_privado[centro] == buscado)
            encontrado = true;
         else if (buscado < vector_privado[centro])
            dcha = centro - 1;
         else
            izda = centro + 1;

         centro = (izda + dcha) / 2;
      }

      if (encontrado)
         return centro;
      else
         return -1;
   }
};

int main(){
   SecuenciaCaracteres secuencia;
   int utilizados_en_secuencia;

   secuencia.Aniade('H');
   secuencia.Aniade('o');
   secuencia.Aniade('l');
   secuencia.Aniade('a');
   
   /////////////////////////////////////////////////////////
   // Recorrido para imprimir los elementos de la secuencia:

   utilizados_en_secuencia = secuencia.TotalUtilizados();

   for (int i=0; i < utilizados_en_secuencia; i++)
     cout << secuencia.Elemento(i);

   // O bien:

   cout << "\n" << secuencia.ToString();


   /////////////////////////////////////////////////////////
   // Búsquedas
   /////////////////////////////////////////////////////////

   
   int pos_encontrado;
   char letra_a_buscar;
   
   
   /////////////////////////////////////////////////////////
   // Primera Ocurrencia 
 
   cout << "\nIntroduzca una letra a buscar en la cadena ";
   cin >> letra_a_buscar;

   pos_encontrado = secuencia.PrimeraOcurrencia(letra_a_buscar);

   // Si estuviese ordenado:
   // pos_encontrado = secuencia.BusquedaBinaria(letra_a_buscar);

   if (pos_encontrado == -1)
      cout << "\nLa letra " << letra_a_buscar << " no se encuentra";
   else
      cout << "\nLa letra " << letra_a_buscar 
           << " se encuentra en la posición " << pos_encontrado;

   /////////////////////////////////////////////////////////
   // Mínimo

   int pos_minimo;

   pos_minimo = secuencia.PosicionMinimo();
   cout << "\nEl mínimo de la cadena se encuentra en la posición "
        << pos_minimo;
}
