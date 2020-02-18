#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
class  SecuenciaEnteros{
private:
   static  const  int  TAMANIO  =  50;
   int  vector_privado[TAMANIO];
   int  total_utilizados;

public:
   SecuenciaEnteros()
	{total_utilizados = 0;
    }

   int  TotalUtilizados(){
      return  total_utilizados;
   }

   void  Aniade(int  nuevo){
      if (total_utilizados  <  TAMANIO){
         vector_privado[total_utilizados]  =  nuevo;
         total_utilizados++;
      }
   }

   int  Elemento(int  indice){
      return  vector_privado[indice];
   }

   void Modifica (int indice_componente, int nuevo){
      if (indice_componente >= 0  &&  indice_componente < total_utilizados)
         vector_privado[indice_componente] = nuevo;
   }
   
   void Invierte (){
   	int posicion_cola = total_utilizados;
		for (int i = 0 ; i < total_utilizados ; i++){
			Modifica(i,posicion_cola);
			posicion_cola--;
		}
   }
   
	int Moda(){
		int valor_guardado;
		int k = 0;
		int contador;
		int vector_auxiliar[TAMANIO];
		int moda;
		
		//Reccorre el vector privado pero salvando cada posicion en una variable local
		for(int i = 0 ; i < total_utilizados ; i++){
			contador = 0;
			valor_guardado = vector_privado[i];
			//Recorremos el vector privado para cada valor guardado
			for(int j = 0 ; j < total_utilizados ; j++){
				if(valor_guardado == vector_privado[j]){
					contador++;
				}
			}
			vector_auxiliar[i] = contador;
		}
		
		//Vemos el vector de apariciones de cada numero
		cout << endl << "El vector de apariciones es: ";
		for(int i = 0 ; i < total_utilizados ; i++){
			cout << vector_auxiliar[i] << " ";
		}
		
		cout << endl << endl;
		
		//Calculamos la moda
		int posicion_mas_repetida = vector_auxiliar[0];
		for(int i = 0 ; i < total_utilizados ; i++){
			if (vector_auxiliar[i] >= posicion_mas_repetida){
				posicion_mas_repetida = i;
			}
		}
		return moda = vector_privado[posicion_mas_repetida];
	}

	
   	
   
  
// ..................................

};

void mostrar(SecuenciaEnteros s)
{int n = s.TotalUtilizados();
 for(int i=0; i < n; i++)
  cout << s.Elemento(i) << ", ";

 cout << endl;
}

int main(){
   SecuenciaEnteros se1, se2, se3;
   int min, max,i;
   
 
	//----------------------------------------
	//----------------------------------------
  
   // secuencia para probar el primer metodo
   for(i=1;i<11;i++)
   	se1.Aniade(i);
   
   //Mostramos la secuencia 1 original
   cout << "Secuencia 1: ";  
	mostrar(se1);
	
	//Invertimos la secuencia 1 original
   se1.Invierte();
   
   //Mostramos la secuencia 1 invertida
   cout << "\nSecuencia 1 invertida: ";
	mostrar(se1);
	
	//----------------------------------------
	//----------------------------------------

   // secuencia para probar el segundo metodo
   srand(time(0));
   max = 5;
   min = -5;
   
   // relleno una secuencia con valores aleatorios en [min,max]
   for(i=0;i<25;i++)
     se2.Aniade(min+(rand()%(max-min))+1);
	
	//Mostramos la secuencia 2
	cout << "\n\nSecuencia 2: ";
	mostrar(se2);
	cout << endl << "La moda de la secuencia es: " << se2.Moda();
	
	
	
	//----------------------------------------
	//----------------------------------------
	
  // secuencia para probar el tercer metodo

   for(i=1;i<6;i++)
   	se3.Aniade(i);


}
