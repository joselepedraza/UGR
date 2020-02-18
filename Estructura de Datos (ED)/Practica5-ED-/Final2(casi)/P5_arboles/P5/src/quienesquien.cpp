#include "../include/quienesquien.h"
#include <sstream>
#include <iostream>
#include <iterator>
#include <math.h>
#include <algorithm>

QuienEsQuien::QuienEsQuien(){
	//TODO :)
	jugada_actual=arbol.root();//Apuntamos al primer y unico nodo ; nulo en este caso.
}
QuienEsQuien::QuienEsQuien(const QuienEsQuien &quienEsQuien){
	//TODO :)
	this->personajes=quienEsQuien.personajes;
	this->atributos=quienEsQuien.atributos;
	this->tablero=quienEsQuien.tablero;
	this->arbol=quienEsQuien.arbol;
	this->jugada_actual=quienEsQuien.jugada_actual;
}
QuienEsQuien& QuienEsQuien::operator= (const QuienEsQuien &quienEsQuien){
	//TODO :)
	if(this != &quienEsQuien){
		this->personajes=quienEsQuien.personajes;
		this->atributos=quienEsQuien.atributos;
		this->tablero=quienEsQuien.tablero;
		this->arbol=quienEsQuien.arbol;
		this->jugada_actual=quienEsQuien.jugada_actual;
	}
	return *this;
}
QuienEsQuien::~QuienEsQuien(){
	this->limpiar();
}

void QuienEsQuien::limpiar(){
	//TODO :)
	this->personajes.clear();
	this->atributos.clear();
	this->tablero.clear();
	//this->jugada_actual.remove(); //(NO PONER ESTA LLAMADA) Explicacion: Esta llamada no debemos ponerla, ya que cuando hacemos
	//La llamada de abajo <this->arbol.clear()>, intenta borrar un nodo que ya esta borrado y dara core.
	this->arbol.clear();
}

bintree<Pregunta> QuienEsQuien::crear_arbol()
{

	//TODO :D:D
	//1. El primer atributo lo ponemos como raiz.
	Pregunta pr(atributos[0],personajes.size());
	bintree<Pregunta>aux(pr);
	arbol=aux;

	//2.insertamos los jugadores en las hojas correspondientes, siguiendo la descripcion del tablero
	bintree<Pregunta>::node n;
	bintree<Pregunta>::node n_anterior;
	int k,pos;

	for(int i=0;i<tablero.size();i++){
		n=arbol.root();
		pos=1;
		for(int j=0;j<tablero[i].size();j++){
			n_anterior=n;
			if(tablero[i][j]){
				if(n.left().null()){
					if(pos<atributos.size()){
						Pregunta pr(atributos[pos],personajes.size());
						arbol.insert_left(n,pr);
					}
				}
				n=n.left();
			}else{
				if(n.right().null()){
					if(pos<atributos.size()){
						Pregunta pr(atributos[pos],personajes.size());
						arbol.insert_right(n,pr);
					}
				}
				n=n.right();
			}
			k=j;
			pos++;
		}
		Pregunta pe(personajes[i],1);
		if(tablero[i][k]){//llegamos a la hoja
			arbol.insert_left(n_anterior,pe);//insertamos el personaje
		}else{
			arbol.insert_right(n_anterior,pe);
		}
	}

	//3.Contamos el numero de jugadores(hojas no nulas) y actualizamos cada nodo con el numero de hojas que contiene
	actualizar_numero_jugadores_activos(arbol.root());

	return arbol;
}

int QuienEsQuien::numero_hojas(bintree<Pregunta>::node n){
	if(n.null()){
		return 0;
	}
	if(n.left().null() && n.right().null()){
		return 1;
	}else{
		return numero_hojas(n.left())+numero_hojas(n.right());
	}
}

void QuienEsQuien::actualizar_numero_jugadores_activos(bintree<Pregunta>::node n){
	if(!n.null()){
		int soluciones=numero_hojas(n);
		if(esHoja(n) && esPersona(*n)){
			Pregunta p((*n).obtener_personaje(),soluciones);
			*n=p;
		}else if(esPregunta(*n)){

			Pregunta p((*n).obtener_pregunta(),soluciones);
			*n=p;
		}
		actualizar_numero_jugadores_activos(n.left());
		actualizar_numero_jugadores_activos(n.right());
	}
}

bool QuienEsQuien::esHoja(bintree<Pregunta>::node n){
  return (n.left().null() && n.right().null());
}


