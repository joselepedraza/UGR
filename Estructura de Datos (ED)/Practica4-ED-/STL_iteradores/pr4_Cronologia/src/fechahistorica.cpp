#include "fechahistorica.h"
/**
 * @file
 * @brief Implementacion de la clase fechahistorica
 *
 */

/*********************** Constructores ***********************/
//Const. por defecto
fechahistorica::fechahistorica(){
	set<string> aco;
	contenedor_fh=make_pair(0,aco);
}

//Const. por param 1
fechahistorica::fechahistorica(pair<int,set<string>> &fh){
	contenedor_fh.first=fh.first;
	contenedor_fh.second=fh.second;
}

//Const. por param 2
fechahistorica::fechahistorica(int an, set<string> s){
	contenedor_fh.first=an;
	contenedor_fh.second=s;
}

//Const. pr param 3
fechahistorica::fechahistorica(int an, string cad){
	contenedor_fh.first=an;
	(contenedor_fh.second).insert(cad);
}

//Const. por copia
fechahistorica::fechahistorica(const fechahistorica &fh){
	contenedor_fh.first=fh.getAnio();
	contenedor_fh.second=fh.getAcontecimientos();
}


/*********************** Metodos Get - Set ***********************/
int fechahistorica::getAnio()const{
	return (contenedor_fh.first);
}

set<string> fechahistorica::getAcontecimientos()const{
	return (contenedor_fh.second);
}

void fechahistorica::setAnio(int a){
	contenedor_fh.first=a;
}

void fechahistorica::setAcontecimientos(const set<string> &s){
	contenedor_fh.second=s;
}


/*********************** Busqueda de acontecimientos *******************/
bool fechahistorica::buscarAcontecimiento(string busqueda){
	string aux;
	int pos=0,n;
	
	vector<string> acontecimientos((contenedor_fh.second).begin(),(contenedor_fh.second).end());
	
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
		contenedor_fh.first=fh.getAnio();
		contenedor_fh.second=fh.getAcontecimientos();
	}
	return *this;
}

//Op. comp.
bool fechahistorica::operator==(const fechahistorica& e) const{
	return (contenedor_fh.first == e.getAnio() &&  contenedor_fh.second == e.getAcontecimientos());
}

//Op. distinto
bool fechahistorica::operator!=(const fechahistorica& e) const{
	return !(contenedor_fh.first == e.getAnio() &&  contenedor_fh.second == e.getAcontecimientos());
}

//Op. menor
bool fechahistorica::operator<(const fechahistorica& e) const{
	return (contenedor_fh.first < e.getAnio());
}

//Op. mayor
bool fechahistorica::operator>(const fechahistorica& e) const{
	return (contenedor_fh.first > e.getAnio());
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
   int n=contenedor_fh.first;
   while (n > 0) {
      n /= 10;
      cont++;
   }
	 //comprueba queal menos tenga 1 acontecimientos
   return(cont==4 && (contenedor_fh.second).size()>=1);
}

/************************* Utilidades *********************************/
//Borrar
void fechahistorica::clear(){
	contenedor_fh.first=0;
	(contenedor_fh.second).clear();
}

int fechahistorica::size(){
	return ((contenedor_fh.second).size());
}


//Aniadir acontecimientos
void fechahistorica::aniadirAcontecimiento(string str){
	(contenedor_fh.second).insert(str);
}

void fechahistorica::aniadirAcontecimientos(set<string> str){
	(contenedor_fh.second).insert(str.begin(),str.end());
}

//Quitar acontecimientos
void fechahistorica::eliminarAcontecimiento(string busqueda){
	(contenedor_fh.second).erase(busqueda);
}

//Recorrer acontecimientos y generar cadena de ellos
string fechahistorica::recorrerAcontecimientos()const{
	string aux;
	for(auto it=(contenedor_fh.second).begin(); it != (contenedor_fh.second).end(); ++it){
		aux+=(*it);
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
	string aux_anio=intToString(contenedor_fh.first);

	return (aux_anio+"#"+aux);
}


/********************** Iteradores begin - end ************************/
fechahistorica::iterator fechahistorica::begin(){
	set<string>::iterator it=(contenedor_fh.second).begin();
	return it;
}

fechahistorica::iterator fechahistorica::end(){
	set<string>::iterator it=(contenedor_fh.second).end();
	return it;
}

fechahistorica::const_iterator fechahistorica::begin() const{
	set<string>::const_iterator it=(contenedor_fh.second).cbegin();
	return it;
}

fechahistorica::const_iterator fechahistorica::end() const{
	set<string>::const_iterator it=(contenedor_fh.second).cend();
	return it;
}
