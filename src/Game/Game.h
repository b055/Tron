/*
 * Game.h
 *
 *  Created on: 03 Aug 2012
 *      Author: cdrnel001
 */

#ifndef GAME_H_
#define GAME_H_

#include "../Player/Player.h"
#include "omp.h"
#include <string>
#include <sstream>
namespace tron{
class Game {
public:
	Game();
	virtual ~Game();

	inline Player getPlayerTwo(){return two;};
	inline Player getPlayerOne(){return one;};
	inline void setPlayerOne(Player other){one = other;};
	inline void setPlayerTwo(Player other){two = other;};
	Grid& getGrid(){return grid;};
	void setGrid(Grid&);
	std::string printGrid();
	bool endState();
	double * getAfterState(){return grid.getAfterState();};
	inline int getTurn(){return turn;}
private:
	Player one;
	Player two;
	int turn;
	Grid grid;
};
};


#endif /* GAME_H_ */
