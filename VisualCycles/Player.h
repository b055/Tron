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
#include "Grid.h"
#include <iostream>
#include <vector>
#include "time.h"
namespace tron{
class Player {
public:
	Player(int);
	virtual ~Player();
	std::vector<std::vector< int> > possibleMoves();
	void setOpponent(int x , int y){oppo_x = x; oppo_y = y;}
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
	inline void setGrid(Grid* ptr){grid = ptr;}
	inline Grid& getGrid(){return *grid;}
	//inline int getWidth(){return width;}
	inline void setOpponentPlayer(Player*p){opponent = p;}
	inline Player* getOpponentPlayer(){return opponent;}
	std::string printGrid();
	void setHead(Grid&);
	void reset();
	void wallHug(Grid**);
	inline bool getLoser(){return loser;}
	inline void setLoser(bool l){loser = l;}
	inline int getPrior(){return priorLosing;}
protected:
	Player * opponent;
	int x;
	int y;
	int digit;
	int oppo_x;
	int oppo_y;
	Grid * grid;
	std::vector<int> upMove(int);
	std::vector<int> rightMove(int);
	std::vector<int> leftMove(int);
	std::vector<int> downMove(int );
	std::vector<int> randomMove();
	std::vector<std::vector< int> > topMoves();
	std::vector<std::vector< int> > bottomMoves();
	std::vector<std::vector< int> > middleMoves();
	int priorLosing;
	bool debug;
	bool loser;
};
}

#endif /* PLAYER_H_ */
