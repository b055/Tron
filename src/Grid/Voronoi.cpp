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

	VAR = 999;
	co = 0;
	pos.resize(grid->getGrid().size());
	copy(grid->getGrid().begin(),grid->getGrid().end(),pos.begin());
	this->grid = *grid;
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
		if(this->grid.getGrid()[0][j] !=0){
			if(0 == this->grid.getPlayerOneHeadY())
			{
				for(int i = 0;i<width;i++)
				{
					one[0][i] = 0;
				}
			}
			else if(0 == this->grid.getPlayerTwoHeadY())
			{
				for(int i = 0;i<width;i++)
				{
					two[0][i] = 0;
				}
			}
			else{
				for(int i = 0;i<width;i++)
				{
					pos[0][i] = 1;
				}
			}
			break;
		}
	for(int j = 0;j<width;j++)
		if(this->grid.getGrid()[width-1][j] !=0){
			if(width-1 == this->grid.getPlayerOneHeadY())
			{
				for(int i = 0;i<width;i++)
				{
					one[width-1][i] = 0;
				}
			}
			else if(width-1 == this->grid.getPlayerTwoHeadY())
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
					pos[width-1][i] = 1;
				}
			}
			break;
		}
	//std::cout<<"here's the one coordinate "<<grid->getPlayerOneHeadY()<<" "<<grid->getPlayerOneHeadX()<<std::endl;
	one[grid->getPlayerOneHeadY()][grid->getPlayerOneHeadX()]=0;
	two[grid->getPlayerTwoHeadY()][grid->getPlayerTwoHeadX()] = 0;
}
void Voronoi::setGrid(Grid & newgrid)
{
	grid = newgrid;
	pos.resize(newgrid.getGrid().size());
	copy(grid.getGrid().begin(),grid.getGrid().end(),pos.begin());

	resetOneandTwo();
	//sets the pos matrix if the poles have been occupied
	for(int j = 0;j<width;j++)
		if(grid.getGrid()[0][j] !=0){
			if(0 == grid.getPlayerOneHeadY())
			{
				for(int i = 0;i<width;i++)
				{
					one[0][i] = 0;
				}
			}
			else if(0 == grid.getPlayerTwoHeadY())
			{
				for(int i = 0;i<width;i++)
				{
					two[0][i] = 0;
				}
			}
			else{
				for(int i = 0;i<width;i++)
				{
					pos[0][i] = 1;
				}
			}
			break;
		}
	for(int j = 0;j<width;j++)
		if(grid.getGrid()[width-1][j] !=0){
			if(width-1 == grid.getPlayerOneHeadY())
			{
				for(int i = 0;i<width;i++)
				{
					one[width-1][i] = 0;
				}
			}
			else if(width-1 == grid.getPlayerTwoHeadY())
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
					pos[width-1][i] = 1;
				}
			}
			break;
		}
	co = 0;
	resetVor();
	resetMark();
	pos[grid.getPlayerOneHeadY()][grid.getPlayerOneHeadX()] = 0;
	pos[grid.getPlayerTwoHeadY()][grid.getPlayerTwoHeadX()] = 0;
	one[grid.getPlayerOneHeadY()][grid.getPlayerOneHeadX()]=0;
	two[grid.getPlayerTwoHeadY()][grid.getPlayerTwoHeadX()] = 0;
}
Voronoi::Voronoi(int width):grid(*new Grid(width)),width(width)
{

}
void Voronoi::resetVor()
{
#pragma omp parallel for
	for(int i = 0;i<width;i++)
		for(int j = 0;j<width;j++){
			mark[i][j] = 0;
		}
	co = 0;
}
void Voronoi::resetMark()
{
#pragma omp parallel for
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
	for(int i = 0;i<width;i++)
	{
		delete[] &vor[i];
		delete[] &mark[i];
		//delete[] &pos[i];
		delete[] &one[i];
		delete[] &two[i];
	}
	delete[] &vor;
	delete[] &mark;
	//delete[] &pos;
	delete[] &one;
	delete[] &two;
}

 //counts the empty boxes

