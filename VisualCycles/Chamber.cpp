/*
 * Chamber.cpp
 *
 *  Created on: Sep 5, 2012
 *      Author: Student
 */

#include "Chamber.h"

namespace tron {

Chamber::Chamber(std::vector<std::vector< int> > *grid,int width, int digit,int x,int y)
:addedNorth(false),addedSouth(false),NorthValue(false),rootChildren(0),SouthValue(false),width(width),digit(digit)
{
	this->grid = grid;
	for(int i = 0;i<width;i++)
	{
		std::vector<int> temp;
		for(int j = 0;j<width;j++)
		{
			temp.push_back(0);
		}
		mark.push_back(temp);
		sol.push_back(temp);
	}

	counter = 1;
	int rightx,leftx,topy,bottomy;
	rightx = (x+1)%width;
	leftx = (x-1+width)% width;
	topy = y-1;
	bottomy = y+1;
	vertices.push_back(new Vertex(x,y));
	if((*grid)[y][rightx] != 0 )
		addVertices(rightx,y);
	if( (*grid)[y][leftx]!=0 )
		addVertices(leftx,y);
	if(topy != -1)
		if((*grid)[topy][x] != 0)
			addVertices(x,topy);
	if(bottomy != width)
		if((*grid)[bottomy][x]!= 0)
			addVertices(x,bottomy);
	value = 0;
	if(vertices.size()>0)
	{
		findArt(*vertices[0]);
		if(rootChildren>1){
			artpoints.push_back(vertices[0]);
		}
		//value = countChildren(vertices[0]);
		
		for(int i = 0;i<width;i++)
			for(int j = 0;j<width;j++)
				mark[i][j] = 0;	
		value = breadth(vertices[0]->x,vertices[0]->y,digit); //seems to perform better
		//printMark();
		//std::cout<<std::endl<<printSol();
	}	
}
Chamber::~Chamber() {
	// handled by the standard vectors
	for(int i = 0; i<vertices.size();i++)
		delete vertices[i];

}
std::string Chamber::printSol()
{
	std::stringstream ss;
	for(int i = 0 ;i<width;i++){
		for(int j =0;j<width;j++)
			ss<<sol[i][j]<<" ";
		ss<<std::endl;
	}
	return ss.str();
}

int Chamber::breadth( int rootx,int rooty, int digit)
{	
	std::queue<std::vector< int> > queue;
	std::vector<int> first;
	first.push_back(rootx);
	first.push_back(rooty);
	queue.push(first);
	bool northPush =false;
	int value = 0;
	std::vector<std::vector< int> > artsinpath;
	while(!queue.empty())
	{
		int x,y;
		std::vector<std::vector< int> >adj;
		std::vector<int> current = queue.front();
		x = current[0];
		y = current[1];
		queue.pop();
		std::vector<int> top;
		std::vector<int> bottom;
		std::vector<int> left;
		std::vector<int> right;
		//gets the adjacents
		if(y-1 >-1 && y -1 < width-2 && isValid(x,y-1,digit))
		{
			top.push_back(x);
			top.push_back(y-1);
			adj.push_back(top);
		}
		else if(y-1 == width-2 )
		{
			for(int i = 0;i<width;i++)
			{
				if(isValid(i,width-2,digit))
				{
					std::vector<int> temp;
					temp.push_back(i);
					temp.push_back(width-2);
					adj.push_back(temp);
				}
			}
		}
		if(y+1 < width && y+1 >1 && isValid(x,y+1,digit))
		{
			bottom.push_back(x);
			bottom.push_back(y+1);
			adj.push_back(bottom);
		}
		else if(y+1 == 1)
		{
			for(int i = 0;i<width;i++)
			{
				if(isValid(i,1,digit))
				{
					std::vector<int> temp;
					temp.push_back(i);
					temp.push_back(1);
					adj.push_back(temp);
				}
			}
		}
		if(isValid((x-1+width)%width,y,digit))
		{
			left.push_back((x-1+width)%width);
			left.push_back(y);
			adj.push_back(left);
		}
		if(isValid((x+1)%width,y,digit))
		{
			right.push_back((x+1)%width);
			right.push_back(y);
			adj.push_back(right);
		}

/* finished gettin all the adjacents */
		for(int i =0;i<adj.size();i++)
		{
			
			if(isValid(adj[i][0],adj[i][1],digit) && mark[adj[i][1]][adj[i][0]] == 0)
			{
				if(adj[i][1] == 0 || adj[i][1] == width-1)
					for(int j = 0;j<width;j++)
						mark[adj[i][1]][j] = 1;
				mark[adj[i][1]][adj[i][0]] = 1;	
				if(isArtPoint(adj[i][0],adj[i][1]))
				{
					std::vector<int> vect;
					vect.push_back(adj[i][0]);
					vect.push_back(adj[i][1]);
					artsinpath.push_back(vect);								
				}
				else
				{					
					queue.push(adj[i]);
					value++;
					//sol[adj[i][1]][adj[i][0]] = value;
				}
			}
		}
	}
	int max = 0;
	for(int i = 0;i<artsinpath.size();i++)
	{		
		int temp = breadth(artsinpath[i][0],artsinpath[i][1],digit);
		//sol[artsinpath[i][1]][artsinpath[i][0]] = temp;
		if(max<temp)
		{
			max = temp;
			//std::cout<<artsinpath[i][0]<<"  "<<artsinpath[i][1]<<"  "<<max<<std::endl;	
		}
	}		
	return value+max;
}
bool Chamber::isValid(int x, int y ,int digit)
{
	if(digit == 1)
		return (*grid)[y][x]<0;
	else 
		return (*grid)[y][x]>0;
}


void Chamber::addVertices(int x, int y)
{
	if(digit == 1 && y>-1 && y<width && (*grid)[y][x]<0 && mark[y][x] == 0)
	{
		if(y == 0)
		{
			if(!addedNorth)
			{
				Vertex * v = new Vertex(x,y);
				vertices.push_back(v);
				addedNorth= true;
				for(int i = 0;i<width;i++)
					mark[0][i] = 1;
				for(int i = 0;i<width;i++)
					addVertices(i,y+1);
			}
		}
		else if(y == width-1)
		{
			if(!addedSouth)
			{
				Vertex *v = new Vertex(x,y);
				vertices.push_back(v);
				addedSouth= true;
				for(int i = 0;i<width;i++)
					mark[width-1][i] = 1;
				for(int i = 0;i<width;i++)
					addVertices(i,y-1);
			}
		}
		else
		{
			mark[y][x] = 1;
			Vertex*v = new Vertex(x,y);
			vertices.push_back(v);
			addVertices(x,y+1);
			addVertices(x,y-1);
			addVertices((x+1)%width,y);
			addVertices((x-1+width)%width,y);
		}
	}
	else if(digit == 3 && y>-1 && y<width && (*grid)[y][x]>0 && mark[y][x] == 0 )
	{
		if(y == 0)
		{
			if(!addedNorth)
			{
				Vertex * v = new Vertex(x,y);
				vertices.push_back(v);
				addedNorth= true;
				for(int i = 0;i<width;i++)
					mark[0][i] = 1;
				for(int i = 0;i<width;i++)
					addVertices(i,1);
			}
		}
		else if(y == width-1)
		{
			if(!addedSouth)
			{
				Vertex *v = new Vertex(x,y);
				vertices.push_back(v);
				addedSouth= true;
				for(int i = 0;i<width;i++)
					mark[width-1][i] = 1;
				for(int i = 0;i<width;i++)
					addVertices(i,y-1);
			}
		}
		else
		{
			mark[y][x] = 1;
			Vertex*v = new Vertex(x,y);
			vertices.push_back(v);
			addVertices(x,y+1);
			addVertices(x,y-1);
			addVertices((x+1)%width,y);
			addVertices((x-1+width)%width,y);
		}
	}

}

void Chamber::printMark()
{
	for(int i = 0;i< width;i++)
	{
		for(int j = 0; j<width;j++)
		{
			//std::cout<<mark[i][j]<<" ";
		}
		//std::cout<<std::endl;
	}
}

// all these points (x,y) are valid paths-> already checked
bool Chamber::isArtPoint(int x, int y)
{
	//std::cout<<x<<"  "<<y<<std::endl;
	for(unsigned int i =0;i<artpoints.size();i++)
	{
		if(y == artpoints[i]->y)
		{
			if(y == 0 || y == width-1)
				return true;
			else
				return x == artpoints[i]->x;
		}
	}
	return false;
}


//finds the articulation points
void Chamber::findArt(Vertex& v)
{
	v.visited = true;
	v.low = v.num = counter++;
	std::vector< Vertex*> adj = adjacent(v);
	for (unsigned int i = 0;i<adj.size();i++)
	{
		Vertex * w = adj[i];
		if(!w->visited)
		{
			
			w->parent = &v;
			v.children.push_back(w);
			if(v.num == 1)
				rootChildren++;
			findArt(*w);
			if(w->low >= v.num)
			{
				artpoints.push_back(&v);
				//std::cout<<v.x<<" "<<v.y<<" is an articulation point\n";
			}
			v.low = v.low<w->low?v.low:w->low;
		}
		else
		{
			if(v.num == 1 || *(v.parent) != *w)
			{
				v.low = v.low<w->num?v.low:w->num;
			}
		}
	}
}

//finds the points adjacent to v
std::vector< tron::Chamber::Vertex*> Chamber::adjacent(Vertex& v)
{
	std::vector< Vertex*> adj;
	int rightx,leftx,topy,bottomy;
	rightx = (v.x+1)%width;
	leftx = (v.x-1+width)% width;
	topy = v.y-1;
	bottomy = v.y+1;
	if(topy ==-1)
	{
		for(unsigned int i = 1;i<vertices.size();i++)
		{
			if(vertices[i]->y == 1){	
				adj.push_back(vertices[i]);
			}
		}
	}
	else if(bottomy == width)
		for(unsigned int i = 1;i<vertices.size();i++)
		{
			if(vertices[i]->y == width-1)
				adj.push_back(vertices[i]);
		}
	else if(topy == 0)
	{
		for(unsigned int i = 1;i<vertices.size();i++)
		{
			if(vertices[i]->x ==rightx && vertices[i]->y == v.y)//right neighbour
			{
				adj.push_back(vertices[i]);
			}
			else if(vertices[i]->x == leftx && vertices[i]->y == v.y)//left neighbour
			{
				adj.push_back(vertices[i]);
			}
			else if(vertices[i]->y == topy)//top neighbour
			{
				adj.push_back(vertices[i]);
			}
			else if(vertices[i]->y == bottomy && vertices[i]->x == v.x)//bottom neighbour
			{
				adj.push_back(vertices[i]);
			}
		}
	}
	else if(bottomy == width-1)
	{
		for(unsigned int i = 1;i<vertices.size();i++)
			{
				if(vertices[i]->x ==rightx && vertices[i]->y == v.y)//right neighbour
				{
					adj.push_back(vertices[i]);
				}
				else if(vertices[i]->x == leftx && vertices[i]->y == v.y)//left neighbour
				{
					adj.push_back(vertices[i]);
				}
				else if(vertices[i]->y == topy && vertices[i]->x == v.x)//top neighbour
				{
					adj.push_back(vertices[i]);
				}
				else if(vertices[i]->y == bottomy)//bottom neighbour
				{
					adj.push_back(vertices[i]);
				}
			}
	}
	else

		for(unsigned int i = 1;i<vertices.size();i++)
		{
			if(vertices[i]->x ==rightx && vertices[i]->y == v.y)//right neighbour
			{
				adj.push_back(vertices[i]);
			}
			else if(vertices[i]->x == leftx && vertices[i]->y == v.y)//left neighbour
			{
				adj.push_back(vertices[i]);
			}
			else if(vertices[i]->y == topy && vertices[i]->x == v.x)//top neighbour
			{
				adj.push_back(vertices[i]);
			}
			else if(vertices[i]->y == bottomy && vertices[i]->x == v.x)//bottom neighbour
			{
				adj.push_back(vertices[i]);
			}
		}
	return adj;
}
} /* namespace tron */
