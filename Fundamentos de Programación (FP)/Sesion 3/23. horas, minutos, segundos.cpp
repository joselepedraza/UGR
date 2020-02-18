#include <iostream>
using namespace std;

int main(){
	int horas, minutos, segundos;
	int dias1, horas1, minutos1, segundos1;
	int horas2, minutos2;
	
	cout << "Introduce un numero de horas: ";
	cin >> horas;
	cout << "Introduce un numero de minutos: ";
	cin >> minutos;
	cout << "Introduce un numero de segundos: ";
	cin >> segundos;
	
	segundos1 = segundos % 60;
	minutos1 = segundos / 60 + minutos;
	minutos2 = minutos1 % 60;
	horas1 = minutos1 / 60 + horas;
	horas2 = horas1 % 24;
	dias1 = horas1 / 24;
	
	cout << "\tEl numero real de dias es: " << dias1 << endl;
	cout << "\tEl numero real de horas es: " << horas2 << endl;
	cout << "\tEl numero real de minutos es: " << minutos2 << endl;
	cout << "\tEl numero real de segundos es: " << segundos1 << endl;
	
}
