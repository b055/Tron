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
	Human(int,int);
	virtual ~Human();
	void play();
	std::string getWeights(){return "";}
	void upMove(int);
	void downMove(int);
	void rightMove(int);
	void leftMove(int);

};

}

#endif /* HUMAN_H_ */
