/*
 * Chamber.h
 *
 *  Created on: Sep 5, 2012
 *      Author: Student
 */

#ifndef CHAMBER_H_
#define CHAMBER_H_
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
namespace tron {

class Chamber {
public:
	Chamber(std::vector<std::vector< int> >*,int,int,int,int);
	virtual ~Chamber();
	void printMark();
	std::string printSol();
	inline int getValue(){return value;}
	int breadth(int,int,int);
private:
	bool isValid(int,int,int);
	std::vector<std::vector< int> >* grid;
	std::vector<std::vector< int> > mark;
	std::vector<std::vector< int> > sol;
	bool isArtPoint(int,int);
	int digit;
	bool NorthValue,SouthValue;
	int counter;
	int width;
	int value;
	int rootChildren;
	void populate(int,int,int & ,int);
	void surroundPopulate(int,int,int&,int);
	int red;
	int black;
public:
	class Vertex
	{
	public:
		Vertex * parent;
		std::vector< Vertex*> children;
		int low,num,x,y;
		bool visited;
		int width;
		Vertex(int x, int y):x(x),y(y)
		{
			low = num =0;
			width = 10;
			visited = false;
		}
		~Vertex() {

		}
		bool operator==(Vertex& v)
		{
			if(v.y == y)
			{
				if(y == 0 || y == width-1)
					return true;
				else
					return x == v.x;
			}
			return false;
		}
		bool operator!=(Vertex &v)
		{
			if(v.y != y)
			{
				return true;
			}
			else
			{
				if(y == 0 || width-1)
					return false;
				else
					return v.x != x;
			}
		}
	};
private:
	void findArt(Vertex &  v);
	std::vector< Vertex*> vertices;
	std::vector< Vertex*> artpoints;
	std::vector< Vertex*> adjacent(Vertex & v);
	void addVertices(int,int);
	bool addedNorth;
	bool addedSouth;
};

} /* namespace tron */
#endif /* CHAMBER_H_ */
