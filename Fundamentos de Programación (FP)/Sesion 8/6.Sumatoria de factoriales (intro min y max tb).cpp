#include <iostream> 
using namespace std;  
   
int LeeIntRango(int min,int max){
	int nuevo;

	do{
		cout <<  "Introduce el valor nuevo: ";
		cin >> nuevo;
	}while(nuevo < min || nuevo > max);	

	return nuevo;
}

long long SumaFactorial(int valor){
	
	int factorial = 1;
	int sumatoria = 1;

	for (int multiplicador = 2; multiplicador <= valor ; multiplicador++)    {

		factorial = factorial * multiplicador;
		sumatoria = sumatoria + factorial;
	}
	
	return sumatoria;
}

int main(){
	
	int minimo, maximo;
	int valor;
	long long sumafactorial;
	
	do{
		cout <<  "Introduce el minimo: ";
		cin >> minimo;
	}while(minimo<1 || minimo >= 20);

	do{
		cout <<  "Introduce el maximo: ";
		cin >> maximo;
	}while(maximo<=minimo || maximo > 20);
	
	valor = LeeIntRango(minimo,maximo);
	sumafactorial = SumaFactorial(valor);
	
	cout << sumafactorial;
	
}
