
#include "../include/cubo_centrado.h"

//*************************************************************************
// clase cuboc (centrado en los ejes)
//*************************************************************************

_cuboc::_cuboc(float tam)
{
//vertices
vertices.resize(8);
		//centrado
		//puntos para la cara inferior
	vertices[0].x=-tam;	vertices[0].y=-tam;	vertices[0].z=tam;
	vertices[1].x=tam;	vertices[1].y=-tam;	vertices[1].z=tam;
	vertices[2].x=tam;	vertices[2].y=-tam;	vertices[2].z=-tam;
	vertices[3].x=-tam;	vertices[3].y=-tam;	vertices[3].z=-tam;
		//puntos para la cara superior
	vertices[4].x=-tam;	vertices[4].y=tam;	vertices[4].z=tam;
	vertices[5].x=tam;	vertices[5].y=tam;	vertices[5].z=tam;
	vertices[6].x=tam;	vertices[6].y=tam;	vertices[6].z=-tam;
	vertices[7].x=-tam;	vertices[7].y=tam;	vertices[7].z=-tam;


// triangulos (caras)
caras.resize(12);
	caras[0]._0=0;	caras[0]._1=1;	caras[0]._2=4;
	caras[1]._0=1;	caras[1]._1=5;	caras[1]._2=4;
	caras[2]._0=1;	caras[2]._1=2;	caras[2]._2=5;
	caras[3]._0=2;	caras[3]._1=6;	caras[3]._2=5;
	caras[4]._0=2;	caras[4]._1=3;	caras[4]._2=6;
	caras[5]._0=3;	caras[5]._1=7;	caras[5]._2=6;
	caras[6]._0=3;	caras[6]._1=0;	caras[6]._2=7;
	caras[7]._0=0;	caras[7]._1=4;	caras[7]._2=7;
	caras[8]._0=4;	caras[8]._1=5;	caras[8]._2=6;
	caras[9]._0=4;	caras[9]._1=6;	caras[9]._2=7;
	caras[10]._0=3;	caras[10]._1=1;	caras[10]._2=0;
	caras[11]._0=3;	caras[11]._1=2;	caras[11]._2=1;

}

