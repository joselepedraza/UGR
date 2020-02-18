#include <iostream>
using namespace std;

class SecuenciaCaracteres{
private:
   static const int TAMANIO = 50;
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
		
/*		//Metodo para saber si aparece otro elemento en la secuencia de caracteres inicial:
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
*/		
		//Metodo para intercambiar dos posiciones (requerido por los algoritmos de ordenacion):
		void IntercambiaComponentes_en_Posiciones(int pos_izda, int pos_dcha){
      		char intercambia;

      		intercambia = VP[pos_izda];
      		VP[pos_izda] = VP[pos_dcha];
      		VP[pos_dcha] = intercambia;
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
   
   	// Inserta un valor en la posición especificada
	void Inserta(int pos_insercion, char valor_nuevo){
		if (total_utilizados < TAMANIO  &&  pos_insercion >= 0  &&  pos_insercion <= total_utilizados){

  	   	 	for (int i = total_utilizados ; i > pos_insercion ; i--){
        		VP[i] = VP[i-1];
    		}
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
   
   void EliminaTodos(){
      total_utilizados = 0;
   }
   
   void Aniade(char nuevo){
      if (total_utilizados < TAMANIO){
         VP[total_utilizados] = nuevo;
         total_utilizados++;
      }
   }
   
   void Modifica(int posicion, char nuevo){
      if (posicion >= 0 && posicion < total_utilizados)
         VP[posicion] = nuevo;
   }

   char Elemento(int indice){
      return VP[indice];
   }
   
   string ToString(){
      string cadena;
      
      for (int i=0; i < total_utilizados; i++)
         cadena = cadena + VP[i];
      
      return cadena;
   }
   
//Metodo para desplazar k posiciones el vector a la derecha (y la ultima pasa a ser la primera en cada iteracion): (requiere del metodo privado Rotar1vez)
	void Rotar (int k){
		for(int i=1; i<=k; i++){
				Rotar1vez();
		}
	}
		 
		 
////////////////BÚSQUEDAS/////////////////
		 
/*		 
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
*/	
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
         		return i + 1;
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
           << " se encuentra en la posición " << pos_encontrado;

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

   cout << "\n" << secuencia.ToString();
}
   
