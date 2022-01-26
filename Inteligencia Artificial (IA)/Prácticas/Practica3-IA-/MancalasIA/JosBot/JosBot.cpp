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
}

JosBot::~JosBot() {
}

void JosBot::initialize() {
}

string JosBot::getName() {
	return "JosBot";
}

Move JosBot::nextMove(const vector<Move> &adversary, const GameState &state) {
	const int PROFUNDIDAD_ALFABETA = 6; // Umbral maximo de profundidad para la poda Alfa_Beta
	quiensoy();	//J1 o J2
	Move accion = AlfaBeta(state, PROFUNDIDAD_ALFABETA);

	return accion;
}

Move JosBot::AlfaBeta(const GameState & state, int profundidad_maxima) {
	int alfa = VMIN;
	int beta = VMAX;
	int puntostotal = VMIN;
	Move acc_act = M_NONE;

	for(int i=1; i<=6;i++){	//recorro mis casillas
		if(state.getSeedsAt(yo, (Position)i) > 0){	//si tengo semillas entonces:
			GameState hijo = state.simulateMove((Move)i);	//simulo el movimiento
			int aux = AlfaBeta(hijo, contrincante, 0, profundidad_maxima, alfa, beta);	//llamo a la poda alfabeta con el estado del hijo (contrincante)
			if(aux>puntostotal){	//si se consiguen mas puntos
				acc_act = ((Move) i);	//actualizo el movimiento actual y el total de puntos
				puntostotal = aux;
			}
		}
	}
	if(acc_act==M_NONE){
		acc_act = alternativa(state);
	}
	return acc_act;
}

int JosBot::AlfaBeta(const GameState & state, Player jos, int profundidad, int profundidad_maxima, double alfa, double beta) {

	if(state.isFinalState() || profundidad==profundidad_maxima){
	Player ganador = state.getWinner();
		if(yo == ganador){
			return VMAX;
		}
		else if(contrincante == ganador){
			return VMIN;
		}
		else if(ganador == 0){
			return 0;
		}
		else{	//si no hay ganador ni perdedor ni se empata
			return heuristicaa(state);
		}
	}
	else { // Recorro los hijos
		if (jos == yo) { //Nodo MAX
			int puntosmax = VMIN;

			for(int i=1; i<=6;i++){
				if(state.getSeedsAt(yo, (Position)i) > 0){
					GameState hijo = state.simulateMove((Move)i); //Genero el siguiente state hijo
					int aux = AlfaBeta(hijo, contrincante, profundidad+1, profundidad_maxima, alfa, beta);
					if (aux>puntosmax){
						puntosmax=aux;
					}
					if(puntosmax > alfa){
						alfa = puntosmax;
					}
					if (beta<=alfa){
						break; // Poda beta
					}
				}
			}
		  return puntosmax;
		}
		else { //Nodo MIN
			int puntosmin = VMAX;

			for(int i=1; i<=6;i++){
				if(state.getSeedsAt(contrincante, (Position)i) > 0){
					GameState hijo = state.simulateMove((Move)i); //Genero el siguiente state hijo
					int aux = AlfaBeta(hijo, yo, profundidad+1, profundidad_maxima, alfa, beta);
					if (aux<puntosmin){
						puntosmin=aux;
					}
					if(puntosmin < beta){
						beta = puntosmin;
					}

					if (beta<=alfa) {
						break; // Poda beta
					}
				}
			}
			return puntosmin;
		}
	}
}

int JosBot::heuristicaa(const GameState & state){
	int totalSem1 = 0;
	int totalSem2 = 0;
	for(int i=1;i<=6;i++){
		totalSem1 += state.getSeedsAt(yo, (Position)i);
		totalSem2 += state.getSeedsAt(contrincante, (Position)i);
	}
	totalSem1 += state.getScore(yo);
	totalSem2 += state.getScore(contrincante);

	return puedorobar((totalSem1-totalSem2), state);
}

int JosBot::puedorobar(int totalSem12,const GameState &state){
	for (int i=1;i<=6;i++){//para max
		roboMax(totalSem12,state,i);
	}
	for (int i=1;i<=6;i++){//para min
		roboMin(totalSem12,state,i);
	}
	return totalSem12;
}
void JosBot::roboMax(int &totalSem12, const GameState &state, int i){
	if (state.getSeedsAt(yo, (Position) i) == 0 && state.isValidState()){	//si yo tengo alguna posicion(valida) sin semillas (puedo robar)
			int pos=posContrincante(i);
			int num_fichas=state.getSeedsAt(contrincante,((Position)pos));//Sumamos las semillas de nuestro contrincante(las de enfrente mia)
			totalSem12+=num_fichas;
	}
}

void JosBot::roboMin(int &totalSem12, const GameState &state, int i){
	if (state.getSeedsAt(contrincante, (Position) i) == 0 && state.isValidState()){
		int pos=posContrincante(i);
		int num_fichas=state.getSeedsAt(yo,((Position)pos));
		totalSem12+=num_fichas;
	}
}

int JosBot::posContrincante(int pos){
	int pos_inv = -1;

	switch (pos) {
		case 1:
			pos_inv = 6;
			break;
		case 2:
			pos_inv = 5;
			break;
		case 3:
			pos_inv = 4;
			break;
		case 4:
			pos_inv = 3;
			break;
		case 5:
			pos_inv = 2;
			break;
		case 6:
			pos_inv = 1;
			break;
	}

	return pos_inv;
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


Move JosBot::alternativa(const GameState & state){
	Move h=M_NONE;	//posicion del i mas grande (de la casilla con mas semillas) por defecto la primera posicion
	bool ult_gran = true;
	unsigned char nsemillas[7];
	int alternativa[7];

	for(int i=1; i<=6;i++){	//inicializamos nuestros vectores(vector donde guardaremos el numero de semillas de cada casilla y vector con la puntuacion de cada movimiento)
		nsemillas[i]=alternativa[i]=0;
	}
	Player turno = state.getCurrentPlayer();	//guardamos el estado del turno actual

	for(int i=1; i<=6;i++){	//contamos las semillas de cada posicion sin contar con el granero (pos=0)
		nsemillas[i]=state.getSeedsAt(turno, (Position) i);//rellenamos el vector con el numero de semillas
	}

	for(int i=1; i<=6; i++){	//recorremos el numero de semillas de cada posicion
		if(nsemillas[i]>i){	//si el numero de semillas es mayor que el numero de la posicion
			alternativa[i]=alternativa[i]+2;	//incremento (con un punto) el contador de posicion donde puede llegar 1 ficha al granero al hacer la siembra
			ult_gran = false;	//la ultima ficha no cae en el granero, cae en casillas del oponente (para turno extra)
		}
		else if(nsemillas[i]==i){//si coincide el num de semillas de la casilla con la posicion => la ultima ficha al sembrar será en el granero (turno extra)
			//cerr << "nsem[i]==i" << (int) nsemillas[i] << "==" << i <<endl;
			ult_gran = true;
			alternativa[i]=alternativa[i]+3;//nos proporciona turno extra (ult_gran = true)
		}
		else{//simplificar sumo 1
			alternativa[i]=alternativa[i]+1;
			}
		}

	for(int i=1;i<6;i++){	//movimientos de 1-6 (7 es NONE)
		if(alternativa[i]>alternativa[i+1] && nsemillas[i]!=0){
			h=(Move) i;
		}
		else if(alternativa[i]==alternativa[i+1] && nsemillas[i+1]!=0){
			h=((Move)(i+1));
		}
	}

	return h;
}
