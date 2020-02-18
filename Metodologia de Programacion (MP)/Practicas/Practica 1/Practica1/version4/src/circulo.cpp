#include <circulo.h>
#include <iostream>
#include <cmath>
using namespace std;

void EscribirCirculo(const Circulo &p)
{
	cout << p.radio;
	EscribirPunto(p.centro);
}

Circulo LeerCirculo()
{
	Circulo c;
	float radio;
	cin >> c.radio;
	LeerPunto();
	return c;
}

double AreaCirculo(const Circulo &c)
{
	double area;
	const double PI = 3.1416;
	area = PI * pow(c.radio,2);
	return area;
}
