//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// Departamento de Ciencias de la Computación e Inteligencia Artificial
// Autor: Alberto Fernández Hilario
//
//////////////////////////////////////////////////////////////////////////

// Media de un conjunto de numeros y mostrar si son mayor o igual a ésta

/*
Escriba un algoritmo para calcular la media aritmética muestral y la desviación estándar
(o típica) muestral de las alturas de tres personas (n=3). Éstos valores serán
reales (de tipo double). La fórmula general para un valor arbitrario de n 
aparece en la relacion de problemas.
* 
Para resolver este problema es necesario usar la función sqrt (raíz cuadrada) 
que se encuentra en la biblioteca cmath.

Estas medidas se utilizan mucho en Estadística para tener una idea de la distribución
de datos. La media (mean en inglés) nos da una idea del valor central y
la desviación típica (standard deviation) nos da una idea de la dispersión de éstos.
Ejecutad el programa con varios valores y comprobad que el resultado es correcto
utilizando una calculadora científica o cualquier calculadora online
*/

#include <iostream>
#include <cmath>
using namespace std;

int main(){
	//Declaracion de variables
	int alt, alt_acum, cont_alt;
	double media;
	
	cont_alt = 0;
	alt_acum = 0;
	//Entrada:
	cout << "Introduce la altura en centimetros (introduce -1 para terminar): ";
	cin >> alt;
	
	while(alt != -1){
		if(alt > 0 && alt < 400){
		//Calculos
		alt_acum = alt_acum + alt;
		cont_alt++;
		media = alt_acum/cont_alt;
		}
	cout << "Introduce la altura en centimetros(introduce -1 para terminar): ";
	cin >> alt;		
	}
	
	//Salida
	cout << "Media aritmetica: " << media << endl;
	
	//Fin del programa
	return 0;
	
}
 
