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
		else{
			//return 0; //empate
			return heuristicaa(state);	//devuelvo el valor de heuristica
		}
	}
	else { // Vamos a recorrer los hijos
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

	return heuristica_robo((totalSem1-totalSem2), state);
}

int JosBot::heuristica_robo(int totalSem12,const GameState &state){
	for (int i=1;i<=6;i++){//para max
		roboMax(totalSem12,state,i);
	}
	for (int i=1;i<=6;i++){//para min
		roboMin(totalSem12,state,i);
	}
	return totalSem12;
}
void JosBot::roboMax(int &totalSem12, const GameState &state, int i){
	if (state.getSeedsAt(yo, (Position) i) == 0 && state.isValidState()){	//si yo tengo alguna casilla vacia (contrincante me puede robar)
			int pos=posContrincante(i);
			int num_fichas=state.getSeedsAt(contrincante,((Position)pos));//Sumamos las semillas de nuestro contrincante
			totalSem12+=num_fichas;
	}
}

void JosBot::roboMin(int &totalSem12, const GameState &state, int i){
	if (state.getSeedsAt(contrincante, (Position) i) == 0 && state.isValidState()){//Si mi casilla esta vacia
		int pos=posContrincante(i);
		int num_fichas=state.getSeedsAt(yo,((Position)pos));// sumamos las de mi contrincante(yo en este caso)
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
