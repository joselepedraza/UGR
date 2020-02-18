#include<iostream>
using namespace std; 

int main(){
	int const CENTI = -1;
	double tmp_anterior = 0;
	double tmp;
	int ctotal = 0;
	int clongitud = 0;
	int clongitudmax = 0;
	int pos_inicio = 0;
	int posiniciofinal = 0;
	
	
	
	while(tmp != CENTI){
		ctotal++;
		if(tmp_anterior <= tmp){
			clongitud++;
			pos_inicio = ctotal -clongitud;
		}
		else{
			clongitudmax=clongitud;
			clongitud=0;
			posiniciofinal = pos_inicio;
			pos_inicio = ctotal;
		}	
		
	cout << "Introduce el valor de la temperatura (-1 para terminar secuencia): ";
	cin >> tmp;
	}
	
	cout << clongitud << pos_inicio;
	
}
