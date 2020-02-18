#include <iostream>
using namespace std;

int main(){
	const char TERMINADOR = '#';
	const int TAM = 256;
	char secuencia[TAM];
	char c;
	int util=0;
	
	int contadores[TAM];
	int max, ref;
	char caracter,pos;
	char caracter2 = -1;
	
	cout << "Introduzca la secuencia de caracteres (finaliza con # para terminar): ";
	
	while(c != TERMINADOR){
		c = cin.get();
		
		if(util < TAM){
			secuencia[util]=c;
			util++;
		}
	}
	
	for(int i = 0; i < TAM; i++){  //ponemos a 0 el vector de contadores de frecuencia
		contadores[i] = 0;
	}
	
	for(int j = 0; j < util-1; j++){ //rellenamos el vector de contadores
		pos = secuencia[j];
		contadores[(int)pos]++;
	}
	
	ref=0;
	for(int k = 0; k < TAM; k++){
		if(contadores[k] > ref){
			ref = contadores[k];
			caracter = k;
		}
		else if(contadores[k]==ref){
			caracter2=k;
		}
	}
	
	//mostrar secuencia introducida
	for (int i = 0; i < util -1; i++)
      cout << secuencia[i];
      
	/*vector de contadores
	for (int i = 0; i < TAM; i++)
      cout << contadores[i];
    */
    
	cout << "\n\tLa moda es la letra " << caracter << " y aparece " << ref << " veces." << endl;
	if(caracter2!=-1){
		cout << "\n\tLa moda es la letra " << caracter2 << " y aparece " << ref << " veces." << endl;
	}

	cout << endl << endl;
	system("PAUSE");
}
