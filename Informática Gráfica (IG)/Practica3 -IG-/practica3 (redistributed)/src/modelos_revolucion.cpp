
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

  parametros(perfil1,m,2,2,1);  //tipo 2 esfera (giro en Y)
}

//*************************************************************************
////Constructor por defecto de Esfera: (usado para la bombilla)
//*************************************************************************
_esfera:: _esfera(){ //tam radio, n puntos del perfil(latitud-paralelos), m lados de la esfera(longitud-meridianos)
  
  vector<_vertex3f> perfil1;
  _vertex3f aux;
  int i;
  
  for (i=1; i<60; i++){
    aux.x= 1.0*cos(M_PI*i/60-M_PI/2.0);
    aux.y= 1.0*sin(M_PI*i/60-M_PI/2.0);
    aux.z= 0.0;
    perfil1.push_back(aux);
  }

  parametros(perfil1,60,2,2,1);  //tipo 2 esfera (giro en Y)
}

//*************************************************************************
//Constructor por defecto de Cono (usado para dibujar lampara)
//*************************************************************************
_cono:: _cono(){ 
  set_radio(1);
  set_altura(2);
  set_n_lados(50);

  cambiar_giro(CONO,GIRO_Y); //genera el perfil segun el giro
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

  parametros(perfil,pasos,0,2,1); //tipo generico (giro en y)

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

      parametros(perfil2,get_n_lados(),0,1,1);
    }
    if(t_objeto==CONO){
      aux.x= 0.0; aux.y=get_radio(); aux.z=0.0;
      perfil2.push_back(aux);
      aux.x=get_altura(); aux.y=0.0; aux.z=0.0;
      perfil2.push_back(aux);

      parametros(perfil2,get_n_lados(),1,1,1);	
    }
  }
  else if(t_giro==GIRO_Y){//generamos para girar en Y
    if(t_objeto==CILINDRO){
		  aux.x=get_radio(); aux.y=-get_altura()/2.0; aux.z=0.0;
		  perfil2.push_back(aux);
		  aux.x=get_radio(); aux.y=get_altura()/2; aux.z=0.0;
		  perfil2.push_back(aux);	

		  parametros(perfil2,get_n_lados(),0,2,1);
    }
    if(t_objeto==CONO){
      aux.x= get_radio(); aux.y=0.0; aux.z=0.0;
      perfil2.push_back(aux);
      aux.x=0.0; aux.y=get_altura(); aux.z=0.0;
      perfil2.push_back(aux);
      parametros(perfil2,get_n_lados(),1,2,1);
    }
  }
  else{//generamos para girar en Z
    if(t_objeto==CILINDRO){
      aux.x=0.0; aux.y=get_radio(); aux.z=-get_altura()/2.0;
      perfil2.push_back(aux);
      aux.x=0.0; aux.y=get_radio(); aux.z=get_altura()/2.0;
      perfil2.push_back(aux);

      parametros(perfil2,get_n_lados(),0,3,1);
    }
    if(t_objeto==CONO){
      aux.x= get_radio(); aux.y=0.0; aux.z=0.0;
      perfil2.push_back(aux);
      aux.x=0.0; aux.y=0.0; aux.z=get_altura();
      perfil2.push_back(aux);

      parametros(perfil2,get_n_lados(),1,3,1);
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
void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo, int giro, int tapa)
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

  // TAPA INFERIOR: && tapa==1
  if(giro == 1){  //si gira en eje X
    if (fabs(perfil[0].y)>0.0 && tapa==1){
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
    if (fabs(perfil[0].x)>0.0 && tapa==1){
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
    /*if (tipo==1 && tapa==0){//para dibujar lampara
      vertices[num_aux*num].y = altura;
    }*/
  }
  if(giro == 3){  //si gira en el eje Z
    if (fabs(perfil[0].y)>0.0 && tapa==1){
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
    if (fabs(perfil[num_aux-1].y)>0.0 && tapa==1){
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
    if (fabs(perfil[num_aux-1].x)>0.0 && tapa==1){   
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
    if (fabs(perfil[num_aux-1].y)>0.0 && tapa==1){
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


//************************************************************************
// Objeto articulado: Tanque
//************************************************************************

_chasis::_chasis()
{
  // perfil para un cilindro
  vector<_vertex3f> perfil;
  _vertex3f aux;

  aux.x=0.107;aux.y=-0.5;aux.z=0.0;
  perfil.push_back(aux);
  aux.x=0.107;aux.y=0.5;aux.z=0.0;
  perfil.push_back(aux);

  rodamiento.parametros(perfil,12,0,2,1);
  altura=0.22;
};

void _chasis::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
  glPushMatrix();
  glScalef(1.0,0.22,0.95);
  base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glRotatef(90.0,1,0,0);
  rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.25,0.0,0.0);
  glRotatef(90.0,1,0,0);
  rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.5,0.0,0.0);
  glRotatef(90.0,1,0,0);
  rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.25,0.0,0.0);
  glRotatef(90.0,1,0,0);
  rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.5,0.0,0.0);
  glRotatef(90.0,1,0,0);
  rodamiento.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}

//************************************************************************

_torreta::_torreta()
{
  altura=0.18;
  anchura=0.65;
};

void _torreta::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
  glPushMatrix();
  glScalef(0.65,0.18,0.6);
  base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.325,0,0);
  glRotatef(90.0,0,0,1);
  glScalef(0.18,0.16,0.6);
  parte_trasera.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}

//************************************************************************

_tubo::_tubo()
{
  // perfil para un cilindro
  vector<_vertex3f> perfil;
  _vertex3f aux;
  aux.x=0.04;aux.y=-0.4;aux.z=0.0;
  perfil.push_back(aux);
  aux.x=0.04;aux.y=0.4;aux.z=0.0;
  perfil.push_back(aux);
  tubo_abierto.parametros(perfil,12,0,2,0);
};

void _tubo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
  glPushMatrix();
  glTranslatef(0.4,0,0);
  glRotatef(90.0,0,0,1);
  tubo_abierto.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}

