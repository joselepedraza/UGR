
#include "../include/triangulos.h"


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
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
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
	int i;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
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
	int i;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		if (i %2 == 0) glColor3f(r1, g1, b1);
		else glColor3f(r2, g2, b2);
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
}
//Modo ajedrez multicolor
void _triangulos3D::draw_ajedrezZ() {
/*	int i;
	vector<float> rgb[3];
	int tam = caras.size();
	vector<int, vector<float>> colores[tam,rgb];	//vector que almacenara el vector del color(r0g1b2) correspondiente
	float r,g,b;
    glPolygonMode(GL_FRONT,GL_FILL);
	srand48(time(NULL));
	for(int i=0;i< caras.size();i++){
		for(int j=0; j<3; j++){
			colores[i][j] = drand48();
		}
	}
	

    glBegin(GL_TRIANGLES);
    for(i=0;i<caras.size();i++){
		glColor3f(colores[i][0], colores[i][1], colores[i][2]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);	
    }
    glEnd();*/
}


//Modo ajedrez multicolor con parpadeo intermitente asincrono
void _triangulos3D::draw_parpadeo_ajedrez() {
	int i;
	float r,g,b;
    glPolygonMode(GL_FRONT,GL_FILL);

	srand48(time(NULL)); 	//para parpadeo asincrono

    glBegin(GL_TRIANGLES);
    for(i=0;i<caras.size();i++){
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


