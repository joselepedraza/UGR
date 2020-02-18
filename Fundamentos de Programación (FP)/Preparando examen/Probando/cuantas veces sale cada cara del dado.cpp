/*
Dado un dado con x caras, tirar 10000 veces, cuantas veces sale cada cara?
*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class SecuenciaEnteros{
	private:
		static const int TAMANIO = 10000;
		int VP[TAMANIO];
		int total_utilizados;
	
		
	public:
		SecuenciaEnteros()
			:total_utilizados(0){
		}		
		
		int TotalUtilizados(int caras){
			total_utilizados = caras;
			return total_utilizados;
		}
		
		int Elemento(int indice,int caras){
			if(indice>caras)
			return 0;
			return VP[indice];
		}
		
		void TirarDado (int caras){
			
			for(int i = 0; i<10000; i++){
				VP[(int)rand()%caras]++;
			}		
		}
};

int main(){
	SecuenciaEnteros dado1;
	int caras, veces_pos, i;
	
	SecuenciaEnteros();
	
	cout << "Introduce el numero de caras del dado: ";
	cin >> caras;
	
	dado1.TotalUtilizados(caras);
	dado1.TirarDado(caras);
	
	
	cout << "Introduzca el numero de la cara a comprobar cuantas veces ha salido: ";
	cin >> i;
	
	veces_pos = dado1.Elemento(i-1,caras);
	
	cout << "La cara " << i << " aparece " << veces_pos << " veces en 10000 tiradas.";
	

}

