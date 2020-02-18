#include <iostream>
using namespace std;

int main(){
	double salario_base, salario_final;
	double const DOS = 1.02;
	double const TRES = 1.03;
	
	cout << "Introduce el salario: ";
	cin  >> salario_base;
	
	cout << "El salario final incrementado un 2% es: " << salario_base * DOS << endl;
	cout << "El salario final incrementado un 3% es: " << salario_base * DOS * TRES << endl;
}
