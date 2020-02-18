#include<iostream>
using namespace std; 

int main(){
	char letra;
	int edad, adivine, anio;
	
	bool let = false, eda = false, adi = false, ani = false;
	
	cout << "Introduce una letra para comprobar si es mayuscula o minuscula: ";
	cin >> letra;
	cout << "Introduce la edad: ";
	cin >> edad;
	cout << "Introduce el numero para comprobar si esta entre 1 y 100: ";
	cin >> adivine;
	cout << "Introduce el año para comprobar si es bisiesto: ";
	cin >> anio;
	
	if(edad < 18 || edad > 65){
		eda = true;
	}
	
	if(adivine >= 1 && adivine <= 100){
		adi = true;
	}
	
	if(letra >= 'a' && letra <= 'z'){
		let = true;
	}
	
	
	if((anio%4==0 && anio%100!=0) || anio%400==0){		//Los años bisiestos son aquellos que o bien son divisibles 
		ani = true;													//por 4 pero no por 100, o bien son divisibles por 400.
	}
	
	cout << let;
	cout << eda;
	cout << adi;
	cout << ani;
	
}
