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
			grid->setPlayerOneHead(x,y);

			(*grid)[y][x] = digit;
			(*grid).isValid(true);
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
			(*grid).setPlayerTwoHead(new_x,new_y);
			(*grid).isValid(true);
			(*grid)[new_y][new_x] = digit;

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

			float * result = a->calculate(digit);
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
			float * result = a->calculate(digit);
			std::cout<<a->outputOne()<<std::endl;
			std::cout<<a->outputTwo()<<std::endl;
			std::cout<<result[0]<<": Player one\t"<<result[1]<<": Player two\n";
			std::cout<<a->outputVoronoi()<<std::endl;

		}*/

		*grid = alpha_beta(0);
	}

	Grid & Minimax::alpha_beta(int depth)
	{
		Grid * g = new Grid(width);
		max(*grid,-1,1,depth,*g);
		Voronoi * vor = new Voronoi(g,width);
		float *result = new float[2];
		result = vor->calculate(digit);
		//std::cout<<result[0]<<"    "<<result[1]<<std::endl;
	//	std::cout<<vor->outputVoronoi();
		return *g;
	}

	float Minimax::max(Grid current, float alpha,float beta, int depth,Grid & next)
	{
		depth++;
		time(&end);
		//if end state return value
		if(current.endState() || difftime(end,start)>=3.5 )
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
			if(depth == 1)
				next = current;
			//std::cout<<"depth - "<<depth<<"\n"<<current.printGrid()<<"\n\n";
			return output;
		}

		float value = -std::numeric_limits<float>::infinity();

		std::vector<Grid> afterstates(width);
		possibleMoves(current,afterstates);
		for(int j = 0;j<width;j++)
		{
			if(afterstates[j].isValid() == false)
				continue;

			float temp = min(afterstates[j],alpha,beta,depth,next);
			if(temp>value){
			//	std::cout<<"depth: "<<depth<<"\n"<<"maximum\n"<<current.printGrid()<<"\n\n";
				value = temp;
				if(depth==1)
					next=afterstates[j];
			}
			alpha = alpha>value?alpha:value;
			if(value>=beta)
				return value;
		}
		return value;
	}

	float Minimax::min(Grid current, float alpha,float beta, int depth,Grid & next)
	{
		//if endstate beta
		depth++;
		time(&end);
		if(current.endState()|| std::difftime(end,start)>=3.5 )
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
			if(depth == 1)
				next = current;
			//std::cout<<"depth - "<<depth<<"\n"<<current.printGrid()<<"\n\n";
			return output;
		}
		float value = std::numeric_limits<float>::infinity();
		std::vector<Grid> afterstates(width);
		this->getOpponentPlayer()->possibleMoves(current,afterstates);
		for(int j = 0;j<width;j++)
		{
			if(afterstates[j].isValid()== false)
				continue;
			float temp = max(afterstates[j],alpha,beta,depth,next);
			if(temp<value)
			{
				value = temp;
				if(depth == 1)
					next = current;
			//	std::cout<<"depth: "<<depth<<"\n"<<"minimum\n"<<current.printGrid()<<"\n\n";
			}
			beta = beta<value?beta:value;
			if(value<=alpha)
				return value;
		}
		return value;
	}
}