void QuienEsQuien::iniciar_juego(){
	//TODO :)

	cout<<"****************************"<<endl;
	cout<<"****** Quien es Quien ******"<<endl;
	cout<<"****************************"<<endl<<endl;

	cout<<"Autores:\n->Angel Barrilao Bensrhir\n->Jose Luis Predaza Roman\n->Jorge Garcia Moreno"<<endl<<endl;
	cout<<"==========================="<<endl;
	bool respuesta=true;
	/*vector<bool> v;
			v.push_back(1);
			v.push_back(0);
			v.push_back(1);
			aniade_personaje("Cristina",v);
			escribir_arbol_completo();
*/
	do{
		cout<<"COMIENZA EL JUEGO"<<endl;
		jugada_actual=arbol.root();

		do{
			cout<<*jugada_actual<<endl;
			cin>>respuesta;
			//~ preguntas_formuladas(jugada_actual);


			if(respuesta){
				jugada_actual=jugada_actual.left();
			}else{
				jugada_actual=jugada_actual.right();
			}


		}while(!esHoja(jugada_actual));

		cout<<"�Ya lo se! tu personaje es "<<*jugada_actual<<endl;
		cout<<"�Quieres jugar de nuevo?"<<endl;
		cin>>respuesta;
	}while(respuesta);

}

set<string> QuienEsQuien::informacion_jugada(bintree<Pregunta>::node jugada_actual){
	//TODO :)
	set<string> personajes_levantados;
	informacion_jugada(personajes_levantados,jugada_actual);
	return personajes_levantados;
}

void QuienEsQuien::informacion_jugada(set<string> &personajes_levantados,bintree<Pregunta>::node n){
	if(!n.null()){
		if(esHoja(n) && esPersona(*n)){
			personajes_levantados.insert((*n).obtener_personaje());
		}
		informacion_jugada(personajes_levantados,n.left());
		informacion_jugada(personajes_levantados,n.right());
	}
}

void QuienEsQuien::eliminar_nodos_redundantes(){
	eliminar_nodos_redundantes(arbol.root());
	actualizar_numero_jugadores_activos(arbol.root());
}

bool QuienEsQuien::tengoHijosNulos(bintree<Pregunta>::node n){
	return (n.left().null() || n.right().null());
}

void QuienEsQuien::eliminar_nodos_redundantes(bintree<Pregunta>::node n){
	if(!n.null()){
		if(ajuste_nodos_nulos(n)){
			eliminar_nodos_redundantes(arbol.root());
		}
		eliminar_nodos_redundantes(n.left());
		eliminar_nodos_redundantes(n.right());
	}
}

bool QuienEsQuien::ajuste_nodos_nulos(bintree<Pregunta>::node n){//Le indicamos una hoja, es decir un nodo solucion
	bintree<Pregunta> otroArbol;
	bool control=false;

	if(tengoHijosNulos(n)){
		if(n != arbol.root()){
			//Determino mi posicion con respecto a mi padre
			if(n.parent().left()==n){//Si soy de izq.
				if(!(n.left().null()) && n.right().null()){
					arbol.prune_left(n,otroArbol);
					arbol.insert_left(n.parent(),otroArbol);
					control=true;
				}else if(!(n.right().null()) && n.left().null()){
					arbol.prune_right(n,otroArbol);
					arbol.insert_left(n.parent(),otroArbol);
					control=true;
				}
			}else if(n.parent().right()==n){//Si soy de der.
				if(!(n.left().null()) && n.right().null()){
					arbol.prune_left(n,otroArbol);
					arbol.insert_right(n.parent(),otroArbol);
					control=true;
				}else if(!(n.right().null()) && n.left().null()){
					arbol.prune_right(n,otroArbol);
					arbol.insert_right(n.parent(),otroArbol);
					control=true;
				}
			}
		}else{
			//Determino mi posicion con respecto a mi padre
			if(!(n.left().null()) && n.right().null()){
				arbol.prune_left(n,otroArbol);
				arbol=otroArbol;
				control=true;
			}else if(!(n.right().null()) && n.left().null()){
				arbol.prune_right(n,otroArbol);
				arbol=otroArbol;
				control=true;
			}
		}
	}
	return control;
}


/*ostream & operator << (ostream & os, bintree<Pregunta> &arb)
{

cout << "Arbol_Pre:";

for (typename bintree<Pregunta>::preorder_iterator i = arb.begin_preorder(); i!=arb.end_preorder(); ++i)
  cout << *i << " ";

cout << endl;
}*/



