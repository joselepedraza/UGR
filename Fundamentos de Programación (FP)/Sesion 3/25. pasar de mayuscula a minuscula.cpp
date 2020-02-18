#include <iostream>
using namespace std; 

int main(){
	char mayuscula, minuscula;
	int const DIF_MAYUS_MINUS = 'a' - 'A';
	
	cout << "Introduce una letra mayuscula: ";
	cin >> mayuscula;
	
	if ((mayuscula >= 'A') && (mayuscula <= 'Z')){
		minuscula = mayuscula + DIF_MAYUS_MINUS;
	}
	else{
		minuscula = mayuscula;
	}
	
	cout << "La letra minuscula es: " << minuscula;
}
