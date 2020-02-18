#include<iostream>
using namespace std; 

int main(){
	int const CENTI = -1;
	
	double tmp;
	int cont_max=0;
	int cont_dias=1;
	double tmp_anterior=0.0;
	
	int seq_inicio = 0, seq_maxima = 0, seq_actual = 0;
	
	cout << "Introduce el valor de la temperatura (-1 para terminar secuencia): ";
	cin >> tmp;
	
	while(tmp != CENTI){
		//seq_actual++;
		
		if(tmp_anterior <= tmp){
			cont_dias++;
			tmp_anterior = tmp;
			//seq_inicio = seq_actual;
		}

		else if(cont_dias > cont_max){
			cont_max = cont_dias;
			cont_dias = 1;
			tmp_anterior = tmp;
				
		//		seq_maxima = seq_inicio;
		//		seq_inicio = seq_actual;
		}
		
		cout << "Introduce el valor de la temperatura (-1 para terminar secuencia): ";
		cin >> tmp;
	}

	
	cout << "Los dias consecutivos con temperaturas crecientes son: " << cont_max;

}
