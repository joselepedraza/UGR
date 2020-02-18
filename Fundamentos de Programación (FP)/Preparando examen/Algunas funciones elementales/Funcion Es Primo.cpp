/*FUNCION NUMERO PRIMO*/

#include<iostream>
#include<cmath>
using namespace std;

bool EsPrimo(int valor){
	
	bool es_primo;
	int divisor;
	double tope;
	
	es_primo = true;
	tope = sqrt(valor);
	
	for (divisor = 2 ; divisor <= tope && es_primo ; divisor++){
		if (valor % divisor == 0){
			es_primo = false;
		}
	}
	
	return es_primo;
}

/*Tambien:

bool EsPrimo(int valor){
	bool es_primo;
	int divisor;
	es_primo = true;
	
	for (divisor = 2 ; divisor < valor && es_primo ; divisor++)
		if (valor % divisor == 0)
			es_primo = false;
	return es_primo;
}
*/

int main(){
	int un_numero;
	bool es_primo;
	
	cout << "Comprobar si un número es primo.\n\n";
	cout << "Introduzca un entero: ";
	cin >> un_numero;
	
	es_primo = EsPrimo(un_numero);
	
	if (es_primo)
		cout << un_numero << " es primo";
	else
		cout << un_numero << " no es primo";
	
}