bool  QuienEsQuien::esPregunta(bintree<Pregunta>::node n){
	if((*n).obtener_num_personajes()>1){
		return (find(atributos.begin(),atributos.end(),((*n).obtener_pregunta())) != atributos.end());
	}else{
		return (find(atributos.begin(),atributos.end(),((*n).obtener_personaje())) != atributos.end());
	}
}

bool QuienEsQuien::esPersona(Pregunta per){
	if(per.obtener_num_personajes()>1){
		return (find(personajes.begin(),personajes.end(),(per.obtener_pregunta())) != personajes.end());
	}else{
		return (find(personajes.begin(),personajes.end(),(per.obtener_personaje())) != personajes.end());
	}
}

float QuienEsQuien::profundidad_promedio_hojas(){
	float media=0;
	profundidad_promedio_hojas(arbol.root(),media);
	return (media/personajes.size());
	//~ return (media/numero_hojas(arbol.root())); //Tambien funciona bien
}

int QuienEsQuien::profundidad(bintree<Pregunta>::node n){
	if(!n.null()){
		return profundidad(n.parent())+1;
	}
	return -1;
}


void QuienEsQuien::profundidad_promedio_hojas(bintree<Pregunta>::node n, float &sum_total_profundidad){
	if(!n.null()){
		if(n.left().null() && n.right().null()){//Es una hoja
			sum_total_profundidad+=profundidad(n);
		}
		profundidad_promedio_hojas(n.left(), sum_total_profundidad);
		profundidad_promedio_hojas(n.right(), sum_total_profundidad);
	}
}


/***********************************************************************
********************Metodos adicionales*********************************
***********************************************************************/



void QuienEsQuien::preguntas_formuladas(stack<pair<string,bool>> & pila_preguntas,bintree<Pregunta>::node jugada){
	if(jugada != arbol.root()){
		if(jugada.parent().left()==jugada){//Si soy de izq.
			string pregunta=(*(jugada.parent())).obtener_pregunta();
			pila_preguntas.push(make_pair(pregunta,true));
		}else if(jugada.parent().right()==jugada){//Si soy de der.
			string pregunta=(*(jugada.parent())).obtener_pregunta();
			pila_preguntas.push(make_pair(pregunta,false));
		}
		preguntas_formuladas(pila_preguntas,jugada.parent());
	}

}

void QuienEsQuien::preguntas_formuladas(bintree<Pregunta>::node jugada){
	if(jugada != arbol.root()){
		stack<pair<string,bool>> pila_preguntas;
		preguntas_formuladas(pila_preguntas,jugada);
		cout<<"El personaje oculto tiene las siguientes caracteristicas:"<<endl;
		while (!pila_preguntas.empty()){
			cout<<pila_preguntas.top().first<<" - "<<pila_preguntas.top().second<<endl;
			pila_preguntas.pop();
		}
		cout<<"pero aun no se cual es"<<endl;
	}
}


void QuienEsQuien::elimina_personaje(string nombre){



}
/*
void QuienEsQuien::aniade_personaje(string nombre,vector<bool> caracteristicas){
	bintree<Pregunta>::node n=arbol.root();
	bintree<Pregunta>::node n_aux;
	bintree<Pregunta> arbol_aux;
	bool ultima_car=caracteristicas[caracteristicas.size()-1];

	for(int i=0;i<caracteristicas.size()-1;i++){
		if(caracteristicas[i]){
			n=n.left();
		}else{
			n=n.right();
		}
	}
	cout<<"XXXXXXXXXXXx"<<*n<<endl;
	Pregunta pr(atributos[caracteristicas.size()-1],2);
	n_aux=n;
	if(n.parent().right() ==  n){//si cuelgo por la derecha
		arbol.prune_right(n.parent(),arbol_aux);
		bintree<Pregunta> arbol_aux2(pr);
		Pregunta per(nombre,1);

		if(ultima_car){
			arbol_aux2.insert_right(arbol_aux2.root(),(*(arbol_aux.root())));
			arbol_aux2.insert_left(arbol_aux2.root(),per);
			arbol.insert_right(n_aux.parent(),arbol_aux2);
		}else{
			arbol_aux2.insert_left(arbol_aux2.root(),(*(arbol_aux.root())));
			arbol_aux2.insert_right(arbol_aux2.root(),per);
			arbol.insert_right(n_aux.parent(),arbol_aux2);
		}


	}else if(n.parent().left() ==  n){//si cuelgo por la izquierda
		arbol.prune_right(n.parent(),arbol_aux);
		bintree<Pregunta> arbol_aux2(pr);
		Pregunta per(nombre,1);

		if(ultima_car){
			arbol_aux2.insert_right(arbol_aux2.root(),(*(arbol_aux.root())));
			arbol_aux2.insert_left(arbol_aux2.root(),per);
			arbol.insert_left(n_aux.parent(),arbol_aux2);
		}else{
			arbol_aux2.insert_left(arbol_aux2.root(),(*(arbol_aux.root())));
			arbol_aux2.insert_right(arbol_aux2.root(),per);
			arbol.insert_left(n_aux.parent(),arbol_aux2);
		}
	}
}

*/
/* 	====================================================================
	============================ FIN ===================================
	====================================================================
*/

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  if ( !v.empty() ) {
    out << '[';
    std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b]";
  }
  return out;
}

