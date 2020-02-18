/*
Se deben procesar las notas de examenes de 10 alumnos. 
Cada alumno se identifica por un codigo de alumno (un número de 3 cifras) y para cada uno de ellos se dispone 
de 5 notas. Cada nota es un valor entero en el rango [0..10].
Debe informar, para cada alumno, la media de sus notas utilizando un mensaje como el siguiente;
"El alumno xxx tiene una nota media de: yy.yy"

El programa debe informar, al final, el porcentaje de alumnos con más aprobados(notas mayores o iguales que 5) que suspensos.
Tanto la lectura del código de alumno y de las notas deben estar convenientemente filtradas.

*/
#include <iostream>
#include <string>

using namespace std;

int LeerNota()
{ int valor;
	do
	 {cout << "Ingrese una nota entre 1 y 10";	
	  cin >> valor;
	}while((valor < 0) || (valor > 10));

 return valor;
}


int Leer_ID_Alumno()
{ int valor;
	do
	 {cout << "Ingrese un codigo de alumno";	
	  cin >> valor;
	}while((valor < 100) || (valor > 999));

 return valor;
}

// las dos funciones previas se pueden unificar en una sola funcion
int LeerValor(int a, int b, string msg)
{ int valor;
	do
	 {cout << msg;	
	  cin >> valor;
	}while((valor < a) || (valor > b));

 return valor;
}





int main()
{int id_alumno, nota;
 int suma, contador_aprobados;
 int total_aprobados = 0;

// para cada alumno
for(int al=1; al <= 3; al++)
	{suma = 0;
	 contador_aprobados = 0;
    id_alumno = LeerValor(100, 999, "Codigo alumno: ");
    cout << endl;
   // leer 5 notas, sumarlas y contar cantidad de aprobados
   for(int n = 1; n <= 5; n++)
		{ nota = LeerValor(0,10," Nota: ");
	  	  suma = suma+ nota;
		  if (nota >= 5)
				contador_aprobados++;

		  cout << endl;
		}
	 // si tuvo mas aprobados que suspensos, contarlo
	 if (contador_aprobados >= 3)
		total_aprobados++;

	 cout << "\n Alumno:" << id_alumno << " nota media " << suma/5.0 << endl;
 }


cout << "\n El porcentaje de alumnos con mas aprobados que suspensos es " << total_aprobados * 10.0 << endl;

}
