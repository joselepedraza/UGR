/*
 * JosBot.cpp
 *
 *  Created on: 15 ene. 2018
 *      Author: manupc
 */

#include "JosBot.h"

#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

JosBot::JosBot() {
	// Inicializar las variables necesarias para ejecutar la partida
	contador=0;
	/*for(int i = 1; i<=6;i++){
		heuristica[i]=0;
	}*/
}

JosBot::~JosBot() {
	// Liberar los recursos reservados (memoria, ficheros, etc.)
}

void JosBot::initialize() {
	// Inicializar el bot antes de jugar una partida
}

string JosBot::getName() {
	return "JosBot"; // Sustituir por el nombre del bot
}

Move JosBot::nextMove(const vector<Move> &adversary, const GameState &state) {

	Move movimiento= M_NONE;//NUESTRO

	const int PROFUNDIDAD_ALFABETA = 5; // Umbral maximo de profundidad para la poda Alfa_Beta

	double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
	//double alpha, beta; // Cotas de la poda AlfaBeta
	quiensoy();
	//int n_act; //Acciones posibles en el estado actual

	valor = AlfaBeta(state, adversary, 0, PROFUNDIDAD_ALFABETA, movimiento, VMIN, VMAX);

	// Implementar aquí la selección de la acción a realizar

	// OJO: Recordatorio. NO USAR cin NI cout.
	// Para salidas por consola (debug) utilizar ////cerr. Ejemplo:
	// ////cerr<< "Lo que quiero mostrar"<<endl;
	return movimiento;
}

double JosBot::AlfaBeta(const GameState & state/*tablero*/,const vector<Move> & jugador, int profundidad, int profundidad_maxima, Move & accion, double alfa, double beta) {
////cerr << "1" <<endl;
	contador++; // Contador para comprobar el numero de nodos comprobados(inicializado en next move)

	// Atributos
	Move accion_anterior;	//KK - esto no vale panaaa, solo pa llamar a la puta funcion recursiva y no pete
	double aux;
/*
	int opciones[7];
	int n_act = movs_posibles(state, &opciones); // Determino cuantas acciones se pueden realizar
*/
////cerr << "2"<<endl;
	if (profundidad==profundidad_maxima) /*n_act==0*/{ // Hemos llegado al nodo final o no hay mas acciones
		Player j_act = state.getCurrentPlayer();
		////cerr << "3Base"<<endl;
		return state.getScore(j_act);
	/*
		if(yo == state.getCurrentPlayer()){
			return state.getScore(yo);
		}
		else{
			return state.getScore(contrincante);
		}
*/
	}
	else if(state.isFinalState()){
		Player ganador = state.getWinner();
		if(yo == ganador){
			return VMAX;
		}
		else if(contrincante == ganador){
			return VMIN;
		}
		else{
			return 0; //empate
		}
	}
	else { // Vamos a recorrer los hijos
////cerr << "4"<<endl;
		Move ult_act=M_NONE; //int ult_act = -1;

		ult_act = (Move) heuristicaa(state);	//casteo la posicion para el movimiento
		////cerr << "ult_act" << (int) ult_act << endl;
		////cerr << "heuristica" << heuristica(state) << endl;
		GameState hijo = state.simulateMove(ult_act); //Genero el siguiente state hijo
		//profundidad++;

		if (profundidad%2==0) { //Nodo MAX

				//while (!(profundidad==profundidad_maxima || state.isFinalState())/*ult_act<7*//*!(hijo==state)*/){ // Recorro los hijos (cuando sea igual al parametro es que ha terminado)
		for(int i=1; i<7;i++){
////cerr << "5MAX"<<endl;
				aux = AlfaBeta(hijo, jugador, profundidad+1, profundidad_maxima, accion_anterior, alfa, beta);
////cerr<< "aux" << aux << endl;
				if (aux>alfa){
					alfa=aux;
					accion = (Move) (ult_act); // Este es el movimiento que hay que arrastrar(debemos castearlo)
					////cerr << "6"<<endl;
				}

				if (beta<=alfa) {
					////cerr << "7"<<endl;
					break; // Poda beta

				}


				hijo = state.simulateMove(ult_act); // Genero el siguiente state hijo
			//}
		}

		  return alfa;

		} else { //Nodo MIN

			//while (!(profundidad==profundidad_maxima || state.isFinalState())/*ult_act<7*//*!(hijo==state)*/){ // Recorro los hijos (cuando sea igual al parametro es que ha terminado)
		for(int i=1; i<7;i++){
////cerr << "8MIN" << profundidad <<endl;
////cerr << "ult_act" << (int) ult_act << endl;
////cerr << "heuristica" << heuristica(state) << endl;
				aux = AlfaBeta(hijo, jugador, profundidad+1, profundidad_maxima, accion_anterior, alfa, beta);

				if (aux<beta){
				  beta=aux;
					////cerr << "9"<<endl;
				  accion = (Move) (ult_act); // Este es el movimiento que hay que arrastrar
				}

				if (beta<=alfa) {
					////cerr << "10"<<endl;
				  break; // Poda alfa

				}

				hijo = state.simulateMove(ult_act); // Genero el siguiente state hijo
			//}
		}

		  return beta;

		}

	}

}

