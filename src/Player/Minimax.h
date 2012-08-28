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
namespace tron {

class Minimax: public tron::Player {
public:
	Minimax(int,int);
	virtual ~Minimax();
	void play();
};

} /* namespace tron */
#endif /* MINIMAX_H_ */
