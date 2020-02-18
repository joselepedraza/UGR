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
	int elemA, elemB, elemResultado = 0;
	ifstream FichA, FichB;
  ofstream final;

	/// Examen: Leer fichero en vector A
  FichA.open("mod5A.txt");
  FichA >> elemA;
  A = new string[elemA];
  for(int i = 0; i < elemA; i++){
    FichA >> A[i];
  }
	imprimirVector(A, elemA);
  cout << endl;

	/// Examen: Leer fichero en vector B
  FichB.open("mod5B.txt");
  FichB >> elemB;
  B = new string[elemB];
  for(int i = 0; i < elemB; i++){
    FichB >> B[i];
  }
  imprimirVector(B, elemB);
  cout << endl;

	/// Examen: Calcular resultado
  final.open("resultado.txt");
  int contador = 0;
  bool aparece;
  for(int i = 0; i < elemB; i++){
    aparece = false;
    for (int j = 0; j < elemA; j++) {
      if (B[i] == A[j]) {
        aparece = true;
      }

    }
    if (aparece == false){
      elemResultado++;
    }
  }

  Resultado = new string[elemResultado];

  for(int i = 0; i < elemB; i++){
    aparece = false;
    for (int j = 0; j < elemA; j++) {
      if (B[i] == A[j]) {
        aparece = true;
      }
    }
    if (aparece == false){
      Resultado[contador] =  B[i];
      contador++;
    }
  }

  for (int i = 0; i < elemResultado; i++) {
    final << Resultado[i] << endl;
  }
	/// Examen: Mostrar resultado
	imprimirVector(Resultado, elemResultado);

	/// Examen: Terminación del programa
  FichA.close();
  FichB.close();
  final.close();

  delete[]Resultado;
  delete[]A;
  delete[]B;

	return 0;
}
