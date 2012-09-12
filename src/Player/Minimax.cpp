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
		//Nothing to do here
	}

	void Minimax::play(time_t & start)
	{
		this->start = start;
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
			x =rand()%width;
			y = rand()%width;

			(*grid)[y][x] = digit;
			grid->setPlayerOneHead(x,y);

			std::cout<<grid->printGrid();
			return;
		}
		else if(count ==1)
		{
			if(debug)
				std::cout<<"finished second\n";
			int new_x,new_y;
			if(oppo_y>0&& oppo_y<width-1)
			{
				new_x = (oppo_x+(width/2))%width;
				new_y = oppo_y;

			}else
			{
				new_x = oppo_x;
				new_y = width-1-oppo_y;
			}
			(*grid)[new_y][new_x] = digit;
			(*grid).setPlayerTwoHead(new_x,new_y);

			return;
		}
		max(*grid,-9999,9999,0,*grid);
	}
	

	float Minimax::max(Grid current, float alpha,float beta, int depth,Grid & next)
	{
		depth++;
		time(&end);
		//if end state return value
		if(current.endState() || difftime(end,start)>= 1)
		{
			//std::cout<<depth<<std::endl;
			Voronoi a(&current,width);
			float output;
			float * result = a.calculate(digit);
			if(digit==1)
			{
				output =  result[0];
			}
			else
			{
				output = result[1];
			}
			if(depth == 1)
				next = current;

			//delete result;
			return output;
		}

		float value = -9999;

		std::vector<Grid> afterstates;
		possibleMoves(current,afterstates);
		for(int j = 0;j<afterstates.size();j++)
		{
			float temp = min(afterstates[j],alpha,beta,depth,next);
			if(temp>=value){
				value = temp;
				if(depth==1)
					next=afterstates[j];
			}

			alpha = alpha>value?alpha:value;
			if(value>=beta){
				if(depth==1)
					next=afterstates[j];
				return value;
			}
		}
		return value;
	}

	float Minimax::min(Grid current, float alpha,float beta, int depth,Grid & next)
	{
		depth++;
		time(&end);
		if(current.endState()|| std::difftime(end,start)>= 1)
		{
			Voronoi a(&current,width);
			float output;
			float * result = a.calculate(digit);
			if(digit== 1 )
			{
				output = result[0];
			}
			else if( digit == 3 )
			{
				output = result[1];
			}
			if(depth == 1)
				next = current;
			//delete result;
			return output;
		}
		float value = 9999;
		std::vector<Grid> afterstates;
		this->getOpponentPlayer()->possibleMoves(current,afterstates);
		for(int j = 0;j<afterstates.size();j++)
		{
			float temp = max(afterstates[j],alpha,beta,depth,next);
			if(temp<=value)
			{
				value = temp;
				if(depth == 1)
					next = afterstates[j];
			}
			beta = beta<value?beta:value;
			if(value<=alpha){
				if(depth==1)
					next=afterstates[j];
				return value;
			}
		}
		return value;
	}
}

