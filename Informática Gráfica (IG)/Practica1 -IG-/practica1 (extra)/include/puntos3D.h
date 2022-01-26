
#ifndef PUNTOS3D_H
#define PUNTOS3D_H

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


using namespace std;

//const float AXIS_SIZE=5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:


	_puntos3D();
void draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};


#endif