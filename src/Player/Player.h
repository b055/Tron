/*
 * Player.h
 *
 *  Created on: 03 Aug 2012
 *      Author: cdrnel001
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include "omp.h"
#include "../Grid/Grid.h"
#include "../Neural/Network.h"
namespace tron{
class Player {
public:
	Player();
	Player(int digit);
	virtual ~Player();
	void possibleMoves(Grid**);
	void setOpponent(int x , int y){oppo_x = x; oppo_y = y;}
	Grid& randomMove();
	inline void setX(int x){this->x = x;}
	inline int getX(){return x;}
	inline int getY(){return y;}
	inline void setY(int y){this->y = y;}
	inline void setOppoY(int y){oppo_y = y;}
	inline void setOppoX(int x){oppo_x = x;}
	inline int getOppoX(){return oppo_x;}
	inline int getOppoY(){return oppo_y;}
	inline void setDigit(int d){digit = d;}
	inline int getDigit(){return digit;}
	void setGrid(Grid&);

	std::string printGrid();
	void setHead(Grid&);
	inline void setNet(Network * new_net){net = new_net;}
	Network* getNet(){return net;}
	void reset();

private:
	int digit;
	int oppo_x;
	int oppo_y;
	Grid grid;
	Network * net;
	int x;
	int y;
	void topMoves(Grid**);
	void bottomMoves(Grid**);
	void middleMoves(Grid**);
	Grid& upMove(int);
	Grid& rightMove(int);
	Grid& leftMove(int);
	Grid& downMove(int );
};
}

#endif /* PLAYER_H_ */
