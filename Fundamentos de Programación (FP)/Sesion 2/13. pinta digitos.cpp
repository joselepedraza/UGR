#include <iostream>

using namespace std;

int main(){
	int num, unidad, decena, centena;
	
	cout << "Introduce un numero entero de 3 cifras: ";
	cin >> num;
	
	unidad = num % 10;
	decena = (num % 100 - unidad) / 10;
	centena = (num % 1000 - decena) / 100;
	
	cout << "\n  ";
	cout << centena;
	cout << "  ";
	cout << decena;
	cout << "  ";
	cout << unidad << endl;
	
}
