#ifndef MODELOS_BASICOS_H
#define MODELOS_BASICOS_H

#include "triangulos3D.h"

using namespace std;

//*************************************************************************
// clase piramide
//*************************************************************************
class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75); //Constructor por defecto
};

//*************************************************************************
// clase cubo
//************************************************************************
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
// clase diamante
//*************************************************************************
class _diamante: public _triangulos3D
{
public:
	_diamante(float tam=0.5, float al = 1.0);  //Constructor por defecto
};

#endif