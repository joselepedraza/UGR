/*FUNCION NUMERO COMBINATORIO*/


#include <iostream>
using namespace std;

long long Factorial (int n){
	
	int i;
	long long fact = 1;
	
	for (i = 2; i <= n; i++)
		fact = fact * i;
		
	return fact;
}

long long Combinatorio(int a, int b){
	
	return Factorial(a)/(Factorial(b) * Factorial(a-b));

}

int main(){

	int elementos, grupos;
	long long resultado;

	cout << "Número Combinatorio.\n";
	cout << "Introduzca número total de elementos a combinar: ";
	cin >> elementos;
	cout << "Introduzca cuántos se escogen en cada grupo: ";
	cin >> grupos;
	
	resultado = Combinatorio(elementos, grupos);
	
	cout << elementos << " sobre " << grupos << " = " << resultado;
}
