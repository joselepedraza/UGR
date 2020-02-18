#include <punto.h>
#include <cmath>
#include <iostream>
using namespace std;

void EscribirPunto(const Punto &p){
	cout << "-(" << p.x << "," << p.y << ")";
}

Punto LeerPunto(){
	Punto p;
	char basura;
	cin >> basura >> basura >> p.x >> basura >> p.y >> basura;
	return p;
}

double DistanciaPuntos(const Punto &p1, const Punto &p2){
	double distancia;
	distancia = sqrt( (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) );
	return distancia;
}

Punto PuntoMedio(const Punto &p1, const Punto &p2){
	Punto m;
	m.x = (p1.x - p2.x);
	m.y = (p1.y - p2.y);
	return m;
}
