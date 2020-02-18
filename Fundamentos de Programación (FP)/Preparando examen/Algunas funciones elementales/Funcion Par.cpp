////////////////////////////////////////////////////////////////////////////
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// Departamento de Ciencias de la Computación e Inteligencia Artificial
// Autor: Juan Carlos Cubero
////////////////////////////////////////////////////////////////////////////

// Comprobar si un número es par

#include <iostream>
using namespace std;

bool EsPar (int n){
    return n % 2 == 0;
}

int main(){
   int un_numero;
   bool es_par_un_numero;

   cout << "Comprobar si un número es par.\n\n";
   cout << "Introduzca un entero: ";
   cin >> un_numero;
   
   es_par_un_numero = EsPar(un_numero);

   if (es_par_un_numero)
      cout << un_numero << " es par";
   else
      cout << un_numero << " es impar";
}
