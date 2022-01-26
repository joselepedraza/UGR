
#include "../include/triangulos3D.h"

//*************************************************************************
// _triangulos3D
//*************************************************************************
_triangulos3D::_triangulos3D()
{

}

//*************************************************************************
// dibujar en modo arista
//*************************************************************************
void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glLineWidth(grosor);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for (unsigned int i=0;i<caras.size();i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************
void _triangulos3D::draw_solido(float r, float g, float b)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for (unsigned int i=0;i<caras.size();i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************
void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);
	for (unsigned int i=0;i<caras.size();i++){
		if (i %2 == 0) glColor3f(r1, g1, b1);
		else glColor3f(r2, g2, b2);
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
}

//*************************************************************************
// dibujar en modo ajedrez multicolor estatico
//*************************************************************************
void _triangulos3D::draw_ajedrez_multicolor() {

    glPolygonMode(GL_FRONT,GL_FILL);

    glBegin(GL_TRIANGLES);
    for(unsigned int i=0;i<caras.size();i++){	
		glColor3f(colores[i].r, colores[i].g, colores[i].b);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);	
    }
    glEnd();
}
//*************************************************************************
// dibujar en modo ajedrez multicolor con parpadeo intermitente asincrono
//*************************************************************************
void _triangulos3D::draw_parpadeo_ajedrez() {
	float r,g,b;
    glPolygonMode(GL_FRONT,GL_FILL);

	srand48(time(NULL)); 	//para parpadeo asincrono

    glBegin(GL_TRIANGLES);
    for(unsigned int i=0;i<caras.size();i++){
		r = drand48();
		g = drand48();
		b = drand48();
	
		glColor3f(r, g, b);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);	
    }
    glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************
void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case MULTICOLOR_CHESS:draw_ajedrez_multicolor();break;
	case MULTICOLOR_CHESS_FLASH:draw_parpadeo_ajedrez();break;
	}
}
//*************************************************************************
// Generar colores aleatorios
//*************************************************************************
void _triangulos3D::genera_colores() {
	
	colores.resize(caras.size());
	//srand48(time(NULL));
	for(unsigned int i=0;i<colores.size();i++){
		colores[i].r = drand48() * 1.0;
		colores[i].g = drand48() * 1.0;
		colores[i].b = drand48() * 1.0;
	}
}
