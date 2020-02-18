/*
 * JosBot.h
 *
 *  Created on: 15 ene. 2018
 *      Author: manupc
 */

#include "Bot.h"

#ifndef MANUPCBOT_H_
#define MANUPCBOT_H_

class JosBot:Bot {
public:
	JosBot();
	~JosBot();


	void initialize();
	string getName();
	Move nextMove(const vector<Move> &adversary, const GameState &state);

private:
	int contador;

	double AlfaBeta(const GameState & state/*tablero*/, const vector<Move> & jugador, int profundidad, int profundidad_maxima, Move & accion, double alfa, double beta);
	int movs_posibles(const GameState & state, int opciones[]);
	int heuristica(const GameState & state);



};

#endif /* MANUPCBOT_H_ */
