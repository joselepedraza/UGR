#include <vector>
#include "vertex.h"

#include "triangulos3D.h"

#include "../include/file_ply_stl.hpp"


typedef enum{PIRAMIDE, CUBO, CUBO_0, DIAMANTE, OBJETO_PLY, ESFERA, CONO, CILINDRO, PERFIL_PLY} _tipo_objeto;
typedef enum{GIRO_X, GIRO_Y, GIRO_Z} _tipo_giro;

//************************************************************************
// Objeto por revolución
//************************************************************************
class _rotacion: public _triangulos3D
{

private: 
       float r;      //radio
       float alt;    //altura
       int m;        //número de generaciones del perfil al girar
public:
       _rotacion();
       void  parametros(vector<_vertex3f> perfil1, int num1, int tipo, int giro);   //tipo indica si el objeto es generico(0), cono(1), esfera(2) o cilindro(3)
       
       void cambiar_giro(_tipo_objeto t_objeto, _tipo_giro t_giro);                                                                      //giro indica en que eje gira 
       void puntos_giro_perfil_eje(vector<_vertex3f> perfil, int giro, int num, int num_aux);
       float get_radio();
       float get_altura();
       int get_n_lados();
       void set_n_lados(int numl);
       void set_radio(float radio);
       void set_altura(float altura);
};

class _cono: public _rotacion{
public:
       _cono(float radio, float altura, int m, _tipo_giro t_giro);      
};

class _esfera: public _rotacion{
public:
       _esfera(float radio, int n, int m); //tam radio, n puntos del perfil, m lados de la esfera
};

class _cilindro: public _rotacion{
public:
       _cilindro(float radio, float altura, int m, _tipo_giro t_giro);       
};


//*************************************************************************
// Clase Perfil ply
//*************************************************************************
class _perfil_PLY: public _rotacion{

public:
   _perfil_PLY(int m);       //lee del ply y pasa el perfil construido
   int pasos;
   void leer_perfil(char *archivo);      //devuelve el perfil leido del archivo PLY
       
};
