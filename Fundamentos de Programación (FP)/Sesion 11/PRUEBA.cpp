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
   int cont_mayores=0;
   int a_insertar;
   int a_desplazar;
   int i,j;
   
   while(cont_v != util_v){
   	if(v[cont_v] >= ref){
   		//Insertar de forma ordenada en mayores_que
   		a_insertar = v[cont_v];
   		for(i = 1; i<k/* && cont_mayores<k*/; i++){
   			a_desplazar = mayores_que[i];
   			//if(mayores_que[i] >= a_insertar && mayores_que[i-1] <= a_insertar){
   				for(j=k; j > 0 /*cont_mayores*/ && a_desplazar < mayores_que[j-1]; j--){
   					mayores_que[j] = mayores_que[j-1];
   					//cont_mayores++;
   				}
   				mayores_que[i]=a_desplazar;
   			//}	
   			
		}
		mayores_que[cont_mayores] = a_insertar;
   		cont_mayores++;
   	}
	cont_v++;	
   }
			
	//Mostrar vector mayores_que
	for (int i = 0; i < cont_mayores; i++)
      cout << mayores_que[i] << " ";
	
}

