#include <iostream>
#include<string>
using namespace std;

class SecuenciaCaracteres{
private:
   static const int TAMANIO = 1000;  // 2e6 es un real (dos millones) -> casting automático
                                    // Herramientas -> Opciones del Compilador ->
                                    // Compilador -> Añadir las siguientes opciones
                                    // -Wl,--stack,26000000
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
      // Si el número de caracteres en memoria es muy grande,
      // es mucho más eficiente reservar memoria previamente
      // y usar push_back

      string cadena;

      cadena.reserve(total_utilizados);

      for (int i=0; i < total_utilizados; i++)
         cadena.push_back(vector_privado[i]);
         //cadena = cadena + vector_privado[i]  <- Evitarlo. Muy ineficiente para tamaños grandes;

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
   
   void AniadeVarios(SecuenciaCaracteres nuevos){
      int totales_a_aniadir = nuevos.TotalUtilizados();
      
      for (int i = 0; i < totales_a_aniadir; i++)
         Aniade(nuevos.Elemento(i)); // Es importante entender
   }

   SecuenciaCaracteres ToUpper(){
      SecuenciaCaracteres en_mayuscula;
      
      for(int i = 0; i < total_utilizados; i++)
         en_mayuscula.Aniade(toupper(vector_privado[i]));

      return en_mayuscula;
   }
   
	//FRECUENCIA
	int Frecuencia(char c){
		int contador = 0;
		
		for(int i = 0; i < total_utilizados; i++){ 
			if(vector_privado[i]==c){
				contador++;
			}
		}
		return contador;
	}
   
   //MODA
   char Moda(){
		int TAM = 256;
		int contadores[TAM];
		
		for(int i = 0; i < TAM; i++){  //ponemos a 0 el vector de contadores de frecuencia
			contadores[i] = 0;
		}
		
		char pos;	//después extraemos el entero del caracter con (int)
		for(int i=0; i < total_utilizados; i++){	//relleno vector de contadores
			//contadores[i] = Frecuencia(vector_privado[i]);
			pos = vector_privado[i];
			contadores[(int)pos]++;		
		}
		
		char caracter;
		int ref=0;
		for(int i=0; i < TAM; i++){
			if(contadores[i] > ref){
				ref = contadores[i];
				caracter = i;
			}
		}
		
		return caracter;
   }
   
   //ELIMINA OCURRENCIAS
	void EliminaOcurrencias(char a_borrar){
		for (int i = 0; i < total_utilizados; i++){
			for(int i = 1;  i < total_utilizados; i++){		//hacemos la comprobacion para el siguiente caracter dado que
				if (vector_privado[i] == a_borrar){			//el metodo elimina desplaza los caracteres a la izquierda
					Elimina(i);								//y siempre quedaria 1 sin comprobar (por eso fallaba)
				}	
			}
		}
	}
};



int main(){
/*
  	SecuenciaCaracteres secuencia1;
	char g;
	
	cout << "Introduce una secuencia de caracteres y para finalizar introduce #: " << endl;
	cin >> g;
	int inicio;
	for(inicio=0; g != '#'; inicio++){
		secuencia1.Aniade(g);
		cin >> g;
	}
	
	cout << "\n" << secuencia1.ToString();
*/

 
   // Lectura de los datos:
   const char TERMINADOR = '#';
   int total_introducidos;
   char caracter;
   int capacidad_secuencia;
   SecuenciaCaracteres secuencia;

   total_introducidos = 0;
   capacidad_secuencia = secuencia.Capacidad(); //reservamos memoria para nuestra secuencia, para evitar errores en la lectura
   
   cout << "Introduce una secuencia de caracteres y para finalizar introduce #: " << endl;
   //caracter = cin.get();
   cin >> caracter;	//para descartar espacios

   while (caracter != TERMINADOR && total_introducidos < capacidad_secuencia){
      secuencia.Aniade(caracter);
      //caracter = cin.get();
      cin >> caracter;
   }
   
   char a_eliminar;
   cout << "Introduce un caracter de la cadena para que desaparezca de la misma: " << endl;
   cin >> a_eliminar;
   
   //COMPUTO
   secuencia.EliminaOcurrencias(a_eliminar);
   
   
	//monstrar secuencia tras eliminar el caracter introducido (sin espacios)
	cout << "\n" << secuencia.ToString();
}
