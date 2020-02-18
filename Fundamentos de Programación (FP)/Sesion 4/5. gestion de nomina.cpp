#include<iostream>
using namespace std; 

int main(){
	double const subida4 = 0.04;
	double salario_h, satisfaccion;
	int num_horas, num_resoluciones;
	double salario_final;
	
	cout << "Introduce el precio por horas actual: ";
	cin >> salario_h;
	cout << "Introduce el numero de horas trabajadas: ";
	cin >> num_horas;
	cout << "Introduce el numero de casos resueltos de forma satisfactoria: ";
	cin >> num_resoluciones;
	//filtro de entrada de datos
	do{
	cout << "Introduce el grado de satisfaccion (del 0 al 5): ";
	cin >> satisfaccion;
	}while(satisfaccion < 0 || satisfaccion > 5);
	
	if(num_resoluciones > 30){
		salario_final = (salario_h * num_horas) + (salario_h * num_horas * subida4);
	}
	else{
		salario_final = salario_h * num_horas;
	}
	
	cout << "\n\t El salario final es: " << salario_final << " euros." << endl;
}
