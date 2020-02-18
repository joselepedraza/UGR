/*Clase Secuenciadecaracteres con diversos metodos que trabajan con un dato del tipo SecuenciaCaracteres: */

#include<iostream>
#include<string>
using namespace std;

class SecuenciaCaracteres{
	private:
		static const int TAMANIO = 200;
		char VP[TAMANIO];
		int total_utilizados;
		
		//Metodo para desplazar una vez a la derecha los valores de la secuencia de caracteres:
		void Rotar1vez (){
			char aux = VP[total_utilizados-1];
			for(int i = total_utilizados-1; i > 1; i--){
				VP[i] = VP[i-1];
			}
			VP[0] = aux;			
		}
		
		//Metodo para saber si aparece otro elemento en la secuencia de caracteres inicial:
		bool Aparece (SecuenciaCaracteres otro, int pos){				
			int N = otro.TotalUtilizados();
			bool rta = true;
		 	for (int i = 0; i < N; i++){							//debe utilizarse while
		 		if (otro.Elemento(i) != VP[pos+i]){
					rta = false;
				}
		 	}
		 	return rta;
		}
		
		//Metodo para intercambiar dos posiciones (requerido por los algoritmos de ordenacion):
		void IntercambiaComponentes_en_Posiciones(int pos_izda, int pos_dcha){
      		char intercambia;

      		intercambia = VP[pos_izda];
      		VP[pos_izda] = VP[pos_dcha];
      		VP[pos_dcha] = intercambia;
   		}
		
	public:
		
		SecuenciaCaracteres()
			:total_utilizados(0){
		}
		
		int TotalUtilizados(){
			return total_utilizados;
		}
		
		int Capacidad(){
			return TAMANIO;
		}
		
		void Aniade(char nuevo){
			if (total_utilizados < TAMANIO){
				VP[total_utilizados] = nuevo;
				total_utilizados++;
			}
		}
		
		char Elemento(int indice){
			return VP[indice];
		}
		

		
		string ToString(){
			string cadena;
			for (int i=0; i<total_utilizados; i++){
				cadena = cadena + VP[i];
			}
			return cadena;
		}
		
		//Metodo para desplazar k posiciones el vector a la derecha (y la ultima pasa a ser la primera en cada iteracion): (requiere del metodo privado Rotar1vez)
		void Rotar (int k){
			for(int i=1; i<=k; i++){
		 		Rotar1vez();
		 	}
		}
		 
		 
////////////////BÚSQUEDAS/////////////////
		 
		 
		//Metodo para saber si existe (está incluida) otra secuencia de caracteres en la secuencia de caracteres inicial: (requiere del metodo privado Aparece)
		int Existe (SecuenciaCaracteres otro){
		 	int rta = -1;											//para devolver -1 si no existe
		 	int k = (total_utilizados - 1) - otro.TotalUtilizados();
		 	
		 	for (int i = 0; i < k; i++){
		 		if (Aparece(otro, i)){
		 			rta = i;										//enseña la posicion si existe
		 		}
		 	}
		 	return rta;
		}
		 
		//Metodo para saber la posicion con valor minimo (letra minima) entre dos valores pasados como argumentos:
		int PosicionMinimoEntre(int izda, int dcha){
    	int posicion_minimo = -1;
      	char minimo;

      	minimo = VP[dcha + 1];
      	posicion_minimo = dcha + 1;

      	for (int i = izda+1 ; i <= dcha ; i++)
        	 if (VP[i] < minimo){
        	    minimo = VP[i];
        	    posicion_minimo = i;
        	 }
		
    	  	return posicion_minimo;
   		}
   		
   		//Metodo para saber la posicion con el valor minimo de toda la secuencia de caracteres: (el utilizado requiere del metodo PosicionMinimoEntre)
   		
//	    int PosicionMinimo(){
//      int posicion_minimo;
//      char minimo;
//
//      minimo = VP[0];						//cogemos la posicion 0 como valor de referencia (minimo), y recorremos la secuencia de caracteres
//      posicion_minimo = 0;							//realizando la comprobacion con de todas las posiciones de la secuencia de caracteres y actualizando el valor del minimo.
//
//      for (int i = 1; i < total_utilizados ; i++){
//         if (VP[i] < minimo){
//            minimo = VP[i];
//            posicion_minimo = i;						//guardamos el minimo y la posicion donde se encuentra.
//         }
//      }
//
//      return posicion_minimo;
//   }

