
#include "../include/modelos_revolucion.h"
#include "../include/modelo_ply.h"

//************************************************************************
// Clase objeto por revolucion
//************************************************************************
_rotacion::_rotacion()
{
}

//**************************************************************************************
//Getters & setters
//**************************************************************************************
float _rotacion::get_radio(){
  return r;
}
float _rotacion::get_altura(){
  return alt;
}
int _rotacion::get_n_lados(){
  return m;
}
void _rotacion::set_n_lados(int numl){
  m=numl;
}
void _rotacion::set_radio(float radio){
  r=radio;
}
void _rotacion::set_altura(float altura){
  alt=altura;
}

//*************************************************************************
////Constructor Esfera: crea el perfil
//*************************************************************************
_esfera:: _esfera(float radio, int n, int m){ //tam radio, n puntos del perfil(latitud-paralelos), m lados de la esfera(longitud-meridianos)
  
  vector<_vertex3f> perfil1;
  _vertex3f aux;
  int i;
  
  for (i=1; i<n; i++){
    aux.x= radio*cos(M_PI*i/n-M_PI/2.0);
    aux.y= radio*sin(M_PI*i/n-M_PI/2.0);
    aux.z= 0.0;
    perfil1.push_back(aux);
  }

  parametros(perfil1,m,2,2);  //tipo 2 esfera (giro en Y)
}

//*************************************************************************
//Constructor de Cono
//*************************************************************************
_cono:: _cono(float radio, float altura, int m, _tipo_giro t_giro){ 
  set_radio(radio);
  set_altura(altura);
  set_n_lados(m);

  cambiar_giro(CONO,t_giro); //genera el perfil segun el giro
}

//*************************************************************************
//Constructor de Cilindro
//*************************************************************************
_cilindro:: _cilindro(float radio, float altura, int m, _tipo_giro t_giro){ 
  set_radio(radio);
  set_altura(altura);
  set_n_lados(m);

  cambiar_giro(CILINDRO,t_giro); //genera el perfil segun el giro
}


//*************************************************************************
// Constructor Perfil ply
//*************************************************************************
_perfil_PLY::_perfil_PLY(int m){
  pasos = m;  //numero de lados (o precisión al girar)
}

//**************************************************************************************
//Funcion para leer perfil de un archivo PLY y generar figura
//**************************************************************************************
void _perfil_PLY::leer_perfil(char *archivo){
  int n_ver;

  vector<_vertex3f> perfil;

  vector<float> ver_ply ;
 
  _file_ply::read_perfil(archivo, ver_ply);

  n_ver=ver_ply.size()/3;

  printf("Number of vertices=%d\n", n_ver);

  perfil.resize(n_ver);

  int j = 0;
  for (unsigned int i = 0; i < ver_ply.size(); i+=3){
    perfil[j].x = ver_ply[i];
    perfil[j].y = ver_ply[i+1];
    perfil[j].z = ver_ply[i+2];

    j++;
  }

  parametros(perfil,pasos,0,2); //tipo generico (giro en y)

}

//**************************************************************************************
//Genera el perfil según el tipo de giro
//**************************************************************************************
void _rotacion::cambiar_giro(_tipo_objeto t_objeto, _tipo_giro t_giro){
  
	vector<_vertex3f> perfil2;
	_vertex3f aux;

  //perfiles para diferentes ejes de rotación
  if(t_giro==GIRO_X){//generamos para girar en X
    if(t_objeto==CILINDRO){
      aux.x=-get_altura()/2.0; aux.y=get_radio(); aux.z=0.0;
      perfil2.push_back(aux);
      aux.x=get_altura()/2.0; aux.y=get_radio(); aux.z=0.0;
      perfil2.push_back(aux);

      parametros(perfil2,get_n_lados(),0,1);
    }
    if(t_objeto==CONO){
      aux.x= 0.0; aux.y=get_radio(); aux.z=0.0;
      perfil2.push_back(aux);
      aux.x=get_altura(); aux.y=0.0; aux.z=0.0;
      perfil2.push_back(aux);

      parametros(perfil2,get_n_lados(),1,1);	
    }
  }
  else if(t_giro==GIRO_Y){//generamos para girar en Y
    if(t_objeto==CILINDRO){
		  aux.x=get_radio(); aux.y=-get_altura()/2.0; aux.z=0.0;
		  perfil2.push_back(aux);
		  aux.x=get_radio(); aux.y=get_altura()/2; aux.z=0.0;
		  perfil2.push_back(aux);	

		  parametros(perfil2,get_n_lados(),0,2);
    }
    if(t_objeto==CONO){
      aux.x= get_radio(); aux.y=0.0; aux.z=0.0;
      perfil2.push_back(aux);
      aux.x=0.0; aux.y=get_altura(); aux.z=0.0;
      perfil2.push_back(aux);

      parametros(perfil2,get_n_lados(),1,2);
    }
  }
  else{//generamos para girar en Z
    if(t_objeto==CILINDRO){
      aux.x=0.0; aux.y=get_radio(); aux.z=-get_altura()/2.0;
      perfil2.push_back(aux);
      aux.x=0.0; aux.y=get_radio(); aux.z=get_altura()/2.0;
      perfil2.push_back(aux);

      parametros(perfil2,get_n_lados(),0,3);
    }
    if(t_objeto==CONO){
      aux.x= get_radio(); aux.y=0.0; aux.z=0.0;
      perfil2.push_back(aux);
      aux.x=0.0; aux.y=0.0; aux.z=get_altura();
      perfil2.push_back(aux);

      parametros(perfil2,get_n_lados(),1,3);
    }
  }

}

//************************************************************************
// Calcula los vértices según en qué eje de giro generemos la figura
//************************************************************************
void _rotacion::puntos_giro_perfil_eje(vector<_vertex3f> perfil, int giro, int num, int num_aux){
  _vertex3f vertice_aux;

  if(giro==1){ //giro en x
    for (int j=0;j<num;j++){
      for (int i=0;i<num_aux;i++){
        vertice_aux.x=perfil[i].x;
        vertice_aux.y=perfil[i].y*cos(2.0*M_PI*j/(1.0*num))-
                      perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
        vertice_aux.z=perfil[i].y*sin(2.0*M_PI*j/(1.0*num))+
                      perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
        vertices[i+j*num_aux]=vertice_aux;
      }
    }

  }
  if(giro==2){ //giro en y
    for (int j=0;j<num;j++){
      for (int i=0;i<num_aux;i++){
        vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                      perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
        vertice_aux.y=perfil[i].y;
        vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                      perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
        vertices[i+j*num_aux]=vertice_aux;
      }
    }
  }
  if(giro==3){ //giro en z
    for (int j=0;j<num;j++){
      for (int i=0;i<num_aux;i++){
        vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))-
                      perfil[i].y*sin(2.0*M_PI*j/(1.0*num));
        vertice_aux.y=perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                      perfil[i].y*cos(2.0*M_PI*j/(1.0*num));
        vertice_aux.z=perfil[i].z;
        vertices[i+j*num_aux]=vertice_aux;
      }
    }
  }
}

