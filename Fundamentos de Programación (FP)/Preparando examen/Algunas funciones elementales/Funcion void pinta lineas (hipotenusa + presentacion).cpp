/*FUNCION HIPOTENUSA + PRESENTACION:
	-funcion void de presentacion
	-funcion cuadrado
	-funcion hipotenusa

	
#include <iostream>
#include <cmath>
using namespace std;
double Cuadrado(double entrada){
	return entrada*entrada;
}

double Hipotenusa(double un_lado, double otro_lado){
	return sqrt(Cuadrado(un_lado) + Cuadrado(otro_lado));
}

void Presentacion(int tope_lineas){
	int i;
	for (i = 1; i <= tope_lineas ; i++)
		cout << "\n************  ";
	cout << "Programa básico de Trigonometría";
	for (i = 1; i <= tope_lineas ; i++)
		cout << "\n************";
}

int main(){
	double lado1, lado2, hipotenusa;
	
	Presentacion(5);
	
	cout << "\n\nIntroduzca los lados del triángulo rectángulo: ";
	cin >> lado1;
	cin >> lado2;
	
	hipotenusa = Hipotenusa(lado1,lado2);
	
	cout << "\nLa hipotenusa vale " << hipotenusa;
}

*/

////////////////////////////////////////////////////////////////////////////
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// Departamento de Ciencias de la Computación e Inteligencia Artificial
// Autor: Juan Carlos Cubero
////////////////////////////////////////////////////////////////////////////

// Cómputo de la hipotenusa con una presentación con funciones void

#include <iostream>
#include <cmath>
using namespace std;

double Cuadrado(double entrada){
   return entrada*entrada;
}

double Hipotenusa(double un_lado, double otro_lado){
   return sqrt(Cuadrado(un_lado) + Cuadrado(otro_lado));
}

void ImprimeAsteriscos (int num_asteriscos){
   for (int i = 1 ; i <= num_asteriscos ; i++)
      cout << "*";
}

void ImprimeLineas (int num_lineas, int num_asteriscos){
   for (int i = 1; i <= num_lineas ; i++){
      cout << "\n";
      ImprimeAsteriscos(num_asteriscos);
   }
}

void Presentacion(string mensaje, int tope_lineas, int num_asteriscos){
   ImprimeLineas (tope_lineas, num_asteriscos);
   cout << "\n" << mensaje;
   ImprimeLineas (tope_lineas, num_asteriscos);
}

int main(){
   double lado1, lado2, hipotenusa;

   Presentacion("Programa básico de Trigonometría", 3, 32);

   cout << "\n\nIntroduzca los lados del triángulo rectángulo:\n";
   cin >> lado1;
   cin >> lado2;

   hipotenusa = Hipotenusa(lado1,lado2);

   cout << "\nLa hipotenusa vale " << hipotenusa;
}
