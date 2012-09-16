/*
 * Voronoi.h
 *
 *  Created on: Aug 25, 2012
 *      Author: ivan
 */

#ifndef VORONOI_H_
#define VORONOI_H_
#include "string.h"
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "Grid.h"
#include <cmath>
#include "Chamber.h"
namespace tron{
class Voronoi{
private:
	int co,width;
	std::vector<std::vector< int> > vor;
	std::vector<std::vector< int> > mark;
	std::vector<std::vector< int> > one;
	std::vector<std::vector< int> > two;
	Grid * grid;
	void surroundCheck(int,int,std::vector<std::vector< int> >&);
	int neighbourMin(int,int,std::vector<std::vector< int> >&);
	void resetVor();

	void getMerge(int);
	void resetOneandTwo();
	void resetMark();
	void breadth(int);
	int VAR;
	
public:
	inline std::vector<std::vector< int> > getVor(){return vor;}
	Voronoi(Grid*,int);
	std::string outputVoronoi();
	std::string outputOne();
	std::string outputTwo();
	virtual ~Voronoi();
	int * calculate(int);

};
}
#endif /* VORONOI_H_ */
