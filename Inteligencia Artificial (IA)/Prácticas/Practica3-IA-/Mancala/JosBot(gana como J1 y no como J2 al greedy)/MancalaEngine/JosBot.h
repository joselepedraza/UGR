/*
 * JosBot.h
 *
 *  Created on: 15 ene. 2018
 *      Author: manupc
 */

#include "Bot.h"
#include <limits>

#ifndef MANUPCBOT_H_
#define MANUPCBOT_H_

const int VMAX = numeric_limits<int>::max();
const int VMIN = numeric_limits<int>::min();

class JosBot:Bot {
public:
	JosBot();
	~JosBot();


	void initialize();
	string getName();
	Move nextMove(const vector<Move> &adversary, const GameState &state);

private:
	int contador;
	//int heuristica[7];	//CREO QUE EL MECANISMO DE PUNTUACION FUNCIONA, SIMPLEMENTE QUE HEURISTICA SE SOBREESCRIBE
	Player yo, contrincante;

	double AlfaBeta(const GameState & state/*tablero*/, const vector<Move> & jugador, int profundidad, int profundidad_maxima, Move & accion, double alfa, double beta);
	int movs_posibles(const GameState & state, int opciones[]);
	int heuristicaa(const GameState & state);
	void quiensoy();


};

#endif /* MANUPCBOT_H_ */
