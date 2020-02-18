#include <iostream>
using namespace std;
#include <cmath>

int main(){
	double nu, sigma, x;
	double gausiana, frac, expon;
	
	cout << "Introduzca el valor de la esperanza: ";
	cin >> nu;
	cout << "Introduzca el valor de la desviacion tipica: ";
	cin >> sigma;
	cout << "Introduzca el valor de la abcisa x: ";
	cin >> x;
	
	frac = 1.0 /(sigma * sqrt(2.0 * 3.141516));
	expon = exp(-0.5*(pow((x-nu)/sigma, 2)));
	gausiana = frac * expon;
	
	cout << "La funcion gausiana con los valores introducidos resulta: " << gausiana << endl;
}
