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

	Player yo, contrincante;

	Move AlfaBeta(const GameState & state, int profundidad_maxima) ;
	int AlfaBeta(const GameState & state, Player jos, int profundidad, int profundidad_maxima, double alfa, double beta);
	void quiensoy();
	int heuristicaa(const GameState & state);
	int puedorobar(int totalSem12,const GameState &state);
	int posContrincante(int pos);
	void roboMax(int &totalSem12, const GameState &state, int i);
	void roboMin(int &totalSem12, const GameState &state, int i);
	Move alternativa(const GameState & state);
};

#endif /* MANUPCBOT_H_ */
