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
	Grid& alpha_beta(int );
	float min(Grid,float,float,int,Grid & next);
	float max(Grid,float,float,int,Grid & next);
	time_t start,end;
};
} /* namespace tron */
#endif /* MINIMAX_H_ */
