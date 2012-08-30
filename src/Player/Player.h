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
#include "time.h"
namespace tron{
class Player {
public:
	Player(int,int);
	virtual ~Player();
	void possibleMoves(Grid &grid,Grid**);
	void setOpponent(int x , int y){oppo_x = x; oppo_y = y;}
	void randomMove(Grid &,Grid*);
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
	inline int getWidth(){return width;}
	inline void setOpponentPlayer(Player*p){opponent = p;}
	inline Player* getOpponentPlayer(){return opponent;}
	std::string printGrid();
	void setHead(Grid&);
	inline void setNet(Network * new_net){net = new_net;}
	Network* getNet(){return net;}
	void reset();
	void wallHug(Grid**);
private:
	Network * net;
protected:
	Player * opponent;
	int x;
	int y;
	int digit;
	int oppo_x;
	int oppo_y;
	int width;
	Grid * grid;
	void upMove(Grid & grid,int, Grid * result);
	void rightMove(Grid & grid, int,Grid * result);
	void leftMove(Grid& ,int, Grid * result);
	void downMove(Grid &,int , Grid * result);
	void topMoves(Grid &,Grid**);
	void bottomMoves(Grid &,Grid**);
	void middleMoves(Grid &,Grid**);
	bool debug;
};
}

#endif /* PLAYER_H_ */
