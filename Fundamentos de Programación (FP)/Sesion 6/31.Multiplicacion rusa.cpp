#include<iostream>
using namespace std; 

int main(){

	int num1,num2,resultado;
	
	cout << "Introduce el numero n: ";
	cin >> num1;
	cout << "Introduce el numero m: ";
	cin >> num2;

	while(num1 >= 1){
		if(num1 % 2 != 0){
			resultado = resultado + num2;  
		}
		num1 = num1 / 2;
		num2 = num2 + num2;
   }
   
   cout << "\n\t El resultado de la multiplica cion rusa es: " << resultado << endl;

}
   
