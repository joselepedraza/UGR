
#include "../include/triangulos3D.h"

//*************************************************************************
// _triangulos3D
//*************************************************************************
_triangulos3D::_triangulos3D()
{		
	calculadas_normales_caras=false;
	calculadas_normales_vertices=false;
	
}



//*************************************************************************
// Cambiar material objeto dibujado
//*************************************************************************
void _triangulos3D::cambiar_material(_material m){
	
	if(m==GOLD){
		ambiente=_vertex4f(0.24725,0.1995,0.0745,1.0);
		difusa=_vertex4f(0.75164,0.60648,0.22648,1.0);	
		especular=_vertex4f(0.628281,0.555802,0.366065,1.0);
		brillo=51.2;
	}
	if(m==POLISHED_GOLD){
		ambiente=_vertex4f(0.24725,0.2245,0.0745,1.0);
		difusa=_vertex4f(0.34615,0.3143,0.0903,1.0);	
		especular=_vertex4f(0.797357,0.723991,0.208006,1.0);
		brillo=83.2;
	}
	if(m==SILVER){
		ambiente=_vertex4f(0.19225,0.19225,0.19225,1.0);
		difusa=_vertex4f(0.50754,0.50754,0.50754,1.0);	
		especular=_vertex4f(0.508273,0.508273,0.508273,1.0);
		brillo=51.2;
	}
	if(m==CHROME){
		ambiente=_vertex4f(0.25,0.25,0.25,1.0);
		difusa=_vertex4f(0.4,0.4,0.4,1.0);	
		especular=_vertex4f(0.774597,0.774597,0.774597,1.0);
		brillo=76.8;
	}
	if(m==TURQUOISE){
		ambiente=_vertex4f(0.1,0.18725,0.1745,0.8);
		difusa=_vertex4f(0.396,0.74151,0.69102,0.8);	
		especular=_vertex4f(0.297254,0.30829,0.306678,0.8);
		brillo=12.8;
	}
	if(m==RUBY){
		ambiente=_vertex4f(0.1745,0.01175,0.01175,0.55);
		difusa=_vertex4f(0.61424,0.04136,0.04136,0.55);	
		especular=_vertex4f(0.727811,0.626959,0.626959,0.55);
		brillo=76.8;
	}

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
// dibujar en modo selección
//*************************************************************************
void _triangulos3D::draw_seleccion(float c)
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3ub(c,c,c);//lo tratamos como enteros
	glBegin(GL_TRIANGLES);
	for (unsigned int i=0;i<caras.size();i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
}

//*************************************************************************
// Cálculo de normales a las caras
//*************************************************************************
void _triangulos3D::calcular_normales_caras(){
	normales_caras.resize(caras.size());

	for(unsigned int i=0; i<caras.size();i++){
		//obtener dos vectores en el triángulo y calcular el producto vectorial
		_vertex3f 
			a1=vertices[caras[i]._1]-vertices[caras[i]._0],
			a2=vertices[caras[i]._2]-vertices[caras[i]._0],
			n=a1.cross_product(a2);	//producto vectorial definido en vertex.h
		//modulo
		float m=sqrt(n.x*n.x+n.y*n.y+n.z*n.z);
		//normalización
		normales_caras[i]= _vertex3f(n.x/m, n.y/m, n.z/m);
	}

	calculadas_normales_caras=true;
}

//*************************************************************************
// Dibujar en modo iluminación plana
//*************************************************************************
void _triangulos3D::draw_iluminacion_plana(_material m){
	
	if(calculadas_normales_caras==false){
		calcular_normales_caras();
	}
	glEnable(GL_LIGHTING);//activamos iluminación
		glShadeModel(GL_FLAT);//ponemos modo plano (smooth para suave)
	
		//activamos normalizacion por si transformamos objetos por escalado no tener que volver a calcular la normal a las caras 
		glEnable(GL_NORMALIZE);

		cambiar_material(m);

		//Definimos las constantes del material para Reflexión Especular (en vez de glColor cuando no se tiene iluminación)
		glMaterialfv(GL_FRONT,GL_AMBIENT,(GLfloat *) &ambiente);	//constante ambiental (=difusa)
		glMaterialfv(GL_FRONT, GL_DIFFUSE,(GLfloat *) &difusa);  //constante difusa
		glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat *) &especular);	//constante especular (mas difusa y ambiente)
		glMaterialf(GL_FRONT,GL_SHININESS,brillo);	//exponente del brillo

		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glBegin(GL_TRIANGLES);
		for (unsigned int i=0;i<caras.size();i++){
			//calcula angulo entre normal y punto fuente de luz para generar el color del triangulo
			glNormal3fv((GLfloat *) &normales_caras[i]); //la normal es la misma para los tres puntos de cada triangulo
			
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
			}
		glEnd();
	glDisable(GL_LIGHTING);
}

