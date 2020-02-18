#include <iostream>
using namespace std;

int main(){
   const int TERMINADOR = -1;
   const int TAMANIO = 1e5;
   double dato, referencia;
   double vector[TAMANIO];
   int util_vector, util_mayores_que, k;
   
   cout << "\nIntroduzca reales con terminador "<< TERMINADOR << "\n";
        
   util_vector = 0;
   cin >> dato;

   while (dato != TERMINADOR && util_vector < TAMANIO){
      vector[util_vector] = dato;
      util_vector++;
      cin >> dato;
   }
   cout << "Introduzca un valor de referencia: ";
   cin >> referencia;
   cout << "Introduzca el valor k: ";
   cin >> k;
   
   double mayores_que[k];
   
   /*
   Recorrer las componentes del vector original
	Si es mayor que la referencia, insertar dicho
	valor de forma ordenada en el vector "mayores_que"
	El vector "mayores_que" siempre tendrá,
	como mucho, k componentes
	*/
	int j;
	int i=0;
	
	//for(int i = 0; i<util_vector;i++){
	
		while((util_mayores_que < k) && (i < util_vector)){
		
			if(vector[i]>=referencia){
				j=0;
				while((mayores_que[j]<vector[i]) && (j<util_mayores_que)){
					j++;
					if(util_mayores_que==j){
						mayores_que[j]=vector[i];
						util_mayores_que++;		//
					}
					else{
						int cont=0;
						if(cont < k){
							//si el nuevo elemento es menor al que tengo en la primera posicion del vector
        					bool nosal = true;
        					int pos;
        					//recorremos el vector hasta encontrar la posicion donde va el nuevo elemento
        					for(pos = 0 ; (pos < cont)&&nosal ; pos++){
         						 if(mayores_que[pos] >= vector[i]){
            						nosal = false;
          						}
        					}
        					//movemos a derecha
        					for(int s = cont ; s >= pos ; s--)
          						mayores_que[s+1] = vector[s];
        					mayores_que[pos] = vector[i];
        					cont++;
        				}
						/*
						int ulti;
						ulti=mayores_que[util_mayores_que-1];
						for(j=util_mayores_que-1;j=0;j--){
							
							mayores_que[j+1]=mayores_que[j];
						}
						mayores_que[0]=ulti;
						util_mayores_que++;
						mayores_que[util_mayores_que]=vector[i];
						*/
						
						/*
						int pos;
						while(z < util_mayores_que && pos==z){
							if(mayores_que[z]>vector[i]){
								pos=z;
							}
							z++;
						}
						*/
						/*
						int pos;
						for(int z=0; z<util_mayores_que && pos==z; z++){
							if(mayores_que[z]>vector[i]){
								pos=z;
							}
						}
						for(int t=0; t<pos;t++){
							mayores_que
						}
						*/
					}
					
				}
			}
			i++;
		}
//	}
	
	//Mostrar vector mayores_que
	for (int i = 0; i < util_mayores_que; i++)
      cout << mayores_que[i] << " ";
	
}
