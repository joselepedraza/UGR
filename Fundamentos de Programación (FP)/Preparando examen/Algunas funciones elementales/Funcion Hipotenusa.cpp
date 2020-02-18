////////////////////////////////////////////////////////////////////////////
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// Departamento de Ciencias de la Computación e Inteligencia Artificial
// Autor: Juan Carlos Cubero
////////////////////////////////////////////////////////////////////////////

// Cómputo de la Hipotenusa de un triángulo rectángulo

#include <iostream>
#include <cmath>
using namespace std;

double Hipotenusa(double un_lado, double otro_lado){
   return sqrt(un_lado*un_lado + otro_lado*otro_lado);
}

int main(){
   double lado1_A, lado2_A, lado1_B, lado2_B,
          hipotenusa_A, hipotenusa_B;

   cout << "Cómputo de la hipotenusa de un triángulo rectángulo.\n\n";
   cout << "Introduzca los dos lados del primer triángulo:\n";
   cin >> lado1_A;
   cin >> lado2_A;
   cout << "Introduzca los dos lados del segundo triángulo:\n";
   cin >> lado1_B;
   cin >> lado2_B;

   hipotenusa_A = Hipotenusa(lado1_A, lado2_A);
   hipotenusa_B = Hipotenusa(lado1_B, lado2_B);
   
   cout << "\n\n";
   cout << "Las hipotenusas valen (respectivamente): \n";
   cout << hipotenusa_A << "\n";
   cout << hipotenusa_B;
   

   }
