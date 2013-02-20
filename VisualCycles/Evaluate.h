/*
 * Evaluate.h
 *
 *  Created on: Aug 9, 2012
 *      Author: ivan
 */

#ifndef EVALUATE_H_
#define EVALUATE_H_
#include "Player.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>

namespace tron {

class Evaluate {
public:
	Evaluate(Player*,Player*);
	virtual ~Evaluate();
	void progress(int);
	inline void setGap(int g){gap = g;}
	inline int getGap(){return gap;}
private:
	long one_count;
	long two_count;
	Player * one;
	Player * two;
	int gap;
	int width;
	std::string date;
};

}

#endif /* EVALUATE_H_ */
