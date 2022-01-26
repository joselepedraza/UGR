
#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>

#include "../include/puntos3D.h"
#include "../include/triangulos3D.h"
#include "../include/modelos_basicos.h"
#include "../include/modelo_ply.h"
#include "../include/modelos_revolucion.h"

using namespace std;

_tipo_objeto t_objeto=PIRAMIDE;
_tipo_giro t_giro=GIRO_Y;
_modo modo=MULTICOLOR_CHESS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;

// objetos básicos
_cubo cubo;
_piramide piramide(0.85,1.3);
_cuboc cuboc;
_diamante diamante(1,0.5);

_objeto_ply  ply;	//bethoven.ply

/* Estándar de pruebas objetos revolución:
_esfera esfera(2.0,5,6);
_cono cono(2.0,2.0,8);
_cilindro cilindro(2.0,2.0,8);
_perfil_PLY perfilply(8);
*/

//Objetos con mayor precisión
_esfera esfera(2.0,50,60);
_cono cono(2.0,2.0,60,GIRO_Y);
_cilindro cilindro(1.0,2.0,60,GIRO_Y);
_perfil_PLY perfilply(80);	//peon.ply

//**************************************************************************************
//Función que comprueba si se ha actualizado el tipo de giro con alguna tecla
//**************************************************************************************
bool giro_cambiado(_tipo_giro giro_actual, _tipo_giro giro_anterior){
	if(giro_actual != giro_anterior){
		return true;
	}
	return false;
}


void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************
void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************
void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************
void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//**************************************************************************
void draw_objects()
{
	switch (t_objeto){
		case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,3);break;
		case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,3);break;
		case CUBO_0: cuboc.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,3);break;
		case DIAMANTE: diamante.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,3);break;
		case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,3);break;
		case ESFERA: esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,6);break;
		case CONO: cono.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,6);break;
		case CILINDRO: cilindro.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,6);break;
		case PERFIL_PLY: perfilply.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,6);break;
	}
}

//**************************************************************************
//
//***************************************************************************
void draw(void)
{

clean_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}


//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************
void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************
void normal_key(unsigned char Tecla1,int x,int y)
{	
	_tipo_giro t_giro_anterior = t_giro;
	switch (toupper(Tecla1)){
		case 'Q':exit(0);
		case 'P':modo=POINTS;break;
		case 'L':modo=EDGES;break;
		case 'S':modo=SOLID;break;
		case 'A':modo=SOLID_CHESS;break;
		case 'M':modo=MULTICOLOR_CHESS;break;
		case 'F':modo=MULTICOLOR_CHESS_FLASH;break;
		
		case '1':t_objeto=PIRAMIDE;break;
		case '2':t_objeto=CUBO;break;
		case '3':t_objeto=CUBO_0;break;
		case '4':t_objeto=DIAMANTE;break;
		case '5':t_objeto=OBJETO_PLY;break;	
		case '6':t_objeto=PERFIL_PLY;break;
		case '7':t_objeto=ESFERA;break;
		case '8':t_objeto=CONO;break;
		case '9':t_objeto=CILINDRO;break;
		
		case 'X':t_giro=GIRO_X;break;
		case 'Y':t_giro=GIRO_Y;break;
		case 'Z':t_giro=GIRO_Z;break;
	}

	if(giro_cambiado(t_giro, t_giro_anterior)){
		cilindro.cambiar_giro(CILINDRO,t_giro);
		cono.cambiar_giro(CONO,t_giro);
	}

	glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************
void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************
int main(int argc, char *argv[])
{

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA 1 y 2 EXTRAs");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

// funcion de inicialización
initialize();

// Creación del objeto leyendolo desde archivo ply
ply.parametros(argv[1]);

//Creación del objeto leyendo perfil desde archivo PLY
perfilply.leer_perfil(argv[2]);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
