//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

using namespace std;

const float AXIS_SIZE=5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:


	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void  draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
//void cambiar_grosor(int i);
//void cambiar_rojo(float r);
//void cambiar_verde(float g);
//void cambiar_azul(float b);


vector<_vertex3i> caras;
//int grosor;
//float r,g,b;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=1);  //Constructor por defecto
};

//*************************************************************************
// clase cubo (centrado en los ejes)
//*************************************************************************

class _cuboc: public _triangulos3D
{
public:

	_cuboc(float tam=0.5);  //Constructor por defecto
};

//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75); //Constructor por defecto
};