//**************************************************************************************
//Genera la figura a partir del perfil y el eje de giro
//**************************************************************************************
void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo, int giro)
{
  
  int num_aux;

  float radio= 1.0;
  if(tipo==2){//si es una esfera, calculamos el radio
    radio = sqrt(perfil[0].x*perfil[0].x+perfil[0].y*perfil[0].y);
  }
  // TRATAMIENTO DE LOS VÉRTICES
  num_aux=perfil.size();

  float altura = 0.0;
  if(tipo==1){//si es un cono
    num_aux=1;
    altura = get_altura();
  }

  vertices.resize(num_aux*num+2); //n(puntos del perfil) *m(lados) +2(puntos para las tapas)

  //Calculamos los puntos de giro según el perfil y eje
  puntos_giro_perfil_eje(perfil, giro, num, num_aux);
  

  // TRATAMIENTO DE LAS CARAS
  caras.resize((num_aux-1)*2*num+2*num);
  int c=0;
  //si es un objeto generico o una esfera 
  if(tipo==0 || tipo==2) {  //entonces hacemos el tratamiento de caras (esto no se hace para el cono)
    //Para perfil con 2 o más puntos:
    for(int j=0; j<num; j++){ 
      for(int i=0; i < num_aux-1; i++){
        caras[c]._0= j*num_aux+i;
        caras[c]._1= j*num_aux+i+1;
        caras[c]._2= ((j+1)%num)*num_aux+i +1;
        c++;
       
        caras[c]._0= ((j+1)%num)*num_aux+i +1;
        caras[c]._1= ((j+1)%num)*num_aux+i;
        caras[c]._2= j*num_aux+i;
        c++;
      }
    }
  }

  // TAPA INFERIOR:
  if(giro == 1){  //si gira en eje X
    if (fabs(perfil[0].y)>0.0){
      vertices[num_aux*num].y=0.0;
      if(tipo==0){  //tipo generico (cilindro)
        vertices[num_aux*num].x = perfil[0].x;
      }
      if(tipo==1){  //tipo cono
        vertices[num_aux*num].x = 0.0;
      }
      vertices[num_aux*num].z=0.0;
    }
  }
  if(giro == 2){  //si gira en el eje Y
    if (fabs(perfil[0].x)>0.0){
      vertices[num_aux*num].x=0.0;
      if(tipo==0){  //tipo generico (cilindro)
        vertices[num_aux*num].y = perfil[0].y;
      }
      if(tipo==1){  //tipo cono
        vertices[num_aux*num].y = 0.0;
      }
      if(tipo==2){  //tipo esfera
        vertices[num_aux*num].y = -radio;
      }
      vertices[num_aux*num].z=0.0;
    }
  }
  if(giro == 3){  //si gira en el eje Z
    if (fabs(perfil[0].y)>0.0){
      vertices[num_aux*num].y=0.0;
      if(tipo==0){  //tipo generico (cilindro)
        vertices[num_aux*num].z = perfil[0].z;
      }
      if(tipo==1){  //tipo cono
        vertices[num_aux*num].x = 0.0;
      }
      vertices[num_aux*num].x=0.0;
    }
  }

  for(int j=0 ; j<num; j++){
    caras[c]._0 = num_aux*num;
    caras[c]._1 = j*num_aux;
    caras[c]._2 = ((j+1)%num)*num_aux;
    c++;
  }

  //TAPA SUPERIOR
  //si gira en X
  if(giro==1){
    if (fabs(perfil[num_aux-1].y)>0.0){
      vertices[num_aux*num+1].y = 0.0;
      if(tipo==0){  //tipo generico (cilindro)
        vertices[num_aux*num+1].x = perfil[num_aux-1].x;
      }
      if(tipo==1 ){  //tipo cono
        vertices[num_aux*num+1].x = altura;
      }
      vertices[num_aux*num+1].z = 0.0;
    }
  }
  //si gira en Y
  if(giro==2){
    if (fabs(perfil[num_aux-1].x)>0.0){   
      vertices[num_aux*num+1].x = 0.0;
      if(tipo==0){  //tipo generico (cilindro)
        vertices[num_aux*num+1].y = perfil[num_aux-1].y;
      }
      if(tipo==1 ){  //tipo cono o cilindro
        vertices[num_aux*num+1].y = altura;
      }
      if(tipo==2){  //tipo esfera
        vertices[num_aux*num+1].y = radio;
      }
      vertices[num_aux*num+1].z = 0.0;
    }
  }
  //si gira en Z
  if(giro==3){  
    if (fabs(perfil[num_aux-1].y)>0.0){
      vertices[num_aux*num+1].y = 0.0;
      if(tipo==0){  //tipo Generico (cilindro)
        vertices[num_aux*num+1].z = perfil[num_aux-1].z;
      }
    }
    if(tipo==1 ){//tipo Cono
      vertices[num_aux*num+1].y = 0.0;
      vertices[num_aux*num+1].z = altura;
    }
    vertices[num_aux*num+1].x = 0.0;    
  }

  if (tipo == 0 || tipo == 2){ //si es un cilindro o esfera
    for(int j=0; j<num; j++){
      caras[c]._0 = (num_aux - 1) + j * num_aux;
      caras[c]._1 = (vertices.size() - 1);
      caras[c]._2 = (num_aux - 1) + ((j + 1) % num) * num_aux;
      c++;
    }
  }

  if(tipo==1){  //si es un cono
    for(int j=0; j<num; j++){
      caras[c]._0 = num_aux*num+1; //para que no vaya una arista del cono al centro
      caras[c]._1 = j*num_aux;
      caras[c]._2 = ((j+1)%num)*num_aux;
      c++;
    }
  }  

  genera_colores();
}
