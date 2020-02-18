#include <iostream>
using namespace std;
#include <cmath>

int main(){
	int num, num_positivo, num_digitos, potencia, digito;
	bool negativo;
   
	cout << "Introduce un entero cualquiera: ";
	cin >> num;
	   
	negativo = num < 0;
	num_digitos = 1;
	potencia = 1;
	num_positivo = abs(num);			//obligamos a que el numero introducido pase a positivo
   
	while (num_positivo > 9){
		num_positivo = num_positivo / 10;
		num_digitos++;
		potencia = potencia * 10;
	}
   
	num_positivo = abs(num);
   
	if(negativo==true){			//Si es negativo primero pintamos el menos (-) y despues hacemos los calculos con el abs de num
		cout << "-  ";
	}
   
	for(int i = 1; i <= num_digitos; i++){
		digito = num_positivo / potencia;
		cout << digito << "  "; 
		num_positivo = num_positivo % potencia;
		potencia = potencia / 10;
	}
	
	cout << endl;

}
