
#ifndef TRIANGULOS3D_H
#define TRIANGULOS3D_H

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

#include "puntos3D.h"


//*************************************************************************
// clase triángulo
//*************************************************************************

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID,SOLID_CHESS,MULTICOLOR_CHESS,MULTICOLOR_CHESS_FLASH, SOLID_ILLUMINATED_FLAT, SOLID_ILLUMINATED_GOURAUD} _modo;
typedef enum{PIRAMIDE, CUBO, CUBO_0, DIAMANTE, OBJETO_PLY, ESFERA, CONO, CILINDRO, PERFIL_PLY, TANQUE, FLEXO} _tipo_objeto;

typedef enum{SILVER, GOLD, POLISHED_GOLD,TURQUOISE, CHROME, RUBY} _material;

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();

void draw_aristas(float r, float g, float b, int grosor);
void draw_solido(float r, float g, float b);
void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void draw_ajedrez_multicolor();
void draw_parpadeo_ajedrez();

void draw_iluminacion_plana(_material m);
void draw_iluminacion_suave(_material m);

//Función para pintar en cualquier modo usando el enum (mcd de todos los parametros de las funciones draw)
void draw(_modo modo, _material m, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

void genera_colores();

void calcular_normales_caras(); //para iluminación plana
void calcular_normales_vertices();	//para iluminación suave

//Extra (cambiar material)
void cambiar_material( _material m);
void cambiar_especular(/*valor para la constante especular r,g,b,t*/);
void cambiar_ambiente_difuso(/*...*/);
void cambiar_brillo(/*...*/);

vector<_vertex3i> caras;
vector<_vertex3f> colores;

vector<_vertex3f> normales_caras;
vector<_vertex3f> normales_vertices;
bool calculadas_normales_caras;	//para controlar que solo hacemos el calculo de las normales una sola vez
bool calculadas_normales_vertices;

//Material para las caras 
_vertex4f ambiente;	//coeficientes ambiente y difuso (mismo material para ambiente y difuso)
_vertex4f difusa;
_vertex4f especular;		//coeficiente especular	(para brillo)
float brillo;				//exponente del brillo	(tamaño del brillo, exponente de Phone)
};

#endif
