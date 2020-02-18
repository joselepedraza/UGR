#include <iostream> 
using namespace std;  
   
int main(){    

//Exponencial x^n
	double base;
	int exponente;
	double potencia;

	cout << "\nIntroduzca la base: ";
	cin >> base;
	cout << "\nIntroduzca el exponente: ";
	cin >> exponente;

	potencia = 1.0;

	for (int i = 1; i <= exponente; i++){
		potencia = potencia * base;
	}
	
	cout << "\n\t" << base << " elevado a " << exponente << " es igual a " << potencia << endl;
	
//Factorial
    long long factorial;
	int num;
	int multiplicador;
	int sumatoria;
	
	do{
		cout << "\nIntroduzca un entero entre 0 y 20: ";		//maximo valor al que se le puede calcular el factorial
		cin >> num;
	}while(num<=0 || num>=20);
	
	factorial = 1;
	sumatoria = 1;

	for (multiplicador = 2; multiplicador <= num ; multiplicador++)    {

		factorial = factorial * multiplicador;
		sumatoria = sumatoria + factorial;
	}
	
	cout << "\n\tEl factorial de " << num << " es " << factorial;
	cout << "\n\tLa sumatoria del factorial de " << num << " es " << sumatoria;
	
}
