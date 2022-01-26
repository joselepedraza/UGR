
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

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void draw_aristas(float r, float g, float b, int grosor);
void draw_solido(float r, float g, float b);
void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void draw_ajedrezZ();
void draw_parpadeo_ajedrez();
//void cambiar_grosor(int i);
//void cambiar_rojo(float r);
//void cambiar_verde(float g);
//void cambiar_azul(float b);
void genera_colores();


vector<_vertex3i> caras;
vector<_vertex3f> colores;
//int grosor;
//float r,g,b;
};

#endif
