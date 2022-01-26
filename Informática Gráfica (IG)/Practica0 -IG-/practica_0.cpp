#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>



void Ejes (int width)
{   
    glLineWidth(width);
    glBegin(GL_LINES);
       glColor3f(1.0,0.0,0.0);
       glVertex3f(-1.0,0.0,0.0);
       glVertex3f(1.0,0.0,0.0);
       glColor3f(0.0,1.0,0.0);
       glVertex3f(0.0,-1.0,0.0);
       glColor3f(1.0,1.0,0.0);
       glVertex3f(0.0,1.0,0.0);   
    glEnd();
   
       
}


void Circle(GLfloat radio, GLfloat cx, GLfloat cy, GLint n, GLenum modo)
{
   int i;

   if (modo==GL_LINE)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   else if (modo==GL_FILL) 
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   else
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

   glBegin(GL_POLYGON);
      for(i=0;i<n;i++){
         glVertex2f( cx+radio*cos(2.0*M_PI*i/n), cy+radio*sin(2.0*M_PI*i/n));
      }
   glEnd();

}


//Construye poligonos pasandole vector con las coordenadas en 3d y numero de puntos
void Poligono_Solido(float v[][3], int n)
{
   int i;

   glPolygonMode(GL_FRONT,GL_FILL);

   glBegin(GL_POLYGON);
      for(i=0;i<n;i++){
         glVertex3f( v[i][0],v[i][1],v[i][2] );
      }
   glEnd();

}

void Poligono_Hueco(float v[][3], int n)
{
   int i;

   glPolygonMode(GL_FRONT,GL_LINE);

   glBegin(GL_POLYGON);
      for(i=0;i<n;i++){
         glVertex3f( v[i][0],v[i][1],v[i][2] );
      }
   glEnd();
   
}

void Monigote ()
{


 
// cara
   
   glColor3f(1.0,0.8,0.6); //rosita
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 

   glLineWidth(4);   //ancho de contorno
   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 
  
   //orejas
   glColor3f(1.0,0.8,0.6); //rosita
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
  
      glVertex3f(-0.26, 0.20, 0.0);
      glVertex3f(-0.2, 0.20, 0.0);
      glVertex3f(-0.2, 0.40, 0.0);
      glVertex3f(-0.26, 0.40, 0.0);

   glEnd();

   glColor3f(1.0,0.8,0.6); //rosita
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(0.2, 0.20, 0.0);
      glVertex3f(0.2, 0.40, 0.0);
      glVertex3f(0.26, 0.40, 0.0);
      glVertex3f(0.26, 0.20, 0.0);
   glEnd();

   //barba
   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.04, 0.0, 0.0);
      glVertex3f(0.04, 0.0, 0.0);
      glVertex3f(0.04, 0.12, 0.0);
      glVertex3f(-0.04, 0.12, 0.0);
   glEnd();  

   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_TRIANGLES);
      glVertex3f(-0.1, 0.0, 0.0);
      glVertex3f(0.1, 0.0, 0.0);
      glVertex3f(0.0, 0.1, 0.0);
   glEnd();

   //ojos
   glColor3f(0.5,0.7,1.0); //azulito
   Circle(0.05,0.1,0.35, 20, GL_FILL); //derecho
   Circle(0.05,-0.1,0.35, 20, GL_FILL); //izquierdo

   //nariz
   glColor3f(1.0,0.5,0.3); //rosita
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_TRIANGLES);
      glVertex3f(-0.06, 0.2, 0.0);
      glVertex3f(0.06, 0.2, 0.0);
      glVertex3f(0.0, 0.35, 0.0);
   glEnd();


   //boca 
   //opc1: (triangulos encadenados)
   glColor3f(1.0,0.0,0.0); //rojo
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_TRIANGLE_STRIP);
      glVertex3f(-0.15, 0.2, 0.0);
      glVertex3f(-0.1, 0.1, 0.0);
      glVertex3f(0.0, 0.15, 0.0);
      
      glVertex3f(0.1, 0.1, 0.0);
      glVertex3f(0.15, 0.2, 0.0);
   glEnd();

   //opc2:  (rectangulo con circulos en los extremos)
   glColor3f(1.0,0.0,0.0); //rojo
   Circle(0.03, 0.1, 0.15, 10, GL_FILL); //derecho
   Circle(0.03, -0.1, 0.15, 10, GL_FILL); //izquierdo

   float boca[4][3] = { {-0.1,0.12,0.0},{0.1,0.12,0.0},{0.1,0.18,0.0},{-0.1,0.18,0.0} };

   glColor3f(1.0,0.0,0.0); //rojo
   Poligono_Solido(boca,4);

// sombrero copa

   //rectangulo vertical
   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2, 0.55, 0.0);
      glVertex3f(0.2, 0.55, 0.0);
      glVertex3f(0.2, 0.90, 0.0);
      glVertex3f(-0.2, 0.90, 0.0);
   glEnd();    

   //cuadrado derecho e izquierdo
   glBegin(GL_POLYGON);
      glVertex3f(-0.2, 0.55, 0.0);
      glVertex3f(-0.2, 0.70, 0.0);
      glVertex3f(-0.30, 0.70, 0.0);
      glVertex3f(-0.30, 0.55, 0.0);
   glEnd();

   glBegin(GL_POLYGON);
      glVertex3f(0.2, 0.55, 0.0);
      glVertex3f(0.2, 0.70, 0.0);
      glVertex3f(0.30, 0.70, 0.0);
      glVertex3f(0.30, 0.55, 0.0);
   glEnd();

}



static void Init( )
{

   glShadeModel( GL_FLAT);
}


static void Reshape( int width, int height )
{
    glViewport(0, 0, (GLint)width, (GLint)height);
    glOrtho (-1.0, 1.0,-1.0, 1.0, -10, 10.0);
}

static void Display( )
{

  glClearColor(0.5,0.5,0.5,0.0);
  glClear( GL_COLOR_BUFFER_BIT );
   
  
   
   Ejes(6);
   Monigote();
   
   glFlush();
}


static void Keyboard(unsigned char key, int x, int y )
{
 
  if (key==27)
      exit(0);

}


int main( int argc, char **argv )
{
   glutInit(&argc,argv);
   glutInitDisplayMode( GLUT_RGB );

   glutInitWindowPosition( 20, 100 );
   glutInitWindowSize(500, 500 );
   glutCreateWindow("Practica 0 IG");


   Init();

   glutReshapeFunc(Reshape);
   glutDisplayFunc(Display);
   glutKeyboardFunc(Keyboard);
  
   glutMainLoop( );

   return 0;
}

