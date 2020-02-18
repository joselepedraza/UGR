#include <iostream> 
using namespace std;  
   
int LeeIntRango(){
	int min = 1;
	int max = 20;
	int nuevo;

	do{
		cout <<  "Introduce el valor entre 1 y 20: ";
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
	int valor;
	long long sumafactorial;

	valor = LeeIntRango();
	sumafactorial = SumaFactorial(valor);
	
	cout << "\n\tLa sumatoria del factorial del valor "<< valor << " es " << sumafactorial << endl;
	
}
