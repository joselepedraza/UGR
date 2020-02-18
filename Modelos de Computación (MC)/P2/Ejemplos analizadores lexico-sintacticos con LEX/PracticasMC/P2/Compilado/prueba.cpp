#include<iostream>
#include<cmath>

using namespace std;

#define MAXIMO = 500;

int sumar(int n1, int n2){
int n3;
n3= n1 + n2;
return n3;
}

bool sehasumado(num3, num1, num2){
bool lohace = false;
if(num3 == num1+num2)
lohace = true;
return lohace;
}

int main(){
double d1;
double d2;
float nlargo;
char esodice;
string esodicelargo;
unsigned nuncameusan;
unsigned amitampoco;
int numero1; 
int numero2;
int numero3;
int numero4;
numero1 = numero2 = 5;
numero3 = sumar(numero1, numero2);

if(sehasumado(numero3, numero1, numero2)){
	for(int i = 0; i < 5; i++){
		numero3++;
		numero4 += (numero3 - 1);
	}
}
else{
	numero4 = 5;
	while(numero4 <= 20){
		numero4++;
		if(numero3>0){
			numero3--;
			numero3*=1;
			numero3/=1;
		}
	}
}
}

