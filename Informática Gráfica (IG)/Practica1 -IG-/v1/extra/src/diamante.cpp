
#include "../include/diamante.h"

//*************************************************************************
// clase diamante (centrado en los ejes)
//*************************************************************************

_diamante::_diamante(float tam, float al)
{
//vertices
vertices.resize(6); 
	
	vertices[0].x = -tam;	vertices[0].y = 0;		vertices[0].z = tam;
	vertices[1].x = tam;	vertices[1].y = 0;		vertices[1].z = tam;
	vertices[2].x = tam;	vertices[2].y = 0;		vertices[2].z = -tam;
	vertices[3].x = -tam;	vertices[3].y = 0;		vertices[3].z = -tam;
	vertices[4].x = 0;		vertices[4].y = al;		vertices[4].z = 0;
	vertices[5].x = 0;		vertices[5].y = -al;	vertices[5].z = 0;

// triangulos (caras)
caras.resize(8);

	caras[0]._0 = 0;	caras[0]._1 = 1;	caras[0]._2 = 4;
	caras[1]._0 = 1;	caras[1]._1 = 2;	caras[1]._2 = 4;
	caras[2]._0 = 2;	caras[2]._1 = 3;	caras[2]._2 = 4;
	caras[3]._0 = 3;	caras[3]._1 = 0;	caras[3]._2 = 4;
	caras[4]._0 = 3;	caras[4]._1 = 0;	caras[4]._2 = 5;
	caras[5]._0 = 2;	caras[5]._1 = 3;	caras[5]._2 = 5;
	caras[6]._0 = 1;	caras[6]._1 = 2;	caras[6]._2 = 5;
	caras[7]._0 = 0;	caras[7]._1 = 1;	caras[7]._2 = 5;

}

