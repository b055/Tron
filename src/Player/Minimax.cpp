/*
 * Minimax.cpp
 *
 *  Created on: Aug 27, 2012
 *      Author: ivan
 */

#include "Minimax.h"

namespace tron {

Minimax::Minimax(int digit,int width):Player(digit,width) {

}

Minimax::~Minimax() {

}

void Minimax::play()
{

	//check if at edges and get possible moves
	if(debug)
		std::cout<<"possible moves for "<<digit<<std::endl;
	int count = 0;
	for(int i = 0;i<width;i++)
	{
		if(count>1)
			break;
		for(int j = 0 ;j<width;j++)
		{
			if(count>1)
				break;
			if((*grid)[i][j]!=0){
				count++;
			}
		}
	}
	if(count == 0)///first move
	{
		//std::cout<<"playing first movve\n";
		std::srand(time(NULL));
		x = rand()%width;
		y = rand()%width;
		grid->setPlayerOneHead(x,y);

		(*grid)[y][x] = digit;
		(*grid).isValid(true);
		return;
	}
	else if(count ==1)
	{
		if(oppo_y>0&& oppo_y<width-1)
		{
			int new_x = (oppo_x+(width/2))%width;
			int new_y = oppo_y;
			(*grid).setPlayerOneHead(oppo_x,oppo_y);
			(*grid).setPlayerTwoHead(new_x,new_y);
			(*grid).isValid(true);
			(*grid)[new_y][new_x] = digit;

		}else
		{
			int new_x = oppo_x;
			int new_y = width-1-oppo_y;
			(*grid).setPlayerOneHead(oppo_x,oppo_y);
			(*grid).setPlayerTwoHead(new_x,new_y);
			(*grid).isValid(true);
			(*grid)[new_y][new_x] = digit;
		}
		//std::cout<<"finished second\n";
		return;
	}
	Voronoi * a =  new Voronoi(grid,width);


	Grid** afterstates = new Grid*[width];
	#pragma omp parallel for
		for(int i = 0;i<width;i++)
			afterstates[i] = new tron::Grid(width);

	int index = -1;
	int difference = -999;
	if(this->y==0)//top
	{
		std::cout<<"got here\n";
		topMoves(afterstates);
	}
	else if (this->y==width-1)//bottom
	{
		bottomMoves(afterstates);
	}
	else//somewhere in the middle
	{
		middleMoves(afterstates);
	}

	int oppo;
	for(int i = 0;i<width;i++)
	{
		if(afterstates[i]->isValid() == false)
			continue;
		a->setGrid(afterstates[i]);
		int * result = a->calculate(digit);
		if(digit ==1)
		{
			int dif = result[0];//-result[1];
			if(dif>difference)
			{
				difference = dif;
				index = i;
				oppo = result[1];
			}
		}
		else
		{
			int dif = result[1];//-result[0];
			if(dif>difference)
			{
				difference = dif;
				index = i;
				oppo=result[0];
			}
		}
		std::cout<<"mini "<<difference<<" opponent"<<oppo<<" "<<" difference "<<difference-oppo<<" index "<<index<<std::endl;
	}

	if(index != -1)
	{
		std::cout<<"my "<<difference<<" opponent"<<oppo<<" "<<" difference "<<difference-oppo<<" index "<<index<<std::endl;
		*grid = *afterstates[index];
		grid->setPlayerOneHead(afterstates[index]->getPlayerOneHeadX(),afterstates[index]->getPlayerOneHeadY());
		grid->setPlayerTwoHead(afterstates[index]->getPlayerTwoHeadX(),afterstates[index]->getPlayerTwoHeadY());
		this->setHead(*afterstates[index]);
		a->setGrid(afterstates[index]);
		int * result = a->calculate(digit);
	//	std::cout<<a->outputOne()<<std::endl;
	//	std::cout<<a->outputTwo()<<std::endl;
		std::cout<<result[0]<<": Player one\t"<<result[1]<<": Player two\n";
		std::cout<<a->outputVoronoi()<<std::endl;

	}
}
} /* namespace tron */

