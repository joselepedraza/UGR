//////////////////////////////////////////////////////////////////////////
//
// Fundamentos de Programaci�n
// ETS Inform�tica y Telecomunicaciones
// Universidad de Granada
// Departamento de Ciencias de la Computaci�n e Inteligencia Artificial
// Autor: Juan Carlos Cubero
//
//////////////////////////////////////////////////////////////////////////

// Conversi�n unidades

/*
Realice un programa que nos pida una longitud cualquiera dada en metros.
El programa deber� calcular e imprimir en pantalla el equivalente de dicha
longitud en pulgadas, pies, millas y millas marinas. Para el c�lculo,
utilice la siguiente tabla de conversi�n del sistema m�trico:

1 pulgada= 25,4 mil�metros
1 pie = 30,48 cent�metros
1 yarda = 0,9144 metros
1 milla = 1609,344 metros

Ejemplo de entrada: 1 -- Salida correcta: 39.3701 3.28084 1.09361 0.00062
*/

#include <iostream>
#include <cmath>
using namespace std;

int main(){
   /*  
   1 pulgada = 25.4 mm
   => 
   1 mm = 1 / 25.4 pulgadas
   =>
   1 m = 1000 * (1 / 25.4) pulgadas
   */
   
   const double PULGADAS_POR_METRO  = 1000 / 25.4 ;   // Podemos poner directamente una expresi�n
   const double PIES_POR_METRO      = 100  / 30.48 ;
   const double YARDAS_POR_METRO    = 1    / 0.9144 ;
   const double MILLAS_POR_METRO    = 1    / 1609.344 ;
   double metros, pulgadas, pies, yardas, millas;
   
   cout << "Conversi�n sistema m�trico\n\n"
        << "Introduzca n�mero de metros: ";
   cin >> metros;

   pulgadas = PULGADAS_POR_METRO * metros;
   pies     = PIES_POR_METRO * metros;
   yardas   = YARDAS_POR_METRO * metros;
   millas   = MILLAS_POR_METRO * metros;
   
   cout << "\n\nPulgadas:\t" << pulgadas
        << "\nPies:\t\t"     << pies
        << "\nYardas:\t\t"   << yardas
        << "\nMillas:\t\t"   << millas
        << "\n\n";
}
 
