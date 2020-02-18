#include <iostream>
using namespace std; 

int main(){
	int x, y, z;
	
	cout << "Introduce la secuencia de numeros x,y,z (pulsa enter despues de cada numero): ";
	cin >> x >> y >> z;
	
	if((x >= y) && (y >= z)){
		cout << "\n\tLos numeros introducidos estan ordenados descendentemente." << endl;
	}
	else if((x <= y) && (y <= z)){
		cout << "\n\tLos numeros introducidos estan ordenados ascendentemente." << endl;
	}
	else{
		cout << "\n\tLos numeros introducidos no tienen ninguna ordenacion." << endl;
	}
}
