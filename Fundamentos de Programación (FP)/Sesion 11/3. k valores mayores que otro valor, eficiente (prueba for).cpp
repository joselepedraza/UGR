#include <iostream>
using namespace std;

int main(){
   const int TERMINADOR = -1;
   const int TAMANIO = 1e5;
   double dato, ref;
   double v[TAMANIO];
   int util_vector=0, k;
   
   cout << "\nIntroduzca reales con terminador "<< TERMINADOR << "\n";
   cin >> dato;
   while (dato != TERMINADOR && util_vector < TAMANIO){
      v[util_vector] = dato;
      util_vector++;
      cin >> dato;
   }
   cout << "Introduzca un valor de referencia: ";
   cin >> ref;
   cout << "Introduzca el valor k: ";
   cin >> k;
   
   double nuevo[k];
   
   /*
   Recorrer las componentes del vector original
	Si es mayor que la referencia, insertar dicho
	valor de forma ordenada en el vector "mayores_que"
	El vector "mayores_que" siempre tendr�,
	como mucho, k componentes
	*/
	int cont = 0;
	for(int i = 0 ; i < TAMANIO ; i++){
    //si el valor del vector es mayor o igual al de ref añadimos
    	if(v[i] >= ref){
    		//Si la posicion es menor al tamaño del vector podemos añadir
      		if(cont < k){
        		//si el nuevo elemento es menor al que tengo en la primera posicion del vector
        		bool nosal = true;
        		int pos;
        		//recorremos el vector hasta encontrar la posicion donde va el nuevo elemento
        		for(pos = 0 ; (pos < cont)&&nosal ; pos++){
          			if(nuevo[pos] >= v[i]){
            			nosal = false;
          			}
        		}
        		//movemos a derecha
        		for(int s = cont ; s >= pos ; s--){
          			nuevo[s+1] = nuevo[s];
          		}
        		nuevo[pos] = v[i];
        		cont++;
			}
    	}
	}	
	

	
	//Mostrar vector mayores_que
	for (int i = 0; i < cont; i++)
      cout << nuevo[i] << " ";
	
}