/*
int JosBot::movs_posibles(const GameState & state, int opciones[]){
	Player turno = state.getCurrentPlayer();
	int contador = 0;
	// Recorremos los 6 movimientos posibles
	for (int i= 1; i<=6; i++) {	//posicion 0 = granero del jugador por eso no la contamos
		// Comprobamos si hay semillas en la casilla i
		if (state.getSeedsAt(turno, (Position) i) >0){
			contador++;
		}
		opciones[i]=state.getSeedsAt(turno, (Position) i);
	}
	return contador;
}
*/
/*PRIMERA FUNCION HEURISTICA: ESCOGEMOS CUALQUIER MOVIMIENTO QUE DEJE 1 FICHA EN NUESTRO GRANERO
	SEGUNDA FUNCION HEURISTICA: PRIMERO ESCOGEMOS EL MOVIMIENTO QUE NOS PERMITA TURNO EXTRA (LA ULTIMA SEMILLA DE LA SIEMBRA SE DEPOSITA EN EL GRANERO)

double JosBot::heuristica(const GameState & state){
	int heurist=0;	//posicion del i mas grande (de la casilla con mas semillas)
	bool ok = true;
	unsigned char semillas[7];
	for(int i=0; i<=6;i++){
		semillas[i]=0;
	}
	Player turno = state.getCurrentPlayer();
	for(int i=1; i<=6;i++){
		semillas[i]=state.getSeedsAt(turno, (Position) i);
	}
	for(int i=1; i<=6; i++){
		if(semillas[i]==i){
			heurist=i;	//devuelvo posicion donde puede llegar 1 ficha al granero
			ok = false;
		}
	}
	if(ok){
		for(int i=6; i>=1; i--){	//de esta manera normalmente caen mas semillas en las del contrario
			if(semillas[i]>0){
				heurist = i;
			}
		}
	}

	return heurist;
}
	*/
/*TERCERA HEURISTICA:

podemos dar puntuacion al posible movimiento de la siguiente manera:
	-Si el mov nos deja una fihca en el granero-> heurist+1
	-Si el mov nos deja la ultima ficha en el granero-> heurist+2 (Turno Extra)
	-Si el mov deja el minimo de semillas al contrario-> heurist+1
	-Si el movimiento nos permite robar->heurist+3
		(robo-> Si un jugador realiza una siembra y la última semilla la deposita en una de sus casillas,
						y resulta que esta casilla está vacía pero la opuesta del otro jugador no, entonces el jugador le roba las fichas
						de esa casilla a su contrincante, llevandoselas directamente a su granero)
*/

int JosBot::heuristicaa(const GameState & state){
	int h=0;	//posicion del i mas grande (de la casilla con mas semillas) por defecto la primera posicion
	bool ult_gran = true;
	unsigned char nsemillas[7];
	int heuristica[7];	//CREO QUE EL MECANISMO DE PUNTUACION FUNCIONA, SIMPLEMENTE QUE HEURISTICA SE SOBREESCRIBE
	//cerr << "1" <<endl;
	for(int i=1; i<=6;i++){	//inicializamos nuestros vectores(vector donde guardaremos el numero de semillas de cada casilla y vector con la puntuacion de cada movimiento)
		nsemillas[i]=heuristica[i]=0;
	}
	Player turno = state.getCurrentPlayer();	//guardamos el estado del turno actual

	for(int i=1; i<=6;i++){	//contamos las semillas de cada posicion sin contar con el granero (pos=0)
		nsemillas[i]=state.getSeedsAt(turno, (Position) i);//rellenamos el vector con el numero de semillas
		//cerr << "nsem[" << i << "]= " << (int) nsemillas[i] <<endl;
	}

	for(int i=1; i<=6; i++){	//recorremos el numero de semillas de cada posicion
		if(nsemillas[i]>i){	//si el numero de semillas es mayor que el numero de la posicion
			//cerr << "nsem[i]>i" << (int) nsemillas[i] << ">" << i <<endl;
			heuristica[i]=heuristica[i]+2;	//incremento (con un punto) el contador de posicion donde puede llegar 1 ficha al granero al hacer la siembra
			ult_gran = false;	//la ultima ficha no cae en el granero, cae en casillas del oponente (para turno extra)
		}
		else if(nsemillas[i]==i){//si coincide el num de semillas de la casilla con la posicion => la ultima ficha al sembrar será en el granero (turno extra)
			//cerr << "nsem[i]==i" << (int) nsemillas[i] << "==" << i <<endl;
			ult_gran = true;
			heuristica[i]=heuristica[i]+3;//nos proporciona turno extra (ult_gran = true)
		}
		else{
			//cerr << "nsem[i]<i" << (int) nsemillas[i] << "<" << i <<endl;
			heuristica[i]=heuristica[i]+1;
		}
	}

	for(int i=1;i<6;i++){	//movimientos de 1-6 (7 es NONE)
		//cerr << "heuristica[" << i << "]= " << heuristica[i] <<endl;
		//cerr << "heuristica[" << i+1 << "]= " << heuristica[i+1] <<endl;
		if(heuristica[i]>heuristica[i+1] && nsemillas[i]!=0){
			h=i;
		}
		else if(heuristica[i]==heuristica[i+1] && nsemillas[i+1]!=0){
			h=i+1;
		}
	}

	return h;
}

void JosBot::quiensoy(){
	if(J1 == this->getPlayer()){
		yo = J1;
		contrincante = J2;
	}
	else{
		yo = J2;
		contrincante = J1;
	}
}
