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
			x =1; rand()%width;
			y = 2;rand()%width;
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
				(*grid).setPlayerTwoHead(new_x,new_y);
				(*grid).isValid(true);
				(*grid)[new_y][new_x] = digit;

			}else
			{
				int new_x = oppo_x;
				int new_y = width-1-oppo_y;
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

		*grid = alpha_beta(*grid,0);
	}

	Grid & Minimax::alpha_beta(Grid & current, int depth)
	{
		Grid * g = new Grid(width);
		max(current,-1,1,depth,*g);
		Voronoi * a = new Voronoi(g,width);
		std::cout<<a->calculate(digit)[0]<<std::endl;
		std::cout<<a->outputOne()<<"\n"<<a->outputTwo()<<"\n"<<a->outputVoronoi()<<std::endl;
		return *g;
	}

	float Minimax::max(Grid current, float alpha,float beta, int depth,Grid & next)
	{
		depth++;
		//if end state return value
		if(current.endState())
		{
			Voronoi * a = new Voronoi(&current,width);
			float output;
			float * result = a->calculate(digit);
			if(digit==1)
			{
				output =  result[0];
			}
			else
			{
				output = result[1];
			}
			next = current;
			return output;
		}

		float value = -1;

		std::vector<Grid> afterstates(width);
		possibleMoves(current,afterstates);
		for(int j = 0;j<width;j++)
		{
			if(afterstates[j].isValid() == false)
				continue;

			float temp = min(afterstates[j],alpha,beta,depth,next);
			value = value>temp?value:temp;

	//		std::cout<<value<<"  "<<temp<<"  "<<beta<<"  "<<alpha<<"\n"<<afterstates[j].printGrid()<<std::endl;

			alpha = alpha>value?alpha:value;
			if(value>=beta || beta<=alpha)
			{
				next = afterstates[j];
				return value;
			}
		}
		return value;
	}

	float Minimax::min(Grid current, float alpha,float beta, int depth,Grid & next)
	{
		//if endstate beta
		depth++;
		if(current.endState())
		{
			Voronoi * a = new Voronoi(&current,width);
			float output;
			float * result = a->calculate(digit);
			if(digit== 1 )
			{
				output = result[0];
			}
			else if( digit == 3 )
			{
				output = result[1];
			}
			return output;
		}
		float value = 1;
		std::vector<Grid> afterstates(width);
		this->getOpponentPlayer()->possibleMoves(current,afterstates);
		for(int j = 0;j<width;j++)
		{
			if(afterstates[j].isValid()== false)
				continue;
			float temp = max(afterstates[j],alpha,beta,depth,next);
			value = value<temp?value:temp;

			std::cout<<value<<"  "<<temp<<"  "<<beta<<"  "<<alpha<<"\n"<<afterstates[j].printGrid()<<std::endl;

			beta = beta<value?beta:value;
			if(value<=alpha || beta<=alpha){
				return value;
			}
		}
		return value;
	}
}

