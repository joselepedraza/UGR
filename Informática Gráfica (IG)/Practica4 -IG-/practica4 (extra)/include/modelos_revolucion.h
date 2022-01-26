#include <vector>
#include "vertex.h"

#include "triangulos3D.h"

#include "../include/file_ply_stl.hpp"
#include "../include/modelos_basicos.h"

//typedef enum{PIRAMIDE, CUBO, CUBO_0, DIAMANTE, OBJETO_PLY, ESFERA, CONO, CILINDRO, PERFIL_PLY, TANQUE, FLEXO} _tipo_objeto;
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
              void  parametros(vector<_vertex3f> perfil1, int num1, int tipo, int giro, int tapa);   //tipo indica si el objeto es generico/cilindro(0), cono(1), esfera(2)
              
              void cambiar_giro(_tipo_objeto t_objeto, _tipo_giro t_giro); //giro indica en que eje gira 
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
              _cono();
              _cono(float radio, float altura, int m, _tipo_giro t_giro);      
};

class _esfera: public _rotacion{
       public:
              _esfera();
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


//************************************************************************
// Objeto articulado: Tanque
//************************************************************************

class _chasis: public _triangulos3D
{
       public:
              _chasis();
              void draw(_modo modo,_material material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

              float altura;

       protected:
              _rotacion  rodamiento;
              _cuboc  base;
};

//************************************************************************

class _torreta: public _triangulos3D
{
       public:
              _torreta();
              void 	draw(_modo modo, _material material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

              float altura;
              float anchura;

       protected:
              _cuboc  base;
              _piramide parte_trasera;
};

//************************************************************************

class _tubo: public _triangulos3D
{
       public:
              _tubo();
              void 	draw(_modo modo,_material material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

       protected:
              _rotacion tubo_abierto; // caña del cañón
};

//************************************************************************

class _tanque: public _triangulos3D
{
       public:
              _tanque();
              void 	draw(_modo modo,_material material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

              float giro_tubo;
              float giro_torreta;

              float giro_tubo_min;
              float giro_tubo_max;

       protected:
              _chasis  chasis;
              _torreta  torreta;
              _tubo     tubo;
};



//************************************************************************
// Objeto articulado: Flexo
//************************************************************************

class _base: public _triangulos3D
{
       public:
              _base();
              void draw(_modo modo, _material material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

              float altura;

       protected:
              _rotacion pie;
              _rotacion soporte;
};

class _brazo1: public _triangulos3D
{
       public:
              _brazo1();
              void draw(_modo modo, _material material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

              float altura;

       protected:
              _rotacion tubo_cerrado;
              _rotacion tubo_cerrado1; 
};


class _brazo2: public _triangulos3D
{
       public:
              _brazo2();
              void draw(_modo modo, _material material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

              float altura;

       protected:
              _rotacion tubo_cerrado;
              
};

class _cabeza: public _triangulos3D
{
       public:
              _cabeza();
              void draw(_modo modo, _material material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
              
              float altura;
       protected:
              _rotacion tubo_gordo;
              _cono cono;
              _esfera bombilla;

};

//************************************************************************

class _flexo: public _triangulos3D
{
       public:
              _flexo();
              void draw(_modo modo, _material material, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

              float giroY_brazo1;
              float animacion_brazo1_Y = 1.0;//0.1;
              float velocidad_brazo1_Y = 1.0;//0.1;
              
              float giroZ_brazo1;
              float giroZ_brazo1_min;
              float giroZ_brazo1_max;
              float animacion_brazo1_Z = 1.0;//0.01;
              float velocidad_brazo1_Z = 1.0;//0.01;

              float giroZ_brazo2;
              float giroZ_brazo2_min;
              float giroZ_brazo2_max;
              float animacion_brazo2_Z = 1.0;//0.01;
              float velocidad_brazo2_Z = 1.0;//0.01;

              float giroX_cabeza;
              float giroX_cabeza_max;
              float giroX_cabeza_min;
              float animacion_cabeza_X = 1.0;//0.005;
              float velocidad_cabeza_X = 1.0;//0.005;

       protected:
              _base base;
              _brazo1 brazo1;
              _brazo2 brazo2; 
              _cabeza cabeza;
};





