/*FUNCION IMPRIME LINEAS*/

#include<iostream>
using namespace std;

/*
void ImprimeLineas (int num_lineas){
	int i;
	for (i = 1; i <= num_lineas ; i++)
		cout << "\n************";
}

void Presentacion(int tope_lineas){
	ImprimeLineas (tope_lineas);
	cout << "  Programa básico de Trigonometría";
	ImprimeLineas (tope_lineas);
}

int main(){
	
	Presentacion(5);
	
}

*/

void ImprimeLineas (int num_lineas, int numero_asteriscos){
for (int i = 1; i <= num_lineas ; i++)
cout << "\n";
for (int j = 1; j <= numero_asteriscos; j++)
cout << "*";
}


