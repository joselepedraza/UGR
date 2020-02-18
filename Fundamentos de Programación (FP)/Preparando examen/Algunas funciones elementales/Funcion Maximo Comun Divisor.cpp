////////////////////////////////////////////////////////////////////////////
// Fundamentos de Programación
// ETS Informática y Telecomunicaciones
// Universidad de Granada
// Departamento de Ciencias de la Computación e Inteligencia Artificial
// Autor: Juan Carlos Cubero
////////////////////////////////////////////////////////////////////////////

// Calcular el MCD de dos enteros

#include <iostream>
using namespace std;


//int MCD(int primero, int segundo){
///*
//   Vamos dividiendo los dos enteros por todos los
//   enteros menores que el menor de ellos hasta que:
//   - ambos sean divisibles por el mismo valor
//   - o hasta que lleguemos al 1
//*/
//   bool mcd_encontrado = false;
//   int divisor, mcd;
//
//   if (primero == 0 || segundo == 0)
//      mcd = 0;
//   else{
//      if (primero > segundo)
//         divisor = segundo;
//      else
//         divisor = primero;
//
//      mcd_encontrado = false;
//
//      while (!mcd_encontrado){
//         if (primero % divisor == 0 && segundo % divisor == 0)
//            mcd_encontrado = true;
//         else
//            divisor--;
//      }
//      mcd = divisor;
//   }
//
//   return mcd;
//}


// La siguiente versión usa la función Minimo:

int Minimo(int un_entero, int otro_entero){    
   if (un_entero < otro_entero)
      return un_entero;
   else
      return otro_entero;
}

int MCD(int primero, int segundo){
   bool mcd_encontrado = false;
   int divisor, mcd;

   if (primero == 0 || segundo == 0)
      mcd = 0;
   else{
      divisor = Minimo(primero, segundo);
      mcd_encontrado = false;

      while (!mcd_encontrado){
         if (primero % divisor == 0 && segundo % divisor == 0)
            mcd_encontrado = true;
         else
            divisor--;
      }
      mcd = divisor;
   }

   return mcd;
}


int main(){
   int un_entero, otro_entero, maximo_comun_divisor;

   cout << "Cómputo del MCD de dos enteros.\n\n";
   cout << "Introduzca dos enteros: ";
   cin >> un_entero;
   cin >> otro_entero;
   
   maximo_comun_divisor = MCD(un_entero, otro_entero);

   cout << "\nEl máximo común divisor de " << un_entero 
        << " y " << otro_entero << " es: " << maximo_comun_divisor;
}
