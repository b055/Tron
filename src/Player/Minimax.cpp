/*
 * Minimax.cpp
 *
 *  Created on: Aug 27, 2012
 *      Author: ivan
 */

#include "Minimax.h"

namespace tron {

	Minimax::Minimax(int digit,int width):Player(digit,width),MAX(9999),LIMIT(10) {
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
			//if (debug)
				std::cout<<"playing first movve\n";
			std::srand(time(NULL));
			x =4;rand()%width;
			y =1; rand()%width;

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
		int free_top =0;
		int free_bottom = 0;
		for(int i = 0;i<width;i++)
		{
			if((*grid)[1][i] ==0)
				free_top++;
			if((*grid)[width-1][i]==0)
				free_bottom++;
		}
		int proximity= 0;
		if((*grid)[0][0] == 0)
		{

		}
		
		int xbefore = x;
		int ybefore = y;
		int value = max(-MAX,MAX,0);

		int xafter = x;int yafter = y;
		std::cout<<std::endl<<value<<"  max value"<<std::endl;
		if(value == -MAX)
		{
			std::cout<<grid->printGrid()<<std::endl;
			restoreGrid(x,y,0);
			restore(xbefore,ybefore,oppo_x,oppo_y);
			std::vector<std::vector<int> > afterstates = possibleMoves();
			int bestx=xafter;
			int besty = yafter;
			int bestvalue = value;
			for(int j = 0;j<afterstates.size();j++)
			{
				Voronoi a(grid,width);
				int * result = a.calculate(digit);
				if(digit==1)
				{
					if(bestvalue<result[0])
					{
						bestvalue = result[0];
						bestx = afterstates[j][0];
						besty = afterstates[j][1];
					}
				}
				else
				{
					if(bestvalue<result[1])
					{
						bestvalue = result[1];
						bestx = afterstates[j][0];
						besty = afterstates[j][1];
					}
				}
			}
			restore(bestx,besty,oppo_x,oppo_y);
			restoreGrid(x,y,digit);
		}
	}
	

	int Minimax::max(int alpha,int beta, int depth)
	{
		depth++;
		time(&end);
		//std::cout<<depth<<std::endl;
		double elapsed = difftime(end,start);
		//if end state return value
		if(getLoser()|| this->getOpponentPlayer()->getLoser() || depth > LIMIT )// || difftime(end,start)>= 3.5)
		{
			//std::cout<<depth<<std::endl;
			//if(elapsed >= 4)
			//	return alpha;
			if(getLoser())
				return -MAX;
			if(this->getOpponentPlayer()->getLoser())
				return MAX;
			Voronoi a(grid,width);
			int * result = a.calculate(digit);
			if(digit==1)
			{
				return result[0];
			}
			else
			{
				return result[1];
			}
		}

		int value = -MAX;
		std::vector<std::vector<int> > afterstates = possibleMoves();
		int bestx = -1; int besty=-1;
		if((y == 0 || y == width-1) && !afterstates.empty())
			random_shuffle(afterstates.begin(),afterstates.end());
		bestx = afterstates[0][0];
		besty = afterstates[0][1];
		for(int j = 0;j<afterstates.size();j++)
		{
			int oldx = this->x; int oldy = this->y;
			int oldoppox = oppo_x; int oldoppoy = oppo_y;

			restore(afterstates[j][0],afterstates[j][1],oppo_x,oppo_y);
			restoreGrid(afterstates[j][0],afterstates[j][1],digit);

			int temp = min(alpha,beta,depth);

			//rolls back
			if(getLoser())
			{
				restoreGrid(afterstates[j][0],afterstates[j][1],getPrior());
				loser = false;
			}
			else if(this->getOpponentPlayer()->getLoser())
			{
				restoreGrid(afterstates[j][0],afterstates[j][1],this->getOpponentPlayer()->getPrior());
				this->getOpponentPlayer()->setLoser(false);
			}
			else
				restoreGrid(afterstates[j][0],afterstates[j][1],0);

			restore(oldx,oldy,oldoppox,oldoppoy);

			if(temp>value){
				value = temp;
				bestx = afterstates[j][0];
				besty = afterstates[j][1];
			}

			if(value>=beta){
				if(depth==1)
				{
					restore(afterstates[j][0],afterstates[j][1],oldoppox,oldoppoy);
					if((*grid)[y][x] == 0)
						restoreGrid(x,y,digit);
					else
					{
						restoreGrid(x,y,digit+(*grid)[y][x]);
						loser = true;
					}
				}
				return value;
			}
			alpha = alpha>value?alpha:value;
		}
		if(depth==1)
		{
			if(bestx != -1){
				restore(bestx,besty,oppo_x,oppo_y);
				if((*grid)[y][x] == 0)
					restoreGrid(x,y,digit);
				else
				{
					restoreGrid(x,y,digit+(*grid)[y][x]);
					loser = true;
				}
			}
		}
		return value;
	}

