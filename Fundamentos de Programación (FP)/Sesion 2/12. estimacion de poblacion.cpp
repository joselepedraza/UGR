#include <iostream>

using namespace std;

int main(){
	double const  TASA = 1000.0;
	long long pob_ini, pob_fin1, pob_fin2, pob_fin3;
	long long morta, nata, emig;
	
	cout << "Introduzca la poblacion inicial: ";
	cin >> pob_ini;
	cout << "Introduzca la tasa de natalidad: ";
	cin >> nata;
	cout << "Introduzca la tasa de mortalidad: ";
	cin >> morta;
	cout << "Introduzca la tasa de emigracion: ";
	cin >> emig;
	
	pob_fin1 = pob_ini + (nata * (pob_ini/TASA)) - (morta * (pob_ini/TASA)) + emig * (pob_ini/TASA);
	pob_fin2 = pob_fin1 + (nata * (pob_fin1/TASA)) - (morta * (pob_fin1/TASA)) + emig * (pob_fin1/TASA);
	pob_fin3 = pob_fin2 + (nata * (pob_fin2/TASA)) - (morta * (pob_fin2/TASA)) + emig * (pob_fin2/TASA);
	
	cout << "\n\tLa poblacion final el primer anio es: " << pob_fin1 << " habitantes." << endl;
	cout << "\n\tLa poblacion final el segundo anio es: " << pob_fin2 << " habitantes." << endl;
	cout << "\n\tLa poblacion final el tercer anio es: " << pob_fin3 << " habitantes." << endl;
}
