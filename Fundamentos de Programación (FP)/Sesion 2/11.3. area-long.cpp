#include <iostream>
#include <cmath>
using namespace std;

int main(){
	double radio;
	double const PI = 3.1415927;
	double longitud, area;
	
	cout << "Introduce la longitud del radio de la circunferencia: ";
	cin >> radio;
	
	longitud = 2.0 * PI * radio;
	area = PI * pow(radio,2);
	
	cout << "\tEl area es: " << area;
	cout << "\n\tLa longitud es: " << longitud;
}
