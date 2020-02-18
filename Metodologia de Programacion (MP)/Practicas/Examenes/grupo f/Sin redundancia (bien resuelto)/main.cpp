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

	char filePath[30];
	bool found;

	/// Examen: Leer fichero en vector A
	cout << "Fichero A: ";
	cin >> filePath;

	FichA.open(filePath);
	FichA >> elemA;
	A = new string[elemA];
	for(int i=0; i<elemA;  i++)
		FichA >> A[i];
	FichA.close();
	imprimirVector(A, elemA);

	/// Examen: Leer fichero en vector B
	cout << "Fichero B: ";
	cin >> filePath;

	FichB.open(filePath);
	FichB >> elemB;
	B = new string[elemB];
	for(int i=0; i<elemB;  i++)
		FichB >> B[i];
	FichB.close();
	imprimirVector(B, elemB);

	/// Examen: Calcular resultado
	elemResultado = elemB - elemA; //Asumimos que no hay elementos repetidos
	Resultado  = new string[elemResultado];
	for(int i=0, c=0; i<elemB && c<elemResultado; i++){
		found = false;
		for(int j=0; j< elemA && !found; j++){
			found = A[j] == B[i];
		}
		if(!found)
			Resultado[c++] = B[i];
	}

	/// Examen: Mostrar resultado
	imprimirVector(Resultado, elemResultado);

	/// Examen: Terminación del programa
	delete[] A;
	delete[] B;
	delete[] Resultado;
	A = B = Resultado = NULL;

	return 0;
}

