/*
 * Minimax.cpp
 *
 *  Created on: Aug 27, 2012
 *      Author: ivan
 */

#include "Minimax.h"

namespace tron {

	Minimax::Minimax(int digit,int width):Player(digit,width),MAX(9999),LIMIT(8) {
	}

	Minimax::~Minimax() {
		//Nothing to do here
	}

	void Minimax::play(time_t & start)
	{
		//check if at poles and get possible moves
		//check if at edges and get possible moves
	/*	if(debug)
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
			int x = rand()%width;
			int y = rand()%width;
			if(y == 0)
				y++;
			if(width-1 == y)
				y--;
			
			(*grid)[y][x] = digit;
			(*grid).setPlayerOneHeadX(x);
			(*grid).setPlayerOneHeadY(y);
			return;
		}
		else if(count ==1)
		{
			//PLAYING SECOND MOVE
			//std::cout<<"playing second move\n";
			//std::cout<<"made copy\n";
			int new_x,new_y;
			if((*grid).getPlayerOneHeadY()>0&& (*grid).getPlayerOneHeadY()<width-1)
			{
				new_x = ((*grid).getPlayerOneHeadX()+(width/2))%width;
				new_y = (*grid).getPlayerOneHeadY();
				(*grid)[new_y][new_x] = digit;
			}			
			(*grid).setPlayerTwoHead(new_x,new_y);
			return;
		}*/
		this->start = start;
		//check if at edges and get possible moves
	//	if(debug)
		//	std::cout<<"possible moves for "<<digit<<std::endl;
		
		/*if(y<18 && y>12 && oppo_y<18 && oppo_y >12)
		{
			LIMIT = 8;
		}
		else
		{
			first = new Voronoi(grid,width);
			first_result= first->calculate(0);
			int one_avail = first->getOneAvail();
			int two_avail = first->getTwoAvail();

			int min_avail = one_avail<two_avail?one_avail:two_avail;
			if(min_avail <= 30)
			{
				LIMIT = 30;
			}
			else
			{
				/*int free_top =0;
				int free_bottom = 0;
				for(int i = 0;i<width;i++)
				{
					if((*grid)[1][i] ==0)
						free_top++;
					if((*grid)[width-1][i]==0)
						free_bottom++;
				}
				int max_pole = free_top>free_bottom?free_top:free_bottom;
				if(max_pole <= 5)
				{}
				else
				{
					int one_north = first->getOneNorth();
					int one_south = first->getOneSouth();
					int two_north = first->getTwoNorth();
					int two_south = first->getTwoSouth();

					int proximity= one_north<one_south?one_north:one_south;
					proximity= proximity<two_north?proximity:two_north;
					proximity = proximity<two_south?proximity:two_south;

					if(proximity < LIMIT/2)
					{// if a player is really close to the pole, just predict beyond the pole
						LIMIT = (proximity<<1) +6;
					}
					else
					{// otherwise just use the limit

					}
				}
			}
		}*/

		int xbefore = x;
		int ybefore = y;

		//peform the minimax
		int value = max(-MAX,MAX,0);

		int xafter = x;int yafter = y;

		/*if a guaranteed loss, just try to make the next best move, hopefully the other player will fuck up
		 * if all goes as planned, i won't need to perform this stuf
		 * */
		std::cout<<value<<std::endl;


		if(value == -MAX)
		{
		//	std::cout<<grid->printGrid()<<std::endl;
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
			return;
		}
		if(xafter == xbefore && yafter == ybefore)
		{
			std::vector<std::vector<int> > afterstates = possibleMoves();
			int bestx=xafter;
			int besty = yafter;
			int bestvalue = -MAX;
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
			restoreGrid(bestx,besty,digit);
		}
		delete first;
	}
	

	int Minimax::max(int alpha,int beta, int depth)
	{
		depth++;
		time(&end);
		//std::cout<<depth<<std::endl;
		double elapsed = difftime(end,start);
		//if end state return value
		if(getLoser()|| this->getOpponentPlayer()->getLoser() || depth > LIMIT || difftime(end,start)>= 4)
		{
			//std::cout<<depth<<std::endl;
			if(elapsed >= 4.5)
				return alpha;
			if(getLoser())
				return -MAX;
			if(this->getOpponentPlayer()->getLoser())
				return MAX;

			{
				Voronoi a(grid,width);
				int * result = a.calculate(digit);

				if(digit==1)
				{
					int value = result[0];
					delete result;
					return value;
				}
				else
				{
					int value = result[1];
					delete result;
					return value;
				}
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
						//restoreGrid(x,y,digit+(*grid)[y][x]);
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
					//restoreGrid(x,y,digit+(*grid)[y][x]);
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
		if(getLoser() || opponent->getLoser() || depth > LIMIT || difftime(end,start)>= 4)
		{
			if(elapsed >= 4.5)
				return beta; //returns the beta
			if(getLoser())
				return -MAX;
			if(opponent->getLoser())
				return MAX;
			Voronoi a(grid,width);
			int * result = a.calculate(digit);
			if(digit== 1 )
			{
				int value =  result[0];
				delete result;
				return value;
			}
			else if( digit == 3 )
			{
				int value = result[1];
				delete result;
				return value;
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

