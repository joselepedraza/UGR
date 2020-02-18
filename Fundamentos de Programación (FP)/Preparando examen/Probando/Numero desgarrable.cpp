/* NUMERO DESGARRABLE*/

#include <iostream>
using namespace std;

int main(){
	int n;
	int izda, dcha, potencia, base;
	bool es_desgarrable = true;
	bool hay_digitos_izda = true;	
		
	do{
		cout << "Introduce el numero para comprobar si es desgarrable o no: ";
		cin >> n;
		
	}while(n < 0);	
  
   	potencia = 1;
	izda = n;
	dcha = 0;
	   
	do{
        izda = n / potencia;
		dcha = n % potencia;
		base = izda + dcha; 	   			
		potencia = potencia * 10;	
		es_desgarrable = (base * base == n);
	  	hay_digitos_izda = (izda != 0);	 
	}while (!es_desgarrable && hay_digitos_izda);
	   
	if (es_desgarrable)
	    cout << "\n" << n << " es desgarrable";
	else 
		cout << n << " no es desgarrable";
   
   cout << "\n\n";
   system("pause");
}