//*************************************************************************
// Cálculo de normales a los vertices
//*************************************************************************
void _triangulos3D::calcular_normales_vertices(){
	normales_vertices.resize(vertices.size());
	
	for(unsigned int i=0; i<vertices.size();i++){
		normales_vertices[i].x=0.0;
		normales_vertices[i].y=0.0;
		normales_vertices[i].z=0.0;
	}
	for(unsigned int i=0; i<caras.size();i++){
		normales_vertices[caras[i]._0]+=normales_caras[i];
		normales_vertices[caras[i]._1]+=normales_caras[i];
		normales_vertices[caras[i]._2]+=normales_caras[i];
	}
	//normalización activada en OpenGL

	calculadas_normales_vertices=true;
}

//*************************************************************************
// Dibujar en modo iluminación suave
//*************************************************************************
void _triangulos3D::draw_iluminacion_suave(_material m){
	
	if(calculadas_normales_caras==false){
		calcular_normales_caras();
	}
	if(calculadas_normales_vertices==false){
		calcular_normales_vertices();
	}

	glEnable(GL_LIGHTING);
		glShadeModel(GL_SMOOTH);
	
		glEnable(GL_NORMALIZE);

		cambiar_material(m);

		glMaterialfv(GL_FRONT,GL_AMBIENT,(GLfloat *) &ambiente);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,(GLfloat *) &difusa);
		glMaterialfv(GL_FRONT,GL_SPECULAR,(GLfloat *) &especular);	
		glMaterialf(GL_FRONT,GL_SHININESS,brillo);

		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glBegin(GL_TRIANGLES);
		
		for (unsigned int i=0;i<caras.size();i++){
			
			glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);

			glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);

			glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
			}
		glEnd();
	glDisable(GL_LIGHTING);
}

//*************************************************************************
// Dibujar con distintos modos
//*************************************************************************
void _triangulos3D::draw(_modo modo,_material m, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
	switch (modo){
		case POINTS:draw_puntos(r1, g1, b1, grosor);break;
		case EDGES:draw_aristas(r1, g1, b1, grosor);break;
		case SOLID:draw_solido(r1, g1, b1);break;
		case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
		case MULTICOLOR_CHESS:draw_ajedrez_multicolor();break;
		case MULTICOLOR_CHESS_FLASH:draw_parpadeo_ajedrez();break;
		case SOLID_ILLUMINATED_FLAT:
			if(m==GOLD){
				draw_iluminacion_plana(GOLD);
			}
			if(m==SILVER){
				draw_iluminacion_plana(SILVER);
			}
			if(m==POLISHED_GOLD){
				draw_iluminacion_plana(POLISHED_GOLD);
			}
			if(m==TURQUOISE){
				draw_iluminacion_plana(TURQUOISE);
			}
			if(m==CHROME){
				draw_iluminacion_plana(CHROME);
			}
			if(m==RUBY){
				draw_iluminacion_plana(RUBY);
			}
			break;
		
		case SOLID_ILLUMINATED_GOURAUD: 
			if(m==GOLD){
				draw_iluminacion_suave(GOLD);
			}
			if(m==SILVER){
				draw_iluminacion_suave(SILVER);
			}
			if(m==POLISHED_GOLD){
				draw_iluminacion_suave(POLISHED_GOLD);
			}
			if(m==TURQUOISE){
				draw_iluminacion_suave(TURQUOISE);
			}
			if(m==CHROME){
				draw_iluminacion_suave(CHROME);
			}
			if(m==RUBY){
				draw_iluminacion_suave(RUBY);
			}
			break;
		case SELECT:draw_seleccion(r1);break; 
		break;
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
