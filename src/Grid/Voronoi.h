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
#include <iostream>
#include <algorithm>
#include <sstream>
#include "Grid.h"
namespace tron{
class Voronoi{
private:
	int co,width;
	std::vector<std::vector< int> > vor;
	std::vector<std::vector< int> > mark;
	std::vector<std::vector< int> > pos;
	std::vector<std::vector< int> > one;
	std::vector<std::vector< int> > two;
	Grid grid;
	void surroundCheck(int,int,std::vector<std::vector< int> >&);
	void surroundLeft(int,int,std::vector<std::vector< int> >&);
	int neighbourMin(int,int,std::vector<std::vector< int> >&);
	void resetVor();
	int countArea(int,int,std::vector<std::vector< int> >&);
	int countLeft(int,int,std::vector<std::vector< int> >&);
	void surroundTop(int,int,std::vector<std::vector< int> >&);
	void surroundBottom(int,int,std::vector<std::vector< int> >&);
	int countBottom(int,int,std::vector<std::vector< int> >&);
	int countTop(int,int,std::vector<std::vector< int> >&);
	void getMerge(int);
	void resetOneandTwo();
	void resetMark();
	int VAR;
public:
	void setGrid(Grid&);
	Voronoi(Grid*,int);
	Voronoi(int);
	std::string outputVoronoi();
	std::string outputOne();
	std::string outputTwo();
	virtual ~Voronoi();
	int * calculate(int);
	inline void setWidth(int w){width = w;}

};
}
#endif /* VORONOI_H_ */
