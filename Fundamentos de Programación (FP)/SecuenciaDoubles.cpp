//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// Departamento de Ciencias de la Computación e Inteligencia Artificial
// Autor: Juan Carlos Cubero
//
//////////////////////////////////////////////////////////////////////////

// Secuencia de Doubles

#include <iostream>
using namespace std;

class SecuenciaDoubles{
private:
   static const int TAMANIO = 50;
   double vector_privado[TAMANIO];
   int total_utilizados;
   
   void IntercambiaComponentes_en_Posiciones(int pos_izda, int pos_dcha){
      double intercambia;

      intercambia = vector_privado[pos_izda];
      vector_privado[pos_izda] = vector_privado[pos_dcha];
      vector_privado[pos_dcha] = intercambia;
   }
public:
   SecuenciaDoubles()
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
   
   void Aniade(double nuevo){
      if (total_utilizados < TAMANIO){
         vector_privado[total_utilizados] = nuevo;
         total_utilizados++;
      }
   }
   
   void Modifica(int posicion, double nuevo){
      if (posicion >= 0 && posicion < total_utilizados)
         vector_privado[posicion] = nuevo;
   }

   double Elemento(int indice){
      return vector_privado[indice];
   }
   
   string ToString(){
      // Si el número de caracteres en memoria es muy grande,
      // es mucho más eficiente reservar memoria previamente
      // y usar push_back

      string cadena;

      cadena.reserve(total_utilizados);

      for (int i=0; i < total_utilizados; i++){
         cadena.append(to_string(vector_privado[i]));
         cadena.append(" ");
         //cadena = cadena + to_string(vector_privado[i])  <- Evitarlo. Muy ineficiente para tamaños grandes;
      }
      
      return cadena;
   }

   int PrimeraOcurrenciaEntre (int pos_izda, int pos_dcha, double buscado){
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
   
   int PrimeraOcurrencia (double buscado){
      return PrimeraOcurrenciaEntre (0, total_utilizados - 1, buscado);
   }
   

   /////////////////////////////////////////////////////////////
   // Búsquedas
   
   // Precond: 0 <= izda <= dcha < total_utilizados
   int PosicionMinimoEntre(int izda, int dcha){
      int posicion_minimo = -1;
      double minimo;

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
   
   int BusquedaBinaria (double buscado){
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
   void Inserta(int pos_insercion, double valor_nuevo){
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
      double a_desplazar;

      for (izda=1; izda < total_utilizados; izda++){
         a_desplazar = vector_privado[izda];

         for (i=izda; i > 0 && a_desplazar < vector_privado[i-1]; i--)
            vector_privado[i] = vector_privado[i-1];

         vector_privado[i] = a_desplazar;
      }
   }
   
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
   
   void AniadeVarios(SecuenciaDoubles nuevos){
      int totales_a_aniadir = nuevos.TotalUtilizados();
      
      for (int i = 0; i < totales_a_aniadir; i++)
         Aniade(nuevos.Elemento(i)); // Es importante entender
   }


   // Busca una sub-secuencia
   // Las posiciones deben estar en orden y consecutivas
   int PosicionContiene (SecuenciaDoubles a_buscar){
      int  inicio;
      int  ultima_componente;
      bool encontrado;
      int  posicion_contiene;
      bool va_coincidiendo;
      int  utilizados_a_buscar;

      /*
      Tenemos una secuencia "grande" de tamaño G y otra pequeña de tamaño P

      Recorrer la secuencia "grande" fijando una posición inicial inicio
      La última posición inicial a probar será G-P
         A partir de inicio recorrer en paralelo las
         dos secuencias "grande" y "pequeña"
         Si no coinciden todas las componentes, hay que
         empezar de nuevo a partir de inicio + 1.
      */

      utilizados_a_buscar = a_buscar.TotalUtilizados();

      if (utilizados_a_buscar > 0){
         ultima_componente = total_utilizados - utilizados_a_buscar;
         encontrado = false;

         for (inicio = 0; inicio <= ultima_componente && !encontrado; inicio++){
            va_coincidiendo = true;

            for (int i = 0; i < utilizados_a_buscar && va_coincidiendo; i++)
               va_coincidiendo = vector_privado[inicio + i] == a_buscar.Elemento(i);

            if (va_coincidiendo){
               posicion_contiene = inicio;
               encontrado = true;
            }
         }
      }
      else
         encontrado = false;

      if (encontrado)
         return posicion_contiene;
      else
         return -1;
   /*
   Batería de pruebas:
      Los dos vectores vacíos.
      Alguno de ellos vacío.
      Los dos vectores iguales.  atti / atti
      Que no se encuentre.   atti / tj
      Que se encuentre al principio.  atti / at
      Que se encuentre justo al final. atti / ti
      Que haya un emparejamiento parcial pero no total,
      aunque luego sí se encuentre.  atttij / ti
   */
   }
};



class LectorSecuenciaDoubles{
private:
   double terminador;
public:
   LectorSecuenciaDoubles(double real_terminador)
      :terminador(real_terminador)
   {
   }
   SecuenciaDoubles Lee(){
      SecuenciaDoubles a_leer;
      int total_introducidos;  // Esta variable es para contar los introducidos
                               // y que no nos pasemos de la capacidad de la secuencia.
      int capacidad_secuencia;
      double real;

      total_introducidos = 0;
      capacidad_secuencia = a_leer.Capacidad();
      cin >> real;

      while (real != terminador && total_introducidos < capacidad_secuencia){
         a_leer.Aniade(real);
         total_introducidos++;
         cin >> real;
      }

      return a_leer;
   }
};



int main(){
   const double TERMINADOR = -1.0;
   LectorSecuenciaDoubles lector_secuencias(TERMINADOR);
   SecuenciaDoubles secuencia;

   secuencia = lector_secuencias.Lee();
   
   secuencia.Ordena_por_Insercion();

   cout << "\n" << secuencia.ToString();
   
   // 7.1 2.2 4.3 9.4 -1.0
}
