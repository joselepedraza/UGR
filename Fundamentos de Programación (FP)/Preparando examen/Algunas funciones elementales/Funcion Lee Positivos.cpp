/*FUNCION LEE NUMEROS POSITIVOS*/

#include<iostream>
#include<string>

using namespace std;

int LeePositivo (int N, string mensaje){
	
	
	
	do{
		cout << mensaje;
		cin >> N;
		
	}while(N < 0);
	
	return N;
}

int main(){
	
	int salario;
	
	salario = LeePositivo (salario, "\nIntroduzca el salario: ");
	
	cout << "El salario es: " << salario;
	
}

/*También:
int LeePositivo(string mensaje){
	int a_leer;
	
	cout << mensaje;
	
	do{
		cin >> a_leer
	}while (a_leer <= 0);
	
	return a_leer;
}

int main(){

	int salario;
	salario = LeePositivo("\nIntroduzca el salario en miles de euros: ");
......
}
*/
