#include<iostream>
using namespace std;

int main(){
	int anio;
	
	cout << "Introduce el año para saber si es bisiesto o no: ";
	cin >> anio;
	
	if((anio%4==0 && anio%100!=0) || anio%400==0){
		cout << "\n\tEl anio introducido " << anio << " es bisiesto." << endl;
	}
	else{
		cout << "\n\tEl anio introducido " << anio << " no es bisiesto." << endl;
	}
}
