#include <iostream>
using namespace std;

class SecuenciaCaracteres{
private:
   static const int TAMANIO = 50;
   char vector_privado[TAMANIO];
   int total_utilizados;
   
   void IntercambiaComponentes_en_Posiciones(int pos_izda, int pos_dcha){
      char intercambia;

      intercambia = vector_privado[pos_izda];
      vector_privado[pos_izda] = vector_privado[pos_dcha];
      vector_privado[pos_dcha] = intercambia;
   }
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
   
   
   /////////////////////////////////////////////////////////////
   // Recorridos que modifican las componentes
   
   // Inserta un valor en la posición especificada
   void Inserta(int pos_insercion, char valor_nuevo){
      if (total_utilizados < TAMANIO  &&  pos_insercion >= 0    
         &&  pos_insercion <= total_utilizados){

         for (int i = total_utilizados ; i > pos_insercion ; i--)
            vector_privado[i] = vector_privado[i-1];

         vector_privado[pos_insercion] = valor_nuevo;
         total_utilizados++;
      }
   }
   
   // Elimina una componente, dada por su posición
   void Elimina (int posicion){
      if (posicion >= 0 && posicion < total_utilizados){
         int tope = total_utilizados-1;

         for (int i = posicion ; i < tope ; i++)
            vector_privado[i] = vector_privado[i+1];

         total_utilizados--;
      }
   }
   
   
   /////////////////////////////////////////////////////////////
   // Algoritmos de ordenación
   
   void Ordena_por_Seleccion(){
      int pos_min;

      for (int izda = 0 ; izda < total_utilizados ; izda++){
         pos_min = PosicionMinimoEntre(izda, total_utilizados - 1);
         IntercambiaComponentes_en_Posiciones(izda, pos_min);
      }
   }
   
   void Ordena_por_Insercion(){
      int izda, i;
      char a_desplazar;

      for (izda=1; izda < total_utilizados; izda++){
         a_desplazar = vector_privado[izda];

         for (i=izda; i > 0 && a_desplazar < vector_privado[i-1]; i--)
            vector_privado[i] = vector_privado[i-1];

         vector_privado[i] = a_desplazar;
      }
   }
   
   /* 
   void InsertaOrdenadamente(char valor_nuevo){
        int i;

        if (total_utilizados > DIM){
           for (i=total_utilizados; i>0 && valor_nuevo < vector_privado[i-1]; i--)
                vector_privado[i] = vector_privado[i-1];

           vector_privado[i] = valor_nuevo;
           total_utilizados++;
        }
   }
   
   void Ordena_por_Insercion (){
      for (int izda=1; izda < total_utilizados; izda++)
         InsertaOrdenadamente(vector_privado[izda]);         
   }
   */
   
   void Ordena_por_Burbuja(){
      int izda, i;

      for (izda = 0; izda < total_utilizados; izda++)
        for (i = total_utilizados-1 ; i > izda ; i--)
          if (vector_privado[i] < vector_privado[i-1])
             IntercambiaComponentes_en_Posiciones(i, i-1);
   }
   
   void Ordena_por_BurbujaMejorado(){
      int izda, i;
      bool cambio;

      cambio= true;

      for (izda=0; izda < total_utilizados && cambio; izda++){
        cambio=false;

        for (i=total_utilizados-1 ; i>izda ; i--)
          if (vector_privado[i] < vector_privado[i-1]){
             IntercambiaComponentes_en_Posiciones(i, i-1);
             cambio=true;
          }
      }
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
   
   /*
   
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
      
   */

   /////////////////////////////////////////////////////////
   // Recorridos que modifican las componentes
   /////////////////////////////////////////////////////////
   
    /////////////////////////////////////////////////////////
   // Eliminar
   
   /*
   int pos_a_eliminar;
   
   cout << "\nIntroduzca posición a eliminar ";
   cin >> pos_a_eliminar;
   
   secuencia.Elimina(pos_a_eliminar);
   

    /////////////////////////////////////////////////////////
   // Insertar 
      
   int pos_a_inserter;
   char caracter_a_insertar;
   
   cout << "\nIntroduzca posición a insertar ";
   cin >> pos_a_inserter;
   cout << "\nIntroduzca carácter a insertar ";
   cin >> caracter_a_insertar;   
   
   secuencia.Inserta(pos_a_inserter, caracter_a_insertar) ;
   */
   
   /////////////////////////////////////////////////////////
   // Algoritmos de ordenación
   /////////////////////////////////////////////////////////
   
   secuencia.Ordena_por_Insercion();

   cout << "\n" << secuencia.ToString();
}

