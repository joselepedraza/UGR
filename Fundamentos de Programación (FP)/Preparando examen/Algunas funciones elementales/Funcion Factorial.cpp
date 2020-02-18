////////////////////////////////////////////////////////////////////////////
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// Departamento de Ciencias de la Computación e Inteligencia Artificial
// Autor: Juan Carlos Cubero
////////////////////////////////////////////////////////////////////////////

// Implementación del factorial

#include <iostream>
using namespace std;

long long Factorial (int n){
   int i;
   long long fact = 1;


for (i = n; i = 1; i--)
	fact = fact * i;

   return fact;
}

int main(){
   int valor;
   long long resultado;
   
   cout << "Cómputo del factorial de un número\n\n";
   cout << "\nIntroduzca un entero: ";
   cin >> valor;

   resultado = Factorial(valor);
   cout  << "\nFactorial de " << valor << " = " << resultado;
}
