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
			if (debug)
				std::cout<<"playing first movve\n";
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


/*
		std::vector<Grid> afterstates(width);

		int index = -1;
		int difference = -999;
		if(this->y==0)//top
		{
			topMoves(*grid,afterstates);
		}
		else if (this->y==width-1)//bottom
		{
			bottomMoves(*grid,afterstates);
		}
		else//somewhere in the middle
		{
			middleMoves(*grid,afterstates);
		}

		int oppo;
		for(int i = 0;i<width;i++)
		{
			if(afterstates[i].isValid() == false)
				continue;
			Voronoi * a =  new Voronoi(&afterstates[i],width);

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
			Voronoi * a =  new Voronoi(&afterstates[index],width);
			std::cout<<"my "<<difference<<" opponent"<<oppo<<" "<<" difference "<<difference-oppo<<" index "<<index<<std::endl;
			*grid = afterstates[index];
			grid->setPlayerOneHead(afterstates[index].getPlayerOneHeadX(),afterstates[index].getPlayerOneHeadY());
			grid->setPlayerTwoHead(afterstates[index].getPlayerTwoHeadX(),afterstates[index].getPlayerTwoHeadY());
			this->setHead(afterstates[index]);
			int * result = a->calculate(digit);
		//	std::cout<<a->outputOne()<<std::endl;
		//	std::cout<<a->outputTwo()<<std::endl;
			std::cout<<result[0]<<": Player one\t"<<result[1]<<": Player two\n";
			std::cout<<a->outputVoronoi()<<std::endl;

		}*/

		*grid = alpha_beta(*grid,5);
	}

	Grid & Minimax::alpha_beta(Grid & current, int depth)
	{
		float temp = max(current,-std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity(),depth);

		std::vector<Grid> afterstates(width);

		this->possibleMoves(current,afterstates);
		for(int j = 0;j<width;j++)
		{
			if(afterstates[j].isValid() == false)
					continue;
			Voronoi * a = new Voronoi(&afterstates[j],width);
			int * result = a->calculate(digit);
			std::cout<<result[0]<<" "<<temp<<"these are the values calculated "<<std::endl;
			if(digit ==1 )
			{
				if(temp == result[0]){
					return afterstates[j];
				}
			}
			else
			{
				if(temp == result[1])
				{
					return afterstates[j];
				}
			}
		}
		return *new Grid(width);
	}

	int Minimax::max(Grid current, int alpha,int beta, int depth)
	{
		depth++;
		//if end state return value
		if(current.endState() || depth ==5)
		{
			Voronoi * a = new Voronoi(&current,width);
			int output;
			if(digit==1)
			{
				output =  a->calculate(digit)[0];
			}
			else
			{
				output = a->calculate(digit)[1];
			}
			std::cout<<" --- MAXIMUM ---  "<<output<<std::endl;
		//	std::cout<<current.printGrid();
		//	std::cout<<a->outputVoronoi();
			return output;
		}

		int value = -std::numeric_limits<int>::infinity();

		std::vector<Grid> afterstates(width);
		possibleMoves(current,afterstates);
		for(int j = 0;j<width;j++)
		{
			if(afterstates[j].isValid() == false)
				continue;
			int temp = min(afterstates[j],alpha,beta,depth);
			value = value>temp?value:temp;
			if(value>=beta || beta<=alpha)
				return value;
			alpha = alpha>value?alpha:value;
		}
		return value;
	}

	int Minimax::min(Grid current, int alpha,int beta, int depth)
	{
		//if endstate beta
		depth++;
		if(current.endState() || depth ==5 )
		{
			Voronoi * a = new Voronoi(&current,width);
			int output;
			if(digit== 1 )
			{
				output = a->calculate(digit)[0];
			}
			else if( digit == 3 )
			{
				output = a->calculate(digit)[1];
			}
			std::cout<<" --- MINIMUM ---   "<<output<<std::endl;
		//	std::cout<<current.printGrid();
		//	std::cout<<a->outputVoronoi();
			return output;
		}
		int value = std::numeric_limits<int>::infinity();

		std::vector<Grid> afterstates(width);
		this->getOpponentPlayer()->possibleMoves(current,afterstates);
		for(int j = 0;j<width;j++)
		{
			if(afterstates[j].isValid()== false)
				continue;
			int temp = max(afterstates[j],alpha,beta,depth);
			value = value<temp?value:temp;
			if(value<=alpha || beta<=alpha)
				return value;
			beta = beta<value?beta:value;
		}
		return value;
	}
}

