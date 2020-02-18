/*
Una liga de fútbol desea procesar los resultados de los equipos que la componen. 
Para ello, se debe implementar un programa que lea primero un "código" de equipo (un valor entero de 5 digitos) y posteriormente la cantidad de partidos ganados, empatados y perdidos (como valores enteros positivos). 
Se sabe que existen 10 equipos. Para cada uno de ellos se debe mostrar la cantidad de puntos obtenidos, 
sabiendo que se otorgan 3 puntos por partido ganado, 1 por partido empatado y 0 (cero) por perdido. 
Al final del procesamiento, el programa debe informar el código del equipo campeón (el equipo con más puntos) y el código del equipo que desciende (aquel con menos puntos).

Todas las lecturas de datos deben estar convenientemente filtradas (idealmente usando funciones).
*/

#include <iostream>
#include <string>

using namespace std;

int LeerNroPartidos(string msg)
{ int valor;
	do
	 {cout << "Ingrese cantidad de partidos " << msg;	
	  cin >> valor;
	}while((valor < 0));

 return valor;
}



int LeerEquipo()
{ int valor;
	do
	 {cout << "Ingrese codigo de equipo (10000-99999)";	
	  cin >> valor;
	}while((valor < 10000) || (valor > 99999));

 return valor;
}




int main()
{int gano, perdio, empato, equipo, puntos, codigo;
 int equipo_campeon, equipo_desciende;


int pts_campeon = 0;
int pts_desciende = 30 ; //un equipo como maximo gana 9 partidos
// para cada equipo
for(int e=1; e <= 10; e++)
	{codigo = LeerEquipo();
    gano = LeerNroPartidos("ganados: ");
    empato = LeerNroPartidos("empatados: ");
    perdio = LeerNroPartidos("perdidos: ");

 	puntos = 3 * gano + 1 * empato;
	cout << "\n El equipo " << codigo << " tuvo " << puntos << " puntos." << endl;
	if (puntos > pts_campeon)
		{pts_campeon = puntos;
 	 	equipo_campeon = codigo;
		}

	if (puntos < pts_desciende)
		{pts_desciende = puntos;
	 	 equipo_desciende = codigo;
		}

 }

cout << "\nFinal del torneo. " << equipo_campeon << " ha sido campeon con " << pts_campeon << " puntos y el equipo " 
<< equipo_desciende << " ha descendido con " << pts_desciende << " puntos." <<  endl;


}
