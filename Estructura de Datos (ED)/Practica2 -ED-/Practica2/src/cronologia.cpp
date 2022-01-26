#include "cronologia.h"


/**
 * @file
 * @brief Implementacion de la clase cronologia
 *
 */


/*********************** Constructores ***********************/
cronologia::cronologia(){}

cronologia::cronologia(const vector<fechahistorica> &v){
	this->fechas=v;
}


cronologia::cronologia(const cronologia &f){
	fechas=f.getFechas();
}

/*********************** Metodos Get - Set ************************/
void cronologia::setFechas(vector<fechahistorica> &v){
	this->fechas=v;
}

vector<fechahistorica> cronologia::getFechas()const{
	return fechas;
}

/************************* Busquedas *******************************/
//Busqueda por anio especifico
fechahistorica cronologia::buscarEventosAnio(int anio){
	for(int i =0;i<fechas.size();i++){
		if(fechas[i].getAnio()==anio){
			//return fechas[i].toString();
			return fechas[i];
		}
	}
	
	fechahistorica fh(anio,"NO ENCONTRADO");
	
	return fh;
}

//Busqueda por rango de anios
cronologia cronologia::buscarEventosRangoAnios(int ini,int fin){
	cronologia cr;
	for(int i =0;i<fechas.size() && fechas[i].getAnio()<=fin;i++){
		if(fechas[i].getAnio()>= ini && fechas[i].getAnio()<=fin){
			cr.insertar(fechas[i]);
		}
	}
	return cr;
}

//Busqueda por keyword
cronologia cronologia::buscarEventosPalabra(string pal){
	cronologia cr;
	for(int i =0;i<fechas.size();i++){
		if(fechas[i].buscarAcontecimiento(pal)){
			cr.insertar(fechas[i]);
		}
	}
	return cr;
}


/*********************** Operadores ***********************/
//op. suma
cronologia cronologia::operator+(const cronologia& c)const{
	cronologia caux(c.getFechas());
	
	for(int i=0;i<fechas.size();i++){
		caux.insertar(fechas[i]);	
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
	if(fechas == e.getFechas())
		return true;
	else
		return false;
}

//op. distinto
bool cronologia::operator!=(const cronologia& e) const{
	if(fechas == e.getFechas())
		return false;
	else
		return true;
}

fechahistorica crearFecha(string cadena){
	vector<string> aux1,result;
	result=explode(cadena,'#');
	for(int i=1;i<result.size();i++){
		aux1.push_back(result[i]);
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
//Ordena las fechas de menor a mayor
/*void cronologia::ordenar(){
	std::sort(fechas.begin(),fechas.end());    //ordena usando la sobrecarga de operadores < >
}*/

//Borrar fechas
void cronologia::clear(){
	fechas.clear();
}

//Insertar fechas
void cronologia::insertar(const fechahistorica & fh){
	//Comprobamos el invariante de la fecha y que no esta en el conjunto
	if (fh.comp_invariante() && !std::binary_search (fechas.begin(),fechas.end(),fh)){
		fechas.insert(lower_bound(fh),fh);//Al aplicarle lower bound se van ordenando los elementos
	}else{
		auto it=std::find_if(fechas.begin(),fechas.end(),
		[fh](const fechahistorica & f) -> bool { return f.getAnio() == fh.getAnio(); });
		(*it).aniadirAcontecimientos(fh.getAcontecimientos());
	}
}

//Eliminar fecha
void cronologia::eliminar(const fechahistorica &fh){
	//Con find obtenemos el iterador donde se encuentra el elemento buscado, con erase eliminamos donde apunte el it.
	fechas.erase(std::find(fechas.begin(),fechas.end(),fh));
}

//toString
string cronologia::toString()const{
	string aux=concatenarFechas();
	return "Cronologia:\n"+aux;
}

int cronologia::size(){
	return fechas.size();
}

//Recorrer fechas y crear cadena con ellas
string cronologia::concatenarFechas()const{
	string aux=" ";

	for(int i=0;i<fechas.size();i++){
		aux+=fechas[i].toString();
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

//Lower_bound
/*Con este metodo conseguimos obtener la posicion+1 del ultimo elemento mas pequenio*/
cronologia::const_iterator cronologia::lower_bound (const fechahistorica& fh)const {
	const_iterator it= (std::lower_bound (fechas.begin(),fechas.end(),fh));
	return it;
}
