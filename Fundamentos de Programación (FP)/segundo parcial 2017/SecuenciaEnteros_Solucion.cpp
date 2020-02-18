//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// Departamento de Ciencias de la Computación e Inteligencia Artificial
// Autor: Juan Carlos Cubero
//
//////////////////////////////////////////////////////////////////////////

// Secuencia de enteros

#include <iostream>
using namespace std;

class SecuenciaEnteros{
private:
   static const int TAMANIO = 50;
   long vector_privado[TAMANIO];
   int total_utilizados;
   
   void IntercambiaComponentes_en_Posiciones(int pos_izda, int pos_dcha){
      long intercambia;

      intercambia = vector_privado[pos_izda];
      vector_privado[pos_izda] = vector_privado[pos_dcha];
      vector_privado[pos_dcha] = intercambia;
   }
   
public:
   SecuenciaEnteros()
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
   
   void Aniade(long nuevo){
      if (total_utilizados < TAMANIO){
         vector_privado[total_utilizados] = nuevo;
         total_utilizados++;
      }
   }
   
   void Modifica(int posicion, long nuevo){
      if (posicion >= 0 && posicion < total_utilizados)
         vector_privado[posicion] = nuevo;
   }

   long Elemento(int indice){
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

   
   void AniadeVarios(SecuenciaEnteros nuevos){
      int totales_a_aniadir = nuevos.TotalUtilizados();
      
      for (int i = 0; i < totales_a_aniadir; i++)
         Aniade(nuevos.Elemento(i)); 
   }
   
   SecuenciaEnteros Union(SecuenciaEnteros otra){
	   SecuenciaEnteros resultado;
	   resultado = otra;
	   for (int i = 0; i < TotalUtilizados(); i++){
		   int posicion = otra.BusquedaBinaria(Elemento(i));
		   if (posicion == -1){ //no existe
			   resultado.Aniade(Elemento(i));
		   }
	   }
	   return resultado;
   }
   
   SecuenciaEnteros Interseccion(SecuenciaEnteros otra){
	   SecuenciaEnteros resultado;
	   for (int i = 0; i < TotalUtilizados(); i++){
		   int posicion = otra.BusquedaBinaria(Elemento(i));
		   if (posicion != -1){ //ya existe
			   resultado.Aniade(Elemento(i));
		   }
	   }
	   return resultado;
   }
   
   SecuenciaEnteros Diferencia(SecuenciaEnteros otra){
	   SecuenciaEnteros resultado;
	   for (int i = 0; i < TotalUtilizados(); i++){
		   int posicion = otra.BusquedaBinaria(Elemento(i));
		   if (posicion == -1){
			   resultado.Aniade(Elemento(i));
		   }
	   }
	   return resultado;
   }
   
   SecuenciaEnteros DiferenciaSim(SecuenciaEnteros otra){
	   SecuenciaEnteros res_union, res_int, resultado;
	   res_union = Union(otra);
	   res_int = Interseccion(otra);
	   resultado = res_union.Diferencia(res_int);
	   return resultado;
   }
   
   /** 
    * Busqueda secuencial. Utilizar preferiblemente busqueda binaria o similar, etc.
    */
   bool BusquedaSecuencial(long valor){
	   bool encontrado = false;
	   for(int i = 0; i < TotalUtilizados() && !encontrado; i++){
			encontrado = Elemento(i) == valor;
		}
		return encontrado;
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
   
   /**
    * Necesita la secuencia ordenada
    */
   int BusquedaBinaria (long buscado){
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



class LectorSecuenciaEnteros{
private:
   long terminador;
public:
   LectorSecuenciaEnteros(long entero_terminador)
      :terminador(entero_terminador)
   {
   }
   SecuenciaEnteros Lee(){
      SecuenciaEnteros a_leer;
      int total_introducidos;  // Esta variable es para contar los introducidos
                               // y que no nos pasemos de la capacidad de la secuencia.
      int capacidad_secuencia;
      long entero;

      total_introducidos = 0;
      capacidad_secuencia = a_leer.Capacidad();
      cin >> entero;

      while (entero != terminador && total_introducidos < capacidad_secuencia){
         a_leer.Aniade(entero);
         total_introducidos++;
         cin >> entero;
      }

      return a_leer;
   }
};



int main(){
   const long TERMINADOR = -1;
   LectorSecuenciaEnteros lector_secuencias(TERMINADOR);
   SecuenciaEnteros secuenciaA, secuenciaB, secuenciaC;

	cout << "Introduce secuencia primera, -1 para terminar" << endl;
   secuenciaA = lector_secuencias.Lee();
   cout << "Introduce secuencia segunda, -1 para terminar" << endl;
	secuenciaB = lector_secuencias.Lee();
	secuenciaB.Ordena_por_BurbujaMejorado(); //Para la búsqueda de los elementos
	
	secuenciaC = secuenciaA.Union(secuenciaB);
	cout << "El resultado de la Union es: " << endl;
   cout << secuenciaC.ToString() << endl;
   
   	secuenciaC = secuenciaA.Interseccion(secuenciaB);
	cout << "El resultado de la Interseccion es: " << endl;
   cout << secuenciaC.ToString() << endl;
   
   secuenciaC = secuenciaA.Diferencia(secuenciaB);
	cout << "El resultado de la Diferencia es: " << endl;
   cout << secuenciaC.ToString() << endl;
   
   secuenciaC = secuenciaA.DiferenciaSim(secuenciaB);
	cout << "El resultado de la Diferencia Simetrica es: " << endl;
   cout << secuenciaC.ToString() << endl;
   
   cout << "Programa Finalizado!" << endl;

   
   // 7 2 4 9 -1
}

 
