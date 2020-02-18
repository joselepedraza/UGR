#include<iostream>
using namespace std;

int main(){
	int x, y, z;
	int aux;
	
	cout << "Introduce el valor de la variable x: ";
	cin >> x;
	cout << "Introduce el valor de la variable y: ";
	cin >> y;
	cout << "Introduce el valor de la variable z: ";
	cin >> z;
	
	aux = z;
	z = y;
	y = x;
	x = aux;
	
	cout << "x = " << x << "\ny = " << y << "\nz = " << z << endl;
	
}
