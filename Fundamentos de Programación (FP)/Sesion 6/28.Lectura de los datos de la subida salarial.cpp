/*EJERCICIO 11:

#include<iostream>
using namespace std; 

int main(){
	double const SUBIDA4 = 0.04;
	double const SUBIDA2 = 0.02;
	double const SUBIDA3 = 0.03;
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
		if(satisfaccion >= 4){
			salario_final = (salario_h * num_horas) + (salario_h * num_horas * SUBIDA4) + (salario_h * num_horas * SUBIDA2);
		}
		else{
			salario_final = (salario_h * num_horas) + (salario_h * num_horas * SUBIDA4);
		}
	}
	else if(num_resoluciones > 20 && num_resoluciones < 30){
		if(satisfaccion >= 4){
				salario_final = (salario_h * num_horas) + (salario_h * num_horas * SUBIDA3) + (salario_h * num_horas * SUBIDA2);
		}
		else{
			salario_final = (salario_h * num_horas) + (salario_h * num_horas * SUBIDA3);
		}
	}	
	else if(satisfaccion >=4){
		salario_final = (salario_h * num_horas) + (salario_h * num_horas * SUBIDA2);
	}
	else{
		salario_final = salario_h * num_horas;
	}
	cout << "\n\t El salario final es: " << salario_final << " euros." << endl;
}
*/


#include<iostream>
using namespace std; 

int main(){
	double salario_h;
	int codemp;
	
	do{
		cout << "Introduce el salario por horas: ";
		cin >> salario_h;
	}while(salario_h < 0);
	
	while(codemp != -1){
	do{
		cout << "Introduce el codigo del empleado (-1 para terminar): ";
		cin >> codemp;
	}while((codemp<=0 || codemp>=4) || codemp !=-1);
	
	}


}

