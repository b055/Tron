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
	Game(int);
	virtual ~Game();
	Grid& getGrid(){return grid;};
	void setGrid(Grid&);
	std::string printGrid();
	bool endState();
	inline int getTurn(){return turn;}
	void reset();
private:
	int turn;
	Grid grid;
	int width;
};
};


#endif /* GAME_H_ */
