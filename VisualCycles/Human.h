/*
 * Human.h
 *
 *  Created on: Aug 21, 2012
 *      Author: ivan
 */

#ifndef HUMAN_H_
#define HUMAN_H_

#include "Player.h"

namespace tron {

class Human: public tron::Player {
public:
	Human(int);
	virtual ~Human();
	void play();
	std::string getWeights(){return "";}

};

}

#endif /* HUMAN_H_ */
