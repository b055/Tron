/*
 * Voronoi.cpp
 *
 * Created on 25th aughust 2012
 * class to calculate the voronoi number
 */

#include "Voronoi.h"
namespace tron{
Voronoi::Voronoi(Grid * grid,int width):width(width)
{

	this->grid = grid;
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
		for(int j = 0;j<width;j++)
			if((*grid)[0][j] !=0){
				if(0 == this->grid->getPlayerOneHeadY())
				{
					for(int i = 0;i<width;i++)
					{
						one[0][i] = 0;
					}
				}
				else if(0 == this->grid->getPlayerTwoHeadY())
				{
					for(int i = 0;i<width;i++)
					{
						two[0][i] = 0;
					}
				}
				else{
					for(int i = 0;i<width;i++)
					{
						(*grid)[0][i] = 1;
					}
				}
				break;
			}
		for(int j = 0;j<width;j++)
			if((*grid)[width-1][j] !=0){
				if(width-1 == this->grid->getPlayerOneHeadY())
				{
					for(int i = 0;i<width;i++)
					{
						one[width-1][i] = 0;
					}
				}
				else if(width-1 == this->grid->getPlayerTwoHeadY())
				{
					for(int i = 0;i<width;i++)
					{
						two[width-1][i] = 0;
					}
				}
				else
				{
					for(int i = 0;i<width;i++)
					{
						(*grid)[width-1][i] = 1;
					}
				}
				break;
			}
		one[grid->getPlayerOneHeadY()][grid->getPlayerOneHeadX()]=0;
		two[grid->getPlayerTwoHeadY()][grid->getPlayerTwoHeadX()] = 0;
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

int Voronoi::countArea(int tempX, int tempY,std::vector<std::vector< int> > & mat){
	if(tempX>-1 && tempY<width && tempX<width && tempY >-1) // y's away from the poles
		if(mark[tempY][tempX]== 0)
			if((*grid)[tempY][tempX] == 0)
			{
				this->co++;
				int a = neighbourMin(tempX,tempY,mat) + 1;
				if(tempY == 0 || tempY == width-1)
				{
					if(tempY == grid->getPlayerOneHeadY())//player one
					{
						if(two[tempY][0] == 0)
							for(int i = 0;i<width;i++)
							{
								one[tempY][i] = VAR;
							}
					}
					else if(tempY == grid->getPlayerTwoHeadY())//player two
					{
						if(one[tempY][0] == 0)
							for(int i = 0;i<width;i++)
							{
								two[tempY][i] = VAR;
							}
					}
					else
					{
						if(mat[tempY][tempX]>a)
							for(int i = 0;i<width;i++)
							{
								mat[tempY][i] = a;
							}
					}
				}
				else
				{
					mat[tempY][tempX] = mat[tempY][tempX]>a?a:mat[tempY][tempX];//%VAR;
				}
				mark[tempY][tempX] = 1;
				surroundCheck(tempX,tempY,mat);
			}

	return co;
 }
int Voronoi::countLeft(int tempX, int tempY,std::vector<std::vector< int> > &mat){
	if(tempX>-1 && tempY<width && tempX<width && tempY >-1) // y's away from the poles
		if(mark[tempY][tempX]== 0)
			if((*grid)[tempY][tempX] == 0)
			{
				this->co++;
				int a = neighbourMin(tempX,tempY,mat) + 1;
				if(tempY == 0 || tempY == width-1)
				{
					if(tempY == grid->getPlayerOneHeadY())//player one
					{
						if(two[tempY][0] == 0)
							for(int i = 0;i<width;i++)
							{
								one[tempY][i] = VAR;
							}
					}
					else if(tempY == grid->getPlayerTwoHeadY())//player two
					{
						if(one[tempY][0] == 0)
							for(int i = 0;i<width;i++)
							{
								two[tempY][i] = VAR;
							}
					}
					else
					{
						if(mat[tempY][tempX]>a)
							for(int i = 0;i<width;i++)
							{
								mat[tempY][i] = a;
							}
					}
				}
				else
				{
					mat[tempY][tempX] = mat[tempY][tempX]>a?a:mat[tempY][tempX];//%VAR;
				}
				mark[tempY][tempX] = 1;
				surroundLeft(tempX,tempY,mat);
			}

	return co;
 }
int Voronoi::countTop(int tempX, int tempY,std::vector<std::vector< int> >&mat){
	if(tempX>-1 && tempY<width && tempX<width && tempY >-1) // y's away from the poles
		if(mark[tempY][tempX]== 0)
			if((*grid)[tempY][tempX] == 0)
			{
				this->co++;
				int a = neighbourMin(tempX,tempY,mat) + 1;
				if(tempY == 0 || tempY == width-1)
				{
					if(tempY == grid->getPlayerOneHeadY())//player one
					{
						if(two[tempY][0] == 0)
							for(int i = 0;i<width;i++)
							{
								one[tempY][i] = VAR;
							}
					}
					else if(tempY == grid->getPlayerTwoHeadY())//player two
					{
						if(one[tempY][0] == 0)
							for(int i = 0;i<width;i++)
							{
								two[tempY][i] = VAR;
							}
					}
					else
					{
						if(mat[tempY][tempX]>a)
							for(int i = 0;i<width;i++)
							{
								mat[tempY][i] = a;
							}
					}
				}
				else
				{
					mat[tempY][tempX] = mat[tempY][tempX]>a?a:mat[tempY][tempX];//%VAR;
				}
				mark[tempY][tempX] = 1;
				surroundTop(tempX,tempY,mat);
			}

	return co;
 }
int Voronoi::countBottom(int tempX, int tempY,std::vector<std::vector< int> >&mat){
	if(tempX>-1 && tempY<width && tempX<width && tempY >-1) // y's away from the poles
		if(mark[tempY][tempX]== 0)
			if((*grid)[tempY][tempX] == 0)
			{
				this->co++;
				int a = neighbourMin(tempX,tempY,mat) + 1;

				if(tempY == 0 || tempY == width-1)
				{
					if(tempY == grid->getPlayerOneHeadY())//player one
					{
						if(two[tempY][0] == 0)
							for(int i = 0;i<width;i++)
							{
								one[tempY][i] = VAR;
							}
					}
					else if(tempY == grid->getPlayerTwoHeadY())//player two
					{
						if(one[tempY][0] == 0)
							for(int i = 0;i<width;i++)
							{
								two[tempY][i] = VAR;
							}
					}
					else
					{
						if(mat[tempY][tempX]>a)
							for(int i = 0;i<width;i++)
							{
								mat[tempY][i] = a;
							}
					}
				}
				else
				{
					mat[tempY][tempX] = mat[tempY][tempX]>a?a:mat[tempY][tempX];//%VAR;
				}
				mark[tempY][tempX] = 1;
				surroundBottom(tempX,tempY,mat);
			}
	return co;
 }
void Voronoi::surroundBottom(int xCoord, int yCoord,std::vector<std::vector< int> >&mat)
{
	countBottom(xCoord,yCoord+1,mat);
	countBottom(xCoord,yCoord-1,mat);
	countBottom((xCoord+1)%width,yCoord,mat);//recursively go through all boxes
	countBottom((xCoord-1+width)%width,yCoord,mat);
 }
 //checks the boxes around current towards the right
void Voronoi::surroundCheck(int xCoord, int yCoord,std::vector<std::vector< int> >&mat)
{
	  countArea((xCoord+1)%width,yCoord,mat);//recursively go through all boxes
	  countArea((xCoord-1+width)%width,yCoord,mat);
	  countArea(xCoord,yCoord+1,mat);
	  countArea(xCoord,yCoord-1,mat);
 }
void Voronoi::surroundLeft(int xCoord, int yCoord,std::vector<std::vector< int> >&mat)
{
	//recursively go through all boxes
	countLeft((xCoord-1+width)%width,yCoord,mat);
	countLeft((xCoord+1)%width,yCoord,mat);
	countLeft(xCoord,yCoord+1,mat);
	countLeft(xCoord,yCoord-1,mat);
}
void Voronoi::surroundTop(int xCoord, int yCoord,std::vector<std::vector< int> >&mat)
{
	//recursively go through all boxes

	countTop(xCoord,yCoord-1,mat);
	countTop(xCoord,yCoord+1,mat);
	countTop((xCoord-1+width)%width,yCoord,mat);
	countTop((xCoord+1)%width,yCoord,mat);
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
	//if(result == VAR)
	//	return 0;
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
float* Voronoi::calculate(int player)
{
	float* result = new float[2];
	if(grid->endState())
	{
		if(grid->getLoser() == 1)
		{
			result[0] = -9999;
			result[1] = 9999;
		}
		else if(grid->getLoser() ==3)
		{
			result[0] = 9999;
			result[1] = -9999;
		}
		else
		{
			std::cout<<"could not determine the loser\n";
			std::cout<<grid->printGrid()<<"\n";
		}
		return result;
	}

	surroundBottom(grid->getPlayerOneHeadX(),grid->getPlayerOneHeadY(),one);this->resetMark();

	surroundTop(grid->getPlayerOneHeadX(),grid->getPlayerOneHeadY(),one);this->resetMark();
	surroundCheck(grid->getPlayerOneHeadX(),grid->getPlayerOneHeadY(),one);this->resetMark();
	surroundLeft(grid->getPlayerOneHeadX(),grid->getPlayerOneHeadY(),one);this->resetMark();

//	last(one);this->resetMark();

//	std::cout<<this->outputOne();
	//std::cout<<std::endl;

	surroundLeft(grid->getPlayerTwoHeadX(),grid->getPlayerTwoHeadY(),two);this->resetMark();
	surroundBottom(grid->getPlayerTwoHeadX(),grid->getPlayerTwoHeadY(),two);this->resetMark();
	surroundTop(grid->getPlayerTwoHeadX(),grid->getPlayerTwoHeadY(),two);this->resetMark();
	surroundCheck(grid->getPlayerTwoHeadX(),grid->getPlayerTwoHeadY(),two);this->resetMark();
//	last(two);this->resetMark();

//	std::cout<<this->outputTwo();
	//std::cout<<std::endl;

	getMerge(player);
	vor[grid->getPlayerOneHeadY()][grid->getPlayerOneHeadX()]=0;
	vor[grid->getPlayerTwoHeadY()][grid->getPlayerTwoHeadX()]=0;
	//std::cout<<this->outputVoronoi();
	int one = 0;
	int two = 0;
	int onered = 0;
	int oneblack = 0;
	int twored = 0;
	int twoblack = 0;
	/*for(int i = 1;i<width-1;i++)
	{
		for(int j = 0;j<width;j++)
		{
			if(vor[i][j]<0)
			{
				one++;
				if((i % 2 == 0 && j % 2 == 0)||( i % 2 == 1 && j % 2 == 1))
				{
					onered++;
				}
				else{
					oneblack++;
				}
			}
			else if(vor[i][j]>0)
			{
				two++;
				if((i % 2 == 0 && j % 2 == 0)||( i % 2 == 1 && j % 2 == 1))
				{
					twored++;
				}
				else {
					twoblack++;
				}
			}
		}
	}*/
	//std::cout<<"before chambers "<<one<<"  "<<two<<std::endl;
	Chamber a(this->vor,width,1,grid->getPlayerOneHeadX(),grid->getPlayerOneHeadY());
	std::vector<std::vector< int> > temp1;
	one = a.calculate(grid->getPlayerOneHeadX(),grid->getPlayerOneHeadY(),temp1);

	Chamber b(this->vor,width,3,grid->getPlayerTwoHeadX(),grid->getPlayerTwoHeadY());
	std::vector<std::vector< int> > temp3;
	two  = b.calculate(grid->getPlayerTwoHeadX(),grid->getPlayerTwoHeadY(),temp3);

	//std::cout<<"after chambers "<<one<<"  "<<two<<std::endl;
	if(vor[0][0]<0)
		one++;
	else if(vor[0][0]>0)
		two++;
	if(vor[width-1][0]<0)
		one++;
	else if(vor[width-1][0]>0)
		two++;

	one -= abs(onered-oneblack);// meed to check thhes red black squares and whether they are actually valid
	two -= abs(twored - twoblack);
	if(one == 0 && two == 0)
	{
		result[0] = 0;result[1] = 0;
	}
	else
	{
		result[0] = one-two;
		result[1] = two-one;
	}
	return result;
}
}
