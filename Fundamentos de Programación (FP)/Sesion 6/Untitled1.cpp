#include<iostream>
using namespace std; 

int main(){
	int const CENTI = -1;
	
	double tmp;
	double tmp_anterior=0.0;
	int subidatmp=0;	
	int subidamax=0;
	int seq_inicio = 0, seq_maxima = 0, seq_actual = 0;
	
	cout << "Introduce el valor de la temperatura (-1 para terminar secuencia): ";
	cin >> tmp;
	
	while(tmp != CENTI){
		
		if(tmp_anterior<=tmp){
			subidatmp++;
			tmp_anterior = tmp;
			if(subidatmp>subidamax)
				subidamax = subidatmp;
		}
		else  if(subidatmp<subidamax && tmp < tmp_anterior)
			subidatmp =0;
		
			
			
		cout << "Introduce el valor de la temperatura (-1 para terminar secuencia): ";
		cin >> tmp;
	}
	
	
	cout << "Los dias consecutivos con temperaturas crecientes son: " << subidatmp;
}
