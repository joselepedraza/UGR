#ifndef MODELO_PLY_H
#define MODELO_PLY_H

#include "triangulos3D.h"

using namespace std;

//*************************************************************************
// clase objeto ply
//*************************************************************************
class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int parametros(char *archivo);

};


#endif