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

	vector<fechahistorica> v = c.getFechas();

	//Comprobamos que no sean el mismo objeto y que no tengan los mismos datos en el vector
	if(this != &c && *this != c){    //comparamos a nivel de memoria y de contenido
		/*for(int i=0;i<v.size();i++){
			v.push_back(v[i]);
		}*/

		for(int i=0;i<this->fechas.size();i++){
			v.push_back(this->fechas[i]);
		}
		std::sort(v.begin(),v.end());//Como tenemos definido el operador menor "<" podemos ordenarlo con un criterio
		cronologia caux(v);

		return caux;
	}else{
		return c;
	}
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

//ops. flujo
ifstream& operator>> (ifstream& ifs, cronologia& r){
	fechahistorica fh;
    vector<string> result,aux1;
	string cadena;

	if (ifs.fail()){   //no necesario, comprobacion hecha en el main
		//Algo ...
	}else{
		/*do{
			getline(ifs,cadena,'\n');
		//}while (cadena.find("#") == 0 && !ifs.eof());
  }while (!ifs.eof());*/
    getline(ifs,cadena,'\n');
		while(!ifs.eof()){
			result=explode(cadena,'#');
			for(int i=1;i<result.size();i++){
				aux1.push_back(result[i]);
			}
			fechahistorica fh = fechahistorica(stoi(result[0]),aux1);    //stoi -> string a entero
			r.insertar(fh);
			aux1.clear();
			result.clear();
			getline(ifs,cadena,'\n');
		}
	}
	ifs.close();
	r.ordenar();
	return ifs;
}

ostream& operator<<(ostream& os, const cronologia& e){
	os << "Cronologia: "+e.toString();
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

//funcion comparacion
bool mifunctor(const fechahistorica &f1 ,const fechahistorica &f2){
	return (f1.getAnio()!=f2.getAnio());
	//Otra forma (expresion lambda):
	//\!std::binary_search (fechas.begin(), fechas.end(),fh,[] (const fechahistorica& f1, const fechahistorica& f2) {return (f1.getAnio()!=f2.getAnio()));
}

//Insertar fechas
void cronologia::insertar(const fechahistorica & fh){
	//Comprobamos el invariante de la fecha y si esta en el conjunto
	if (fh.comp_invariante() && !std::binary_search (fechas.begin(),fechas.end(),fh,mifunctor)){
		fechas.insert(lower_bound(fh),fh);//Al aplicarle lower bound se van ordenando los elementos
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
	return "Cronologia:\n "+aux;
}

//Recorrer fechas y crear cadena con ellas
string cronologia::concatenarFechas()const{
	string aux=" ";

	for(int i=0;i<fechas.size();i++){
		aux+=fechas[i].toString();
		aux+="\n";
	}
	//aux[(aux.size()-1)]="\n";//Sobreescribimos la ult. coma
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