void QuienEsQuien::mostrar_estructuras_leidas(){
	cout << "personajes: "<< (this->personajes) << endl;
	cout << "atributos:  "<< (this->atributos)  << endl;
	cout << "tablero:    "<< endl;


	// Escribe la cabecera del tablero
	for(vector<string>::iterator it_atributos = this->atributos.begin();
		it_atributos != this->atributos.end();
		it_atributos++){
		cout << *it_atributos << "\t";
	}
	cout <<endl;

	int indice_personaje = 0;
	for(vector<vector<bool>>::iterator it_tablero_atributos = tablero.begin();
		it_tablero_atributos!= tablero.end();
		it_tablero_atributos++){

		string personaje = this->personajes[indice_personaje];
		int indice_atributo = 0;
		for(vector<bool>::iterator it_atributos_personaje = (*it_tablero_atributos).begin();
			it_atributos_personaje != (*it_tablero_atributos).end();
			it_atributos_personaje++){

			cout << *it_atributos_personaje<<"\t";

			indice_atributo++;
		}

		cout << personaje << endl;

		indice_personaje++;
	}

}

/**
  * @brief Devuelve una copia de la cadena original sin las subcadenas no deseadas.
  *
  * @param cadena_original Cadena de la que se eliminan las subcadenas no deseadas.
  * @param cadena_a_eliminar Subcadena que se busca y se elimina.
  *
  * @return Copia de la cadena original sin las subcadenas no deseadas.
  */
string limpiar_string(string cadena_original,string cadena_a_eliminar){
	string linea(cadena_original);

	while(linea.find_first_of(cadena_a_eliminar) != std::string::npos){
		linea.erase(linea.find_first_of(cadena_a_eliminar),cadena_a_eliminar.length());
	}

	return linea;
}

istream& operator >> (istream& is, QuienEsQuien &quienEsQuien) {
	quienEsQuien.limpiar();

  	if(is.good()){
  		string linea;
    	getline(is, linea, '\n');

    	linea = limpiar_string(linea,"\r");

    	while(linea.find('\t') != string::npos ){
    		string atributo = linea.substr(0,linea.find('\t'));
			quienEsQuien.atributos.push_back(atributo);
    		linea = linea.erase(0,linea.find('\t')+1);
    	}

		assert(linea ==  "Nombre personaje");
	}

    while( is.good() ) {
    	string linea;
    	getline(is, linea, '\n');
    	linea = limpiar_string(linea,"\r");

    	//Si la linea contiene algo extrae el personaje. Si no lo es, la ignora.
    	if(linea != ""){;
	    	vector<bool> atributos_personaje;

	    	int indice_atributo=0;
	    	while(linea.find('\t') != string::npos){
	    		string valor = linea.substr(0,linea.find('\t'));

	    		assert(valor == "0" || valor == "1");

	    		bool valor_atributo = valor == "1";

	    		atributos_personaje.push_back(valor_atributo);

	    		linea = linea.erase(0,linea.find('\t')+1);
	    		indice_atributo++;
			}

			string nombre_personaje = linea;

	    	quienEsQuien.personajes.push_back(nombre_personaje);
	    	quienEsQuien.tablero.push_back(atributos_personaje);
	    }
  	}

	return is;
}

ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien){

	//Escribimos la cabecera, que contiene los atributos y al final una columna para el nombre
	for(vector<string>::const_iterator it_atributos = quienEsQuien.atributos.begin();
		it_atributos != quienEsQuien.atributos.end();
		it_atributos++){

		os  << *it_atributos << "\t";
	}
	os << "Nombre personaje" << endl;

	//Rellenamos con ceros y unos cada l�nea y al final ponemos el nombre del personaje.
	for(int indice_personaje=0;indice_personaje<quienEsQuien.personajes.size();indice_personaje++){
		for(int indice_atributo=0;indice_atributo<quienEsQuien.atributos.size();indice_atributo++){

			os  << quienEsQuien.tablero[indice_personaje][indice_atributo] << "\t";
		}
		os  << quienEsQuien.personajes[indice_personaje] << endl;
	}

	return os;
}

