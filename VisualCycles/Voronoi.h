/*
 * Voronoi.h
 *
 *  Created on: Aug 25, 2012
 *      Author: ivan
 */

#ifndef VORONOI_H_
#define VORONOI_H_
#include <string>
#include <vector>
#include <queue>
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
	int VAR, one_avail,two_avail;
	
public:
	inline std::vector<std::vector< int> > getVor(){return vor;}
	Voronoi(Grid*,int);
	std::string outputVoronoi();
	std::string outputOne();
	std::string outputTwo();
	virtual ~Voronoi();
	int * calculate(int);
	inline int getOneAvail(){return one_avail;}
	inline int getTwoAvail(){return two_avail;}
	inline int getOneNorth(){return one[0][0];}
	inline int getTwoNorth(){return two[0][0];}
	inline int getOneSouth(){return one[width-1][0];}
	inline int getTwoSouth(){return two[width-1][0];}
};
}
#endif /* VORONOI_H_ */
