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
namespace tron {

class Minimax: public tron::Player {
public:
	Minimax(int,int);
	virtual ~Minimax();
	void play();
private:
	Grid& alpha_beta(Grid&, int );
	int min(Grid,int,int,int);
	int max(Grid,int,int,int);

};
} /* namespace tron */
#endif /* MINIMAX_H_ */