/**
  * @brief Convierte un n�mero a un vector de bool que corresponde
  *        con su representaci�n en binario con un numero de digitos
  *        fijo.
  *
  * @param n N�mero a convertir en binario.
  * @param digitos N�mero de d�gitos de la representaci�n binaria.
  *
  * @return Vector de booleanos con la representaci�n en binario de @e n
  *      con el n�mero de elementos especificado por @e digitos.

  */
vector<bool> convertir_a_vector_bool(int n, int digitos) {
  vector<bool> ret;
  while(n) {
    if (n&1){
      ret.push_back(true);
    } else{
      ret.push_back(false);
    }
    n>>=1;
  }

  while(ret.size()<digitos){
  	ret.push_back(false);
  }

  reverse(ret.begin(),ret.end());
  return ret;
}


void QuienEsQuien::usar_arbol(bintree<Pregunta> arbol_nuevo){
	arbol = arbol_nuevo;
}

void escribir_esquema_arbol(ostream& ss,
					  const bintree<Pregunta>& a,
		    		  bintree<Pregunta>::node n,
					  string& pre){
	if (n.null()){
	    ss << pre << "-- x" << endl;
	} else {
	    ss << pre << "-- " << (*n) << endl;
	    if ( !n.right().null() || !n.left().null()) {// Si no es una hoja
			pre += "   |";
	    	escribir_esquema_arbol(ss,a, n.right(), pre);
	     	pre.replace(pre.size()-4, 4, "    ");
	      	escribir_esquema_arbol (ss,a, n.left(), pre);
	      	pre.erase(pre.size()-4, 4);
	    }
  	}
}


void QuienEsQuien::escribir_arbol_completo() const{
	string pre = "";
	escribir_esquema_arbol(cout,this->arbol,this->arbol.root(),pre);
}


/**
 * @brief Genera numero enteros positivos aleatorios en el rango [min,max).
**/

int generaEntero(int min, int max){
    int tam= max -min;
    return ((rand()%tam)+min);
}

void QuienEsQuien::tablero_aleatorio(int numero_de_personajes){
	srand(0);

	this->limpiar();

	float log_2_numero_de_personajes = log(numero_de_personajes)/log(2);

	int numero_de_atributos = ceil(log_2_numero_de_personajes);

	cout << "Petici�n para generar "<< numero_de_personajes<<" personajes ";
	cout << "con "<<numero_de_atributos<< " atributos"<<endl;
	cout << "Paso 1: generar "<< pow(2,numero_de_atributos) << " personajes"<<endl;

	//Fase 1: completar el tablero con todos los personajes posibles
	//Completo el tablero y los nombres de personajes a la vez
	for(int indice_personaje=0;indice_personaje< pow(2,numero_de_atributos);indice_personaje++){
		vector<bool> atributos_personaje = convertir_a_vector_bool(indice_personaje,numero_de_atributos);
		string nombre_personaje = "Personaje_"+to_string(indice_personaje);

		this->personajes.push_back(nombre_personaje);
		this->tablero.push_back(atributos_personaje);
	}

	// Completo los nombres de los atributos.
	for(int indice_atributo=0;indice_atributo<numero_de_atributos;indice_atributo++){
		string nombre_atributo = "Atr_"+to_string(indice_atributo);
		this->atributos.push_back(nombre_atributo);
	}

	cout << "Paso 2: eliminar "<< (pow(2,numero_de_atributos)-numero_de_personajes) << " personajes"<<endl;
	//Fase 2. Borrar personajes aleatoriamente hasta que quedan solo los que hemos pedido.
	while(personajes.size()>numero_de_personajes){
		int personaje_a_eliminar = generaEntero(0,personajes.size());

		personajes.erase(personajes.begin()+personaje_a_eliminar);
		tablero.erase(tablero.begin()+personaje_a_eliminar);
	}
}
