
#include "../include/modelo_ply.h"
#include "../include/file_ply_stl.hpp"
#include "../include/triangulos3D.h"

//*************************************************************************
// Clase Objeto ply
//*************************************************************************
_objeto_ply::_objeto_ply() 
{

}

int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int> car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);
caras.resize(n_car);

int j = 0;
for (unsigned int i = 0; i < ver_ply.size(); i+=3){
      vertices[j].x = ver_ply[i];
      vertices[j].y = ver_ply[i+1];
      vertices[j].z = ver_ply[i+2];

      j++;
}

int k = 0;
for (unsigned int i = 0; i < car_ply.size(); i+=3){
      caras[k]._0 = car_ply[i];
      caras[k]._1 = car_ply[i+1];
      caras[k]._2 = car_ply[i+2];

      k++;

}

genera_colores();
return(0);
}