int Voronoi::countArea(int tempX, int tempY,std::vector<std::vector< int> > & mat){
	if(tempX>-1 && tempY<width && tempX<width && tempY >-1) // y's away from the poles
		if(mark[tempY][tempX]== 0)
			if(pos[tempY][tempX] == 0)
			{
				this->co++;
				int a = neighbourMin(tempX,tempY,mat) + 1;
				if(tempY == 0 || tempY == width-1)
				{
					if(tempY == grid.getPlayerOneHeadY())//player one
					{
						if(two[tempY][0] == 0)
							for(int i = 0;i<width;i++)
							{
								one[tempY][i] = VAR;
							}
					}
					else if(tempY == grid.getPlayerTwoHeadY())//player two
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
			if(pos[tempY][tempX] == 0)
			{
				this->co++;
				int a = neighbourMin(tempX,tempY,mat) + 1;
				if(tempY == 0 || tempY == width-1)
				{
					if(tempY == grid.getPlayerOneHeadY())//player one
					{
						if(two[tempY][0] == 0)
							for(int i = 0;i<width;i++)
							{
								one[tempY][i] = VAR;
							}
					}
					else if(tempY == grid.getPlayerTwoHeadY())//player two
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
			if(pos[tempY][tempX] == 0)
			{
				this->co++;
				int a = neighbourMin(tempX,tempY,mat) + 1;
				if(tempY == 0 || tempY == width-1)
				{
					if(tempY == grid.getPlayerOneHeadY())//player one
					{
						if(two[tempY][0] == 0)
							for(int i = 0;i<width;i++)
							{
								one[tempY][i] = VAR;
							}
					}
					else if(tempY == grid.getPlayerTwoHeadY())//player two
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
			if(pos[tempY][tempX] == 0)
			{
				this->co++;
				int a = neighbourMin(tempX,tempY,mat) + 1;

				if(tempY == 0 || tempY == width-1)
				{
					if(tempY == grid.getPlayerOneHeadY())//player one
					{
						if(two[tempY][0] == 0)
							for(int i = 0;i<width;i++)
							{
								one[tempY][i] = VAR;
							}
					}
					else if(tempY == grid.getPlayerTwoHeadY())//player two
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
	ss<<"this is one "<<this->grid.getPlayerOneHeadX()<<" "<<grid.getPlayerOneHeadY()<<std::endl;
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
	ss<<"this is two "<<this->grid.getPlayerTwoHeadX()<<" "<<grid.getPlayerTwoHeadY()<<std::endl;
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
#pragma omp parallel for
	for(int i = 0;i<width;i++)
		for(int j = 0;j<width;j++)
			vor[i][j] = (one[i][j]%VAR-two[i][j]%VAR);

}
float* Voronoi::calculate(int player)
{

	float* result = new float[2];
	if(grid.endState())
	{
		if(grid.loser() == 0)
		{
			std::cout<<grid.printGrid();
			result[0] = -1;result[1]=1;
		}
		else if(grid.loser() ==1)
		{
			result[1]=-1;result[0]=1;
		}
		return result;
	}
	if(&grid == 0)
		std::cout<<"grid is null\n";
	if(&one == 0 )
		std::cout<<"one is null\n";
	if(&two == 0 )
		std::cout<<"two is null\n";
	if(&pos == 0)
		std::cout<<"pos is null\n";
	if(&vor == 0)
		std::cout<<"vor is null\n";

	surroundBottom(grid.getPlayerOneHeadX(),grid.getPlayerOneHeadY(),one);this->resetMark();

	surroundTop(grid.getPlayerOneHeadX(),grid.getPlayerOneHeadY(),one);this->resetMark();
	surroundCheck(grid.getPlayerOneHeadX(),grid.getPlayerOneHeadY(),one);this->resetMark();
	surroundLeft(grid.getPlayerOneHeadX(),grid.getPlayerOneHeadY(),one);this->resetMark();

//	last(one);this->resetMark();

//	std::cout<<this->outputOne();
	std::cout<<std::endl;

	surroundLeft(grid.getPlayerTwoHeadX(),grid.getPlayerTwoHeadY(),two);this->resetMark();
	surroundBottom(grid.getPlayerTwoHeadX(),grid.getPlayerTwoHeadY(),two);this->resetMark();
	surroundTop(grid.getPlayerTwoHeadX(),grid.getPlayerTwoHeadY(),two);this->resetMark();
	surroundCheck(grid.getPlayerTwoHeadX(),grid.getPlayerTwoHeadY(),two);this->resetMark();
//	last(two);this->resetMark();

//	std::cout<<this->outputTwo();
	std::cout<<std::endl;

	getMerge(player);
	vor[grid.getPlayerOneHeadY()][grid.getPlayerOneHeadX()]=0;
	vor[grid.getPlayerTwoHeadY()][grid.getPlayerTwoHeadX()]=0;
	//std::cout<<this->outputVoronoi();
	int one = 0;
	int two = 0;
	for(int i = 1;i<width-1;i++)
	{
		for(int j = 0;j<width;j++)
		{
			if(vor[i][j]<0)
				one++;
			else if(vor[i][j]>0)
				two++;
		}
	}

	if(vor[0][0]<0)
		one++;
	else if(vor[0][0]>0)
		two++;
	if(vor[width-1][0]<0)
		one++;
	else if(vor[width-1][0]>0)
		two++;

/*
	if(one == 0 && two == 0)
	{
		result[0] = 0;result[1] = 0;
	}
	else*/
	{
		result[0] = (one-two)/(float)(one+two);
		result[1] = (two-one)/(float)(one+two);
	}

	return result;
}
}
