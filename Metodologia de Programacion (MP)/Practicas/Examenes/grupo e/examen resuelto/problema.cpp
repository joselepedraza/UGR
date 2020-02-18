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
	FichA.open("mod3A.txt");

	FichA >> elemA;

	A = new string[elemA];

	for (int i = 0; i < elemA; i++) {
		FichA >> A[i];
	}

	imprimirVector(A, elemA);

	/// Examen: Leer fichero en vector B

	FichB.open("mod3B.txt");

	FichB >> elemB;

	B = new string[elemB];

	for (int i = 0; i < elemB; i++) {
		FichB >> B[i];
	}

	imprimirVector(B, elemB);

	/// Examen: Calcular resultado

	int contador = 0;
	bool aparece;

	for (int i = 0; i < elemA; i++) {
		aparece = false;
		for (int j = 0; j < elemB; j++) {
			if (A[i] == B[j]) {
				aparece = true;
			}
		}
		if (aparece == false) {
			contador++;
		}
	}

	cout << contador << endl;

	elemResultado = contador;

	Resultado = new string[elemResultado];

	contador = 0;

	for (int i = 0; i < elemA; i++) {
		aparece = false;
		for (int j = 0; j < elemB; j++) {
			if (A[i] == B[j]) {
				aparece = true;
			}
		}
		if (aparece == false) {
			Resultado[contador] = A[i];
			contador++;
		}
	}

	/// Examen: Mostrar resultado
	imprimirVector(Resultado, elemResultado);

	/// Examen: Terminación del programa

	FichA.close();
	FichB.close();

	delete [] A;
	delete [] B;
	delete [] Resultado;

	return 0;
}

