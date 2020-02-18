#include<iostream>
#include<string>
using namespace std;

int LeerValorPositivo (string msg){
	int N;
	do{
		cout << msg;
		cin >> N;
	}while( N < 0);
	return N;
}

bool EsDesgarrable (int N){
	int izq, drch, potencia, base;
	bool es_desgarrable = true;
	bool hay_digitos_izq = true;
	
	potencia = 1;
	izq = N;
	drch = 0;
	
	do{
		izq = N / potencia;
		drch = N % potencia;
		base = izq + drch;
		potencia = potencia * 10;
		es_desgarrable = (base * base == N);
		hay_digitos_izq = (izq != 0);
	}while( !es_desgarrable && hay_digitos_izq);
		
	return es_desgarrable;
	
}

int main(){
	
	int num;
	bool es_desgarrable;
	
	num = LeerValorPositivo("Introduce un numero para comprobar si es desgarrable o no: ");
	
	es_desgarrable = EsDesgarrable(num);
	
	if (es_desgarrable == true){
		cout << "El numero " << num << " es desgarrable." << endl;
	}
	else{
		cout << "El numero " << num << " no es desgarrable." << endl;
 	}
 	
system ("PAUSE");	
}





