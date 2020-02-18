/**
@file main.cpp
@brief 
Universidad de Granada
Metodología de la Programación I
Examen de laboratorio 

Por favor, rellene las funciones que se indican
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/**
@brief Imprime el contenido de un vector de string
@param v 	Vector de string
@param n	Número de elementos que contiene @a v
*/
void imprimirVector(string *v, int n)  {
	cout << n << " elementos" << endl;
	for (int i=0; i<n; i++)
		cout << "["<<i<<"] = " << v[i] << endl;
}

int main()  {
	string *A=NULL, *B=NULL, *Resultado=NULL;
	int elemA, elemB, elemResultado;
	ifstream FichA, FichB;
	
	/// Examen: Leer fichero en vector A
	imprimirVector(A, elemA);

	/// Examen: Leer fichero en vector B
	imprimirVector(B, elemB);

	/// Examen: Calcular resultado

	/// Examen: Mostrar resultado
	imprimirVector(Resultado, elemResultado);

	/// Examen: Terminación del programa

	return 0;
}
 
