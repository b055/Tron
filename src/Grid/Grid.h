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
namespace tron{
class Grid {
public:
	Grid();
	Grid(int * ,int*, int**);
	Grid(bool){};
	virtual ~Grid();
	int* operator[](int);
	void setPlayerOneHead(int,int);
	void setPlayerTwoHead(int,int);
	std::string printGrid();
	Grid& operator=(Grid&);
	double * getAfterState();
	Grid& operator()(Grid&);

private:
	int ** grid;
	int player_one_head_x;
	int player_one_head_y;
	int player_two_head_x;
	int player_two_head_y;
	int turn;
	bool valid;
public:
	void reset();
	inline bool isValid(){return valid;}
	inline void isValid(bool b){valid = b;}
	inline int getPlayerOneHeadX(){return player_one_head_x;};
	inline int getPlayerOneHeadY(){return player_one_head_y;};
	inline int getPlayerTwoHeadY(){return player_two_head_y;};
	inline int getPlayerTwoHeadX(){return player_two_head_x;};
	inline void setPlayerOneHeadX(int x){player_one_head_x = x;}
	inline void setPlayerOneHeadY(int y){player_one_head_y = y;}
	inline void setPlayerTwoHeadX(int x){player_two_head_x = x;}
	inline void setPlayerTwoHeadY(int y){player_two_head_y = y;}
};
}
#endif /* GRID_H_ */
