/*
 * Minimax.h
 *
 *  Created on: Aug 27, 2012
 *      Author: ivan
 */

#ifndef MINIMAX_H_
#define MINIMAX_H_

#include "Player.h"
#include "../Grid/Voronoi.h"
#include <limits>
#include <time.h>
#include <stdio.h>
namespace tron {

class Minimax: public tron::Player {
public:
	Minimax(int,int);
	virtual ~Minimax();
	void play(time_t &start);

private:
	int min(int,int,int);
	int max(int,int,int);
	int MAX;
	int LIMIT;
	int priorLosing;
	time_t start,end;
	void restore(int,int,int,int);
	void restoreGrid(int,int,int);
};
} /* namespace tron */
#endif /* MINIMAX_H_ */
