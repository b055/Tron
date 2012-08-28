/*
 * Grid.h
 *
 *  Created on: 06 Aug 2012
 *      Author: cdrnel001
 */

#ifndef GRID_H_
#define GRID_H_

#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include "Voronoi.h"
namespace tron{
class Grid {
public:
	Grid(int );
	Grid(int * ,int*, int**);
	Grid(bool){};
	virtual ~Grid();
	std::vector<int>& operator[](int);
	void setPlayerOneHead(int,int);
	void setPlayerTwoHead(int,int);
	std::string printGrid();
	Grid& operator=(Grid &);
	inline void operator()(int y,int x, int val){grid[y][x] = val;}
	inline int operator()(int y,int x){return grid[y][x];}
	double * getAfterState(int);
	Grid& operator()(Grid&);
	inline std::vector<std::vector<int> > & getGrid(){return grid;}
	bool separated();
private:
	std::vector<std::vector<int> > grid;
	int player_one_head_x;
	int player_one_head_y;
	int player_two_head_x;
	int player_two_head_y;
	int turn;
	bool valid;
	int width;
	double * state;
	int statewidth;
	int cells;
	int * result;
	Voronoi * a;
public:
	void reset();
	inline bool isValid()const{return valid;}
	inline void isValid(bool b){valid = b;}
	inline int getPlayerOneHeadX()const{return player_one_head_x;};
	inline int getPlayerOneHeadY()const{return player_one_head_y;};
	inline int getPlayerTwoHeadY()const{return player_two_head_y;};
	inline int getPlayerTwoHeadX()const{return player_two_head_x;};
	inline void setPlayerOneHeadX(int x){player_one_head_x = x;}
	inline void setPlayerOneHeadY(int y){player_one_head_y = y;}
	inline void setPlayerTwoHeadX(int x){player_two_head_x = x;}
	inline void setPlayerTwoHeadY(int y){player_two_head_y = y;}

};
}
#endif /* GRID_H_ */
