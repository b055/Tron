/*
 * Voronoi.cpp
 *
 * Created on 25th aughust 2012
 * class to calculate the voronoi number
 */

#include "Voronoi.h"
namespace tron{
Voronoi::Voronoi(Grid * const gridPointer,int width):width(width)
{
	this->grid = new Grid(width);
	(*this->grid) = *gridPointer;
	if(grid->getLoser() == 0)
	{

		VAR = 999;
		co = 0;

		for(int i = 0;i<width;i++)
		{
			std::vector<int> temp;
			std::vector<int> other;
			for(int j = 0;j<width;j++)
			{
				temp.push_back(0);
				other.push_back(VAR);
			}
			mark.push_back(temp);
			vor.push_back(temp);
			one.push_back(other);
			two.push_back(other);
		}


		one[this->grid->getPlayerOneHeadY()][this->grid->getPlayerOneHeadX()]=0;
		two[this->grid->getPlayerTwoHeadY()][this->grid->getPlayerTwoHeadX()] = 0;
		if(this->grid->getPlayerOneHeadY() == 0 || this->grid->getPlayerOneHeadY() == width-1)
		{
			for(int i =0;i<width;i++)
				one[this->grid->getPlayerOneHeadY()][i]= 0;
		}
		if(this->grid->getPlayerTwoHeadY() == 0 || this->grid->getPlayerTwoHeadY() == width-1)
		{
			for(int i =0;i<width;i++)
				one[this->grid->getPlayerTwoHeadY()][i]= 0;
		}
	}
}
void Voronoi::resetVor()
{
	for(int i = 0;i<width;i++)
		for(int j = 0;j<width;j++){
			mark[i][j] = 0;
		}
	co = 0;
}
void Voronoi::resetMark()
{
	for(int i = 0;i<width;i++)
		for(int j = 0;j<width;j++){
			mark[i][j] = 0;
		}
}
void Voronoi::resetOneandTwo()
{
#pragma omp parallel for
	for(int i = 0;i<width;i++)
			for(int j = 0;j<width;j++){
				one[i][j] = VAR;
				two[i][j] = VAR;
			}
}
Voronoi::~Voronoi() {
	//handled by the standard vectors
}