   		int PosicionMinimo(){
			return PosicionMinimoEntre(0, total_utilizados - 1);
   		}
   		
		//Metodo que busca si aparece un char entre dos posiciones de la secuencia de caracteres:
   	   	int PrimeraOcurrenciaEntre (int pos_izda, int pos_dcha, char buscado){
			int i = pos_izda;
      		bool encontrado = false;

      		while (i <= pos_dcha  &&  !encontrado)
     		    if (VP[i] == buscado)
            		encontrado = true;
         		else
            		i++;

      		if (encontrado)
         		return i;
      		else
         		return -1;
   		}
   		//Metodo que busca un char en toda la cadena de caracteres: (requiere del metodo PrimeraOcurrenciaEntre)
   		int PrimeraOcurrencia (char buscado){
  			return PrimeraOcurrenciaEntre (0, total_utilizados - 1, buscado);
   		}
   		
   		//Metodo que busca un char en toda la cadena de caracteres, siempre acotando su centro:
   		int BusquedaBinaria (char buscado){
      		int izda, dcha, centro;
      		bool encontrado = false;

      		izda = 0;
      		dcha = total_utilizados - 1;
      		centro = (izda + dcha) / 2;

      		while (izda <= dcha  &&  !encontrado){
         		if (VP[centro] == buscado)
            		encontrado = true;
         		else if (buscado < VP[centro])
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
   
   
/////////////////////RECORRIDOS QUE MODIFICAN LAS COMPONENTES////////////////////

		
		// Inserta un valor en la posición especificada
		void Inserta(int pos_insercion, char valor_nuevo){
			if (total_utilizados < TAMANIO  &&  pos_insercion >= 0  &&  pos_insercion <= total_utilizados){

  	        for (int i = total_utilizados ; i > pos_insercion ; i--)
            VP[i] = VP[i-1];

         	VP[pos_insercion] = valor_nuevo;
         	total_utilizados++;
      		}
   		}
   
   		// Elimina una componente, dada por su posición
		void Elimina (int posicion){
			if (posicion >= 0 && posicion < total_utilizados){
				int tope = total_utilizados-1;
				
				for (int i = posicion ; i < tope ; i++){
					VP[i] = VP[i+1];
				}
				total_utilizados--;
			}
		}
		
		//Elimina todas las componentes:
		void EliminaTodos(){
    		total_utilizados = 0;
   		}
   		
///////////////////////////ALGORITMOS DE ORDENACION///////////////////////////////
		
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
     		    a_desplazar = VP[izda];

         		for (i=izda; i > 0 && a_desplazar < VP[i-1]; i--)
            		VP[i] = VP[i-1];

         		VP[i] = a_desplazar;
      			}
   		}
   		
		void Ordena_por_BurbujaMejorado(){
      		int izda, i;
      		bool cambio;

      		cambio= true;

      		for (izda=0; izda < total_utilizados && cambio; izda++){
			 	cambio=false;

        	for (i=total_utilizados-1 ; i>izda ; i--)
        		  if (VP[i] < VP[i-1]){
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
   secuencia.Aniade('g');
   
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
           << " se encuentra en la posición " << pos_encontrado + 1;

   /////////////////////////////////////////////////////////
   // Mínimo

   int pos_minimo;

   pos_minimo = secuencia.PosicionMinimo();
   cout << "\nEl mínimo de la cadena se encuentra en la posición "
        << pos_minimo;
      
   

   /////////////////////////////////////////////////////////
   // Recorridos que modifican las componentes
   /////////////////////////////////////////////////////////
   
    /////////////////////////////////////////////////////////
   // Eliminar
   
   
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
   
   
   /////////////////////////////////////////////////////////
   // Algoritmos de ordenación
   /////////////////////////////////////////////////////////
   
  // secuencia.Ordena_por_Insercion();

   cout << "\n" << secuencia.ToString();
}

