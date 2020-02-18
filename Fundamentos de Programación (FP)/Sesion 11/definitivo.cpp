#include <iostream>
using namespace std;

int main(){
   const int TERMINADOR = -1;
   const int TAMANIO = 1e5;
   double dato, ref;
   double v[TAMANIO];
   int util_v=0, k;
   
   cout << "\nIntroduzca reales con terminador "<< TERMINADOR << "\n";
   cin >> dato;
   while (dato != TERMINADOR && util_v < TAMANIO){
      v[util_v] = dato;
      util_v++;
      cin >> dato;
   }
   cout << "Introduzca un valor de referencia: ";
   cin >> ref;
   cout << "Introduzca el valor k: ";
   cin >> k;
   
   double mayores_que[k];
   int cont_v=0;
   
   int a_insertar;
   
   while(cont_v != util_v){
   	if(v[cont_v] >= ref){
   		a_insertar = v[cont_v];
   		//Insertar de forma ordenada en mayores_que
   		int cont_mayores=0;
			while(a_insertar < mayores_que[cont_mayores] && mayores_que < k){		//sacamos la posicion		
				cont_mayores++;
			}
			for()
			
		}
			cont_v++;
	}
		
		
			
	//Mostrar vector mayores_que
	for (int i = 0; i < cont_mayores; i++)
      cout << mayores_que[i] << " ";
	
}