 //counts the empty boxes

void Voronoi::breadth( int digit)
{
	std::queue<std::vector< int> > queue;
	std::vector<int> first;
	std::vector<std::vector< int> > *mat;
	if(digit == 1)
	{
		first.push_back(grid->getPlayerOneHeadX());
		first.push_back(grid->getPlayerOneHeadY());
		mat = &one;
	}
	else
	{
		first.push_back(grid->getPlayerTwoHeadX());
		first.push_back(grid->getPlayerTwoHeadY());
		mat = &two;
	}
	queue.push(first);
	bool northPush =false;
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
		if(y-1 >-1 && y -1 < width-2 && (*grid)[y-1][x] == 0)
		{
			top.push_back(x);
			top.push_back(y-1);
			adj.push_back(top);
		}
		else if(y-1 == width-2 )
		{
			for(int i = 0;i<width;i++)
			{
				if((*grid)[width-2][i] == 0)
				{
					std::vector<int> temp;
					temp.push_back(i);
					temp.push_back(width-2);
					adj.push_back(temp);
				}
			}
		}
		if(y+1 < width && y+1 >1 && (*grid)[y+1][x] ==0)
		{
			bottom.push_back(x);
			bottom.push_back(y+1);
			adj.push_back(bottom);
		}
		else if(y+1 == 1)
		{
			for(int i = 0;i<width;i++)
			{
				if((*grid)[1][i] == 0)
				{
					std::vector<int> temp;
					temp.push_back(i);
					temp.push_back(1);
					adj.push_back(temp);
				}
			}
		}
		if((*grid)[y][(x-1+width)%width] ==0)
		{
			left.push_back((x-1+width)%width);
			left.push_back(y);
			adj.push_back(left);
		}
		if((*grid)[y][(x+1+width)%width] ==0)
		{
			right.push_back((x+1)%width);
			right.push_back(y);
			adj.push_back(right);
		}
		for(int i =0;i<adj.size();i++)
		{
			if((*grid)[adj[i][1]][adj[i][0]] ==0  && mark[adj[i][1]][adj[i][0]] == 0 )
			{

				queue.push(adj[i]);
				if(adj[i][1] == 0 || adj[i][1] == width-1)
					for(int j = 0;j<width;j++)
						mark[adj[i][1]][j] = 1;
				else
					mark[adj[i][1]][adj[i][0]] = 1;

			}

		}
		int min = VAR;
		if(!northPush)
		{
			(*mat)[current[1]][current[0]]= 0;
			northPush = true;
		}
		else if(current[1] == 0 || current[1] == width-1)
		{
			int tempy;
			if(current[1] == 0)	tempy = 1;
			else tempy = width-2;
			for(int i =0;i<width;i++)
				min = min>(*mat)[tempy][i]?(*mat)[tempy][i]:min;
			if(min == VAR)
				for(int i = 0;i<width;i++)
					if((*grid)[tempy][i]==0)
					{
						min =0;break;
					}
			for(int i =0;i<width;i++)
				if((*grid)[current[1]][i]==0)
					(*mat)[current[1]][i] = min+1;
		}
		else
			(*mat)[current[1]][current[0]] =neighbourMin(current[0],current[1],*mat)+1;
	}

}
int Voronoi::neighbourMin(int x,int y,std::vector<std::vector< int> >& mat)
{
	int result = VAR;
	int i,j;

	i = (x-1+width)%width; j =y;
	if(i>-1 && i<width&& j>-1 && j<width)
	{
		if(mat[j][i]<result)
			result = mat[j][i];
	}
	i = (x+1)%width;
	if(i>-1 && i<width&& j>-1 && j<width)
	{
		if(mat[j][i]<result)
			result = mat[j][i];
	}
	i = x; j = y-1;
	if(i>-1 && i<width&& j>-1 && j<width)
	{
		if(mat[j][i]<result)
			result = mat[j][i];
	}
	j = y+1;
	if(i>-1 && i<width&& j>-1 && j<width)
	{
		if(mat[j][i]<result)
			result = mat[j][i];
	}
	if(result == VAR)
		return 0;
	return result;
}
std::string Voronoi::outputOne()
{
	std::stringstream ss;
	ss<<"this is one "<<this->grid->getPlayerOneHeadX()<<" "<<grid->getPlayerOneHeadY()<<std::endl;
	for(int i = 0;i<width;i++)
	{
		for(int j = 0;j<width;j++)
		{
			ss<<one[i][j]<<"\t";
		}
		ss<<std::endl;
	}
	return ss.str();
}
std::string Voronoi::outputTwo()
{
	std::stringstream ss;
	ss<<"this is two "<<this->grid->getPlayerTwoHeadX()<<" "<<grid->getPlayerTwoHeadY()<<std::endl;
	for(int i = 0;i<width;i++)
	{
		for(int j = 0;j<width;j++)
		{
			ss<<two[i][j]<<"\t";
		}
		ss<<std::endl;
	}
	return ss.str();
}
std::string Voronoi::outputVoronoi()
{
	std::stringstream ss;
	ss<<"this is the voronoi "<<std::endl;
	for(int i = 0;i<width;i++)
	{
		for(int j = 0;j<width;j++)
		{
			ss<<vor[i][j]<<"\t";
		}
		ss<<std::endl;
	}
	return ss.str();
}
void Voronoi::getMerge(int turn){
	for(int i = 0;i<width;i++)
		for(int j = 0;j<width;j++)
			vor[i][j] = (one[i][j]-two[i][j])%VAR;

}
int* Voronoi::calculate(int player)
{
	int* result = new int[2];

	breadth(1);
	resetMark();
	breadth(3);

	getMerge(player);
	vor[grid->getPlayerOneHeadY()][grid->getPlayerOneHeadX()]=0;
	vor[grid->getPlayerTwoHeadY()][grid->getPlayerTwoHeadX()]=0;
	

	Chamber a(&(this->vor),width,1,grid->getPlayerOneHeadX(),grid->getPlayerOneHeadY());

	int one = a.getValue();

	Chamber b(&(this->vor),width,3,grid->getPlayerTwoHeadX(),grid->getPlayerTwoHeadY());

	int two  = b.getValue();
	
	/*
	int one_excess = abs(onered-oneblack);// meed to check thhes red black squares and whether they are actually valid
	int two_excess = abs(twored - twoblack);

	if(vor[0][0] < 0) one_spot++; else if(vor[0][0]>0) two_spot++;
	if(vor[width-1][0]<0) one_spot++; else if(vor[width-1][0]>0) two_spot++;


	if(one_excess/(float)one_spot >=0.1) // need to think this part out
		one *= (float)one_excess/one_spot;
	if(two_excess/(float)two_spot >=0.1)
		two *= (float)two_excess/two_spot;
	*/

	result[0] = one-two;
	result[1] = two-one;
	
	return result;
}

}