	int Minimax::min(int alpha,int beta, int depth)
	{
		depth++;
		time(&end);
		double elapsed = difftime(end,start);
		Player* opponent = this->getOpponentPlayer();
		//std::cout<<depth<<std::endl;
		if(getLoser() || opponent->getLoser() || depth > LIMIT+1)// || std::difftime(end,start)>= 3.5)
		{
			//if(elapsed >= 4)
			//	return beta; //returns the beta
			if(getLoser())
				return -MAX;
			if(opponent->getLoser())
				return MAX;
			Voronoi a(grid,width);
			int * result = a.calculate(digit);
			if(digit== 1 )
			{
				return result[0];
			}
			else if( digit == 3 )
			{
				return result[1];
			}
		}

		int value = MAX;
		std::vector<std::vector<int> > afterstates = opponent->possibleMoves();

		if((oppo_y == 0 || oppo_y == width-1) && !afterstates.empty())// shuffle the points at the poles, chances are not all would be checked
			random_shuffle(afterstates.begin(),afterstates.end());

		for(int j = 0;j<afterstates.size();j++)
		{

			int oldx = this->oppo_x; int oldy = this->oppo_y;
			int oldoppox = x; int oldoppoy = y;

			restore(x,y,afterstates[j][0],afterstates[j][1]);
			restoreGrid(afterstates[j][0],afterstates[j][1],opponent->getDigit());

			int temp = max(alpha,beta,depth);

			//rolls back
			if(opponent->getLoser())
			{
				restoreGrid(afterstates[j][0],afterstates[j][1],opponent->getPrior());
				opponent->setLoser(false);
			}
			else if(getLoser())
			{
				restoreGrid(afterstates[j][0],afterstates[j][1],getPrior());
				loser = false;
			}
			else
				restoreGrid(afterstates[j][0],afterstates[j][1],0);

			restore(oldoppox,oldoppoy,oldx,oldy);

			if(temp<value)
			{
				value = temp;
			}
			if(value<=alpha){
				return value;
			}
			beta = beta<value?beta:value;
		}
		return value;
	}


	void Minimax::restore(int x,int y ,int oppo_x,int oppo_y)
	{
		Player * opponent = this->getOpponentPlayer();

		if(digit ==1)
		{
			(*grid).setPlayerOneHead(x,y);
			(*grid).setPlayerTwoHead(oppo_x,oppo_y);
		}
		else
		{
			(*grid).setPlayerTwoHead(x,y);
			(*grid).setPlayerOneHead(oppo_x,oppo_y);
		}
		this->oppo_x = oppo_x;
		this->oppo_y = oppo_y;
		this->x = x;
		this->y = y;

		opponent->setOppoX(x);
		opponent->setOppoY(y);
		opponent->setX(oppo_x);
		opponent->setY(oppo_y);
	}

	void Minimax::restoreGrid(int x,int y,int digit)
	{
		if(y == 0 || y == width-1)
		{
			for(int i =0;i<width;i++)
				(*grid)[y][i] = digit;
		}
		else
			(*grid)[y][x] = digit;
	}
}

