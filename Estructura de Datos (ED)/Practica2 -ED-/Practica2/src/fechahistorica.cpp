#include "fechahistorica.h"
/**
 * @file
 * @brief Implementacion de la clase fechahistorica
 *
 */

/*********************** Constructores ***********************/
//Const. por defecto
fechahistorica::fechahistorica(){
	anio=0;
}

//Const. por param
fechahistorica::fechahistorica(int anio, const vector<string> &acontecimientos){
	this->anio=anio;
	this->acontecimientos=acontecimientos;
}

//Const. por copia
fechahistorica::fechahistorica(const fechahistorica &fh){
	anio=fh.getAnio();
	acontecimientos=fh.getAcontecimientos();
}

//Const. solo un string
fechahistorica::fechahistorica(int an, string cad){
	anio=an;
	acontecimientos.push_back(cad);
}

/*********************** Metodos Get - Set ***********************/
int fechahistorica::getAnio()const{
	return anio;
}

vector<string> fechahistorica::getAcontecimientos()const{
	return acontecimientos;
}

void fechahistorica::setAnio(int a){
	this->anio=a;
}

void fechahistorica::setAcontecimientos(const vector<string> &v){
	this->acontecimientos=acontecimientos;
}


/*********************** Busqueda de acontecimientos *******************/
bool fechahistorica::buscarAcontecimiento(string busqueda){
	string aux;
	int pos=0,n;

	for(int i=0;i<acontecimientos.size();i++){
		n=acontecimientos[i].find(busqueda,pos);//pos Para empezar a buscar desde la ultima ocurrencia
		if(n != -1){
			aux+=acontecimientos[i];
			pos=n+1;//Le sumamos uno para que salte la ocurencia.
		}
	}
	return !(aux.empty());
}

/*********************** Operadores ***********************/
//Op. asignacion
fechahistorica& fechahistorica::operator=(const fechahistorica& fh){
	if(this != &fh){
		anio=fh.getAnio();
		acontecimientos=fh.getAcontecimientos();
	}
	return *this;
}

//Op. comp.
bool fechahistorica::operator==(const fechahistorica& e) const{
	if(anio == e.getAnio() &&  acontecimientos == e.getAcontecimientos())
		return true;
	else
		return false;
}

//Op. distinto
bool fechahistorica::operator!=(const fechahistorica& e) const{
	if(anio == e.getAnio() &&  acontecimientos == e.getAcontecimientos())
		return false;
	else
		return true;
}

//Op. menor
bool fechahistorica::operator<(const fechahistorica& e) const{
	return (anio < e.getAnio());
}

//Op. mayor
bool fechahistorica::operator>(const fechahistorica& e) const{
	return (anio > e.getAnio());
}

/*********************** Invariante de rep. **************************/
/*bool fechahistorica::comp_invariante(int n){
  //comprobar que tenga 4 cifras
   int cont = 0;
   while (n > 0) {
      n /= 10;
      cont++;
    }

   if(cont==4){
     return true;
   }
   return false;
}*/

bool fechahistorica::comp_invariante()const{
  //comprobar que tenga 4 cifras
   int cont = 0;
   int n=this->anio;
   while (n > 0) {
      n /= 10;
      cont++;
   }
	 //comprueba queal menos tenga 1 acontecimientos
   return(cont==4 && acontecimientos.size()>=1);
}

/************************* Utilidades *********************************/
//Borrar
void fechahistorica::clear(){
	anio=0;
	acontecimientos.clear();
}

int fechahistorica::size(){
	return (acontecimientos.size());
}


//Aniadir acontecimientos
void fechahistorica::aniadirAcontecimiento(string str){
	if(std::find(acontecimientos.begin(),acontecimientos.end(),str) == acontecimientos.end()){
			acontecimientos.push_back(str);
	}
}

void fechahistorica::aniadirAcontecimientos(vector<string> str){
	for(int i=0;i<str.size();i++){
		if(std::find(acontecimientos.begin(),acontecimientos.end(),str[i]) == acontecimientos.end()){
			acontecimientos.push_back(str[i]);
		}
	}
}

//Quitar acontecimientos
void fechahistorica::eliminarAcontecimiento(string busqueda){
	string aux;
	int pos=0,n;
	bool stop=false;

	for(int i=0;i<acontecimientos.size() && !stop;i++){
		n=acontecimientos[i].find(busqueda,pos);//pos Para empezar a buscar desde la ultima ocurrencia
		if(n != -1){
			acontecimientos.erase(acontecimientos.begin()+i);
			stop=true;
		}
	}
}

//Recorrer acontecimientos y generar cadena de ellos
string fechahistorica::recorrerAcontecimientos()const{
	string aux;

	for(int i=0;i<this->acontecimientos.size();i++){
		aux+=this->acontecimientos[i];
		aux+="#";
	}
	aux.erase(aux.end()-1);
	return aux;
}

string intToString(int n){
	stringstream ss;
	ss << n;
	string str = ss.str();
	return str;
}

//ToString
string fechahistorica::toString()const{
	string aux=recorrerAcontecimientos();
	string aux_anio=intToString(this->anio);

	return (aux_anio+"#"+aux);
}