//************************************************************************

_tanque::_tanque()
{
  giro_tubo=2.0;
  giro_torreta=0.0;
  giro_tubo_min=-9;
  giro_tubo_max=20;
};

void _tanque::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
  glPushMatrix();
  chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor);

  glRotatef(giro_torreta,0,1,0);
  glPushMatrix();
  glTranslatef(0.0,(chasis.altura+torreta.altura)/2.0,0.0);
  torreta.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(torreta.anchura/2.0,(chasis.altura+torreta.altura)/2.0,0.0);
  glRotatef(giro_tubo,0,0,1);
  tubo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
  glPopMatrix();
};



//************************************************************************
// Objeto articulado: Flexo
//************************************************************************

_base::_base()
{
  // perfil para un cilindro
  vector<_vertex3f> perfil;
  _vertex3f aux;
  aux.x=0.6;aux.y=0.0;aux.z=0.0;
  perfil.push_back(aux);
  aux.x=0.5;aux.y=0.3;aux.z=0.0;
  perfil.push_back(aux);
  aux.x=0.3;aux.y=0.3;aux.z=0.0;
  perfil.push_back(aux);
  aux.x=0.2;aux.y=0.55;aux.z=0.0;
  perfil.push_back(aux);

  pie.parametros(perfil,12,0,2,1);
  altura=0.2; //la del scale (para brazo1)
};

void _base::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
  glPushMatrix();
  glScalef(1.2,0.5,1.0);
  pie.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

}

//************************************************************************

_brazo1::_brazo1()
{
  // perfil para un cilindro
  vector<_vertex3f> perfil;
  _vertex3f aux;
  aux.x=0.04;aux.y=0.0;aux.z=0.0;
  perfil.push_back(aux);
  aux.x=0.08;aux.y=2.0;aux.z=0.0;
  perfil.push_back(aux);
  tubo_cerrado.parametros(perfil,12,0,2,1);
  tubo_cerrado1.parametros(perfil,12,0,2,1);
  altura=2.0;
};

void _brazo1::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
  glPushMatrix();
  glTranslatef(0,0,-0.130);
  //glRotatef(45.0,0,0,1);
  tubo_cerrado.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0,0,0.130);
  //glRotatef(45.0,0,0,1);
  tubo_cerrado1.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}

//************************************************************************


_brazo2::_brazo2()
{
  // perfil para un cilindro
  vector<_vertex3f> perfil;
  _vertex3f aux;
  aux.x=0.12;aux.y=-0.65;aux.z=0.0;
  perfil.push_back(aux);
  aux.x=0.06;aux.y=-0.40;aux.z=0.0;
  perfil.push_back(aux);
  aux.x=0.03;aux.y=2.5;aux.z=0.0;
  perfil.push_back(aux);
  tubo_cerrado.parametros(perfil,12,0,2,1);
  altura=2.5;
};

void _brazo2::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
  glPushMatrix();
  //glScalef(1.0,2.0,1.0);
  glTranslatef(0,-0.5,0);
  glRotatef(-90.0,0,0,1); //45º en Z
  //glRotatef(180.0,0,1,0); //45º en Z
  tubo_cerrado.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}


//************************************************************************

_cabeza::_cabeza()
{
  // perfil para un cilindro (gordo)
  vector<_vertex3f> perfil;
  _vertex3f aux;
  aux.x=0.2;aux.y=1.0;aux.z=0.0;
  perfil.push_back(aux);
  aux.x=0.2;aux.y=1.5;aux.z=0.0;
  perfil.push_back(aux);
  tubo_gordo.parametros(perfil,12,0,2,1);
  altura=1.0;
  //perfil para un cono (creado por defecto en .h)
  //perfil para una esfera (creado por defecto en .h)

};

void _cabeza::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
  glPushMatrix();
  glTranslatef(-0.1,0.2,0.0);
  glPushMatrix();
  glTranslatef(2.7,-1.8,0);
  tubo_gordo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glTranslatef(0.0,0.4,0.0);
  glScalef(0.5,0.5,0.5);
  cono.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glScalef(0.5,0.5,0.5);
  bombilla.draw(SOLID, 0.8, 0.8, 0.8, r2, g2, b2, grosor);
  glPopMatrix();
  glPopMatrix();
  
}


//************************************************************************

_flexo::_flexo()
{
  //Giros para brazo1
  giroY_brazo1=0.0;
  
  giroZ_brazo1=-20.0;
  giroZ_brazo1_max=10;
  giroZ_brazo1_min=-30;

  //Giro para brazo2
  giroZ_brazo2=6.0;
  giroZ_brazo2_max=20;
  giroZ_brazo2_min=-20;

  //Giro para cabeza
  giroX_cabeza=0.0;
  giroX_cabeza_max=9.0;
  giroX_cabeza_min=-9.0;
};

void _flexo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
  glScalef(0.5,0.5,0.5);
  glPushMatrix();
    base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
   
    glTranslatef(0.0,base.altura,0.0);
    
    glRotatef(giroY_brazo1,0,1,0);
    glRotatef(giroZ_brazo1,0,0,1);
    glRotatef(45.0,0,0,1);
    brazo1.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    
    
      glTranslatef(0.0,base.altura+brazo1.altura,0.0);
      glRotatef(giroZ_brazo2,0,0,1);
      brazo2.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
      
      glRotatef(giroX_cabeza,1,0,0);
      cabeza.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

};
