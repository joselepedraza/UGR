#include "cronologia.h"


/**
 * @file
 * @brief Implementacion de la clase cronologia
 *
 */


/*********************** Constructores ***********************/
cronologia::cronologia(){}

cronologia::cronologia(const map<int,fechahistorica> &m){
	this->fechas=m;
}


cronologia::cronologia(const cronologia &f){
	fechas=f.getFechas();
}

/*********************** Metodos Get - Set ************************/
void cronologia::setFechas(map<int,fechahistorica> &m){
	this->fechas=m;
}

map<int,fechahistorica> cronologia::getFechas()const{
	return fechas;
}

/************************* Busquedas *******************************/
//Busqueda por anio especifico
fechahistorica cronologia::buscarEventosAnio(int anio){
	auto res=fechas.find(anio);
	fechahistorica fh(anio,"NO ENCONTRADO");

	if(res != fechas.end())
		return (res->second);
	return fh;
}

//Busqueda por rango de anios
cronologia cronologia::buscarEventosRangoAnios(int ini,int fin){
	cronologia cr;
	map<int,fechahistorica> rango;
	rango.insert(fechas.lower_bound(ini),fechas.upper_bound(fin));
	cr.setFechas(rango);
	return cr;
}

//Busqueda por keyword
cronologia cronologia::buscarEventosPalabra(string pal){
	cronologia cr;

	for(auto it=fechas.begin();it!= fechas.end();++it){
		if((it->second).buscarAcontecimiento(pal)){
			cr.insertar((it->second));
		}
	}

	return cr;
}


/*********************** Operadores ***********************/
//op. suma
cronologia cronologia::operator+(const cronologia& c)const{
	cronologia caux(c.getFechas());

	for(auto it=fechas.begin();it != fechas.end();it++){
		caux.insertar((it->second));
	}

	return caux;
}

//op. asignacion
cronologia& cronologia::operator=(const cronologia& c){
	if(this != &c){
		fechas=c.getFechas();
	}
	return *this;
}

//op.comp.
bool cronologia::operator==(const cronologia& e) const{
	return (fechas == e.getFechas());
}

//op. distinto
bool cronologia::operator!=(const cronologia& e) const{
	return !(fechas == e.getFechas());
}

fechahistorica crearFecha(string cadena){
	set<string> aux1;
	vector<string> result;
	result=explode(cadena,'#');
	for(int i=1;i<result.size();i++){
		aux1.insert(result[i]);
	}

	fechahistorica fh = fechahistorica(stoi(result[0]),aux1);//stoi -> string a entero
	return fh;
}

//ops. flujo
ifstream& operator>> (ifstream& ifs, cronologia& r){
	fechahistorica fh;
	string cadena;

	assert (!ifs.fail());//Si por alguna razon falla el flujo del fichero abortamos el programa, ya que no podriamos hacer absolutamente nada.
	getline(ifs,cadena,'\n');
	while(!ifs.eof()){
		if (!cadena.empty() && cadena[cadena.size() - 1] == '\r'){
            cadena.erase(cadena.size() - 1);
            //cerr<<"\tLa cadena leida termina con \\r, elimino este caracter y me queda la cadena: "<<cadena<<endl;
        }
		fechahistorica fh = crearFecha(cadena);
		r.insertar(fh);
		getline(ifs,cadena,'\n');
	}

	if(!cadena.empty() && ifs.eof()){
		fechahistorica fh = crearFecha(cadena);
		r.insertar(fh);
	}

	ifs.close();
	return ifs;
}


ostream& operator<<(ostream& os, const cronologia& e){
	os <<e.toString();
	return os;
}


/************************ Utilidades ***********************/

//Borrar fechas
void cronologia::clear(){
	fechas.clear();
}

//Insertar fechas
void cronologia::insertar(const fechahistorica & fh){
	//Comprobamos el invariante de la fecha y que no esta en el conjunto
	auto it=fechas.find(fh.getAnio());
	if (fh.comp_invariante() &&  (it == fechas.end())){
		fechas.insert(make_pair(fh.getAnio(),fh));
	}else{
		(it->second).aniadirAcontecimientos(fh.getAcontecimientos());
	}
}

//Eliminar fecha
void cronologia::eliminar(const fechahistorica &fh){
	//Con find obtenemos el iterador donde se encuentra el elemento buscado, con erase eliminamos donde apunte el it.
	fechas.erase(fh.getAnio());
}

//toString
string cronologia::toString()const{
	string aux=concatenarFechas();
	//return "Cronologia:\n"+aux;
	return aux;
}

int cronologia::size(){
	return fechas.size();
}

//Recorrer fechas y crear cadena con ellas
string cronologia::concatenarFechas()const{
	string aux=" ";
	for(auto it=fechas.begin();it!=fechas.end();++it){
		aux+=((*it).second).toString();
		aux+="\n";
	}
	aux.erase(aux.begin());//borramos el espacio en blanco
	return aux;
}

//Cortar cadena
vector<string> explode(const string& s, char delim){
	vector<string> result;
	istringstream iss(s);  //construye para poder usar getline con un string (como si fuera un fichero)
	string token = "";
	while(getline(iss, token, delim)){
		result.push_back(move(token));
	}
	return result;
}

/********************** Iteradores begin - end ************************/
cronologia::iterator cronologia::begin(){
	map<int,fechahistorica>::iterator it=fechas.begin();
	return it;
}

cronologia::iterator cronologia::end(){
	map<int,fechahistorica>::iterator it=fechas.end();
	return it;
}

cronologia::const_iterator cronologia::begin() const{
	map<int,fechahistorica>::const_iterator it=fechas.cbegin();
	return it;
}

cronologia::const_iterator cronologia::end() const{
	map<int,fechahistorica>::const_iterator it=fechas.cend();
	return it;
}
