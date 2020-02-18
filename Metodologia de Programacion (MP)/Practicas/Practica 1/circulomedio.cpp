/* Programa que calcula un círculo con centro en medio de dos círculos y radio la mitad de la distancia.
   También calcula su área.

   Author: MP
   Módulo no definitivo (creado para ser modificado)

   Un ejemplo de ejecución es:
     Introduzca un circulo en formato radio-(x,y): 3-(0,0)
     Introduzca otro circulo: 4-(5,0)
     El círculo que pasa por los dos centros es: 2.5-(2.5,0)
	Su area es: 19.63
**/

#include <iostream>
#include <cmath>
using namespace std;

// Definición de las estructuras:
struct Punto {
    double x;
    double y;
};

struct Circulo {
    Punto centro;
    double radio;
};

// Prototipos de las funciones(o cabecera de las funciones):
void EscribirPunto(const Punto punto);
Punto LeerPunto();
double DistanciaPuntos(const Punto punto1, const Punto punto2);
Punto PuntoMedio(const Punto punto1, const Punto punto2);

void EscribirCirculo(const Circulo circulo);
Circulo LeerCirculo();
double AreaCirculo(const Circulo circulo);

// Programa principal:
int main()
{
    Circulo c1,c2, c3;

    do {
        cout << "Introduzca un circulo en formato radio-(x,y): ";
        c1 = LeerCirculo();

        cout << "Introduzca otro circulo: ";
        c2 = LeerCirculo();
    }while( DistanciaPuntos (c1.centro,c2.centro) == 0 );

    c3.centro = PuntoMedio( c1.centro, c2.centro );

    c3.radio = DistanciaPuntos( c1.centro, c2.centro ) / 2;

    cout << "El circulo que pasa por los dos centros es: ";
	EscribirCirculo( c3 );
    cout << endl << "Su area es: " << AreaCirculo( c3 ) << endl;
}

// Implementación de las funciones:
void EscribirPunto(const Punto punto){
    cout << "(";
	cout << punto.x;
	cout << ",";
	cout << punto.y;
	cout << ")";

}

Punto LeerPunto(){
	double x,y;
	char separador;

	cin >> separador >> x >> separador >> y >> separador;
}

double DistanciaPuntos(const Punto punto1, const Punto punto2){
	double distancia = sqrt(pow(punto2.x - punto1.x , 2) + pow(punto2.y - punto1.y , 2));
	return distancia;
}

Punto PuntoMedio(const Punto punto1, const Punto punto2){
	Punto punto_medio;
	punto_medio.x = (punto1.x + punto2.x)/2;
	punto_medio.y = (punto1.y + punto2.y)/2;
	
	return punto_medio;
}

void EscribirCirculo(const Circulo circulo){
	cout << circulo.radio;
	cout << "-";
	cout << "(";
	cout << circulo.centro.x;
	cout << ",";
	cout << circulo.centro.y;
	cout << ")";
}

Circulo LeerCirculo(){
	double radio, x, y;
	char separador;
	
	cin >> radio >> separador >> separador >> x >> separador >> y >> separador;
}

double AreaCirculo(const Circulo circulo){
	const double PI = 3.1415926536;
	double area = PI * (pow(circulo.radio, 2));
	return area;
	
}
/* Fin: circulomedio.cpp */


