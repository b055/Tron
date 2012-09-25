/*
 * Minimax.cpp
 *
 *  Created on: Aug 27, 2012
 *      Author: ivan
 */

#include "Minimax.h"

namespace tron {

	Minimax::Minimax(int digit):Player(digit),MAX(9999),LIMIT(6) {
	}

	Minimax::~Minimax() {
		//Nothing to do here
	}

	void Minimax::play(time_t & start)
	{
		//check if at poles and get possible moves
		//check if at edges and get possible moves
		/*if(debug)
			std::cout<<"possible moves for "<<digit<<std::endl;
		int count = 0;
		for(int i = 0;i<30;i++)
		{
			if(count>1)
				break;
			for(int j = 0 ;j<30;j++)
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
			int x = rand()%30;
			int y = rand()%30;
			if(y == 0)
				y++;
			if(30-1 == y)
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
			if((*grid).getPlayerOneHeadY()>0&& (*grid).getPlayerOneHeadY()<30-1)
			{
				new_x = ((*grid).getPlayerOneHeadX()+(30/2))%30;
				new_y = (*grid).getPlayerOneHeadY();
				(*grid)[new_y][new_x] = digit;
			}			
			(*grid).setPlayerTwoHead(new_x,new_y);
			return;
		}*/
		this->start = start;

		first = new Voronoi(grid);
		int *result = first->calculate(digit);

		if(first->getSeparated())
		{
			wallHug();
			return;
		}

		if((y ==1 || oppo_y == 1) && (*grid)[0][0] == 0)
		{
			LIMIT = 4;
		}
		else if( (y>=28 ||  oppo_y ==28) && (*grid)[29][0] == 0)
		{
			LIMIT = 4;
		}
		if((y == 0 || y == 29) && possibleMoves().size()>6 )
		{
			LIMIT = 4;
		}
		else if((oppo_y == 0 || oppo_y == 29)&& this->getOpponentPlayer()->possibleMoves().size()>6)
		{
			LIMIT = 4;
		}

		int xbefore = x;
		int ybefore = y;

		//peform the minimax
		int value = max(-MAX,MAX,0);

		int xafter = x;int yafter = y;

		/*if a guaranteed loss, just try to make the next best move, hopefully the other player will fuck up
		 * if all goes as planned, i won't need to perform this stuf
		 * */
		//std::cout<<value<<std::endl;

		LIMIT = 6;
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
				Voronoi a(grid);
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
				Voronoi a(grid);
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
	
	void Minimax::wallHug()
	{
		std::vector<std::vector<int> > afterstates = possibleMoves();
		int bestx,besty;
		int max = -1;
		std::vector<std::vector< int> > maxStack;
		if(afterstates.size() == 1)
		{
			restore(afterstates[0][0],afterstates[0][1],oppo_x,oppo_y);
			restoreGrid(afterstates[0][0],afterstates[0][1],digit);
			return;
		}
		bestx = afterstates[0][0];
		besty = afterstates[0][1];
		int chamber = 0;
		for(int i = 0;i<afterstates.size();i++)
		{
			int temp =0;

			int topy,bottomy,rightx,leftx;
			topy = afterstates[i][1]-1;
			bottomy = afterstates[i][1]+1;
			rightx = afterstates[i][0]+1;
			if(rightx == 30)
				rightx = 0;
			leftx = afterstates[i][0]-1;
			if(leftx == -1)
				leftx = 29;
			if((*grid)[afterstates[i][1]][rightx]!=0)
				temp++;
			if((*grid)[afterstates[i][1]][leftx]!=0)
				temp++;
			if(bottomy != 30)
			{
				if((*grid)[bottomy][afterstates[i][0]]!=0)
					temp++;
			}
			else
			{

			}
			if(topy != -1)
			{
				if((*grid)[topy][afterstates[i][0]]!=0)
					temp++;
			}
			else
			{

			}


			if(temp>=max)
			{

				if(temp == 4)
				{
					continue;
				}

				int oldx = x;int oldy = y;
				restore(afterstates[i][0],afterstates[i][1],oppo_x,oppo_y);
				restoreGrid(afterstates[i][0],afterstates[i][1],digit);
				Voronoi one(grid);
				int* result = one.calculate(digit);
				restore(oldx,oldy,oppo_x,oppo_y);
				restoreGrid(afterstates[i][0],afterstates[i][1],0);

				if(digit == 1)
				{
					if(result[0]>=chamber)
					{
						chamber = result[0];
						std::vector< int> current;
						current.push_back(afterstates[i][0]);
						current.push_back(afterstates[i][1]);
						current.push_back(temp);
						maxStack.push_back(current);
						bestx= afterstates[i][0];
						besty = afterstates[i][1];
						max = temp;
					}

				}
				else
				{
					if(result[1]>=chamber)
					{
						chamber = result[1];
						std::vector< int> current;
						current.push_back(afterstates[i][0]);
						current.push_back(afterstates[i][1]);
						current.push_back(temp);
						maxStack.push_back(current);
						bestx= afterstates[i][0];
						besty = afterstates[i][1];
						max = temp;
					}
				}
			}
		}
		int count = 0;
		for(int i = 0;i<maxStack.size();i++)
		{
			if(maxStack[i][3] == max)
				count++;
		}
		if(count == 2)
		{
			int oldx = x;int oldy = y;
			restore(maxStack[0][0],maxStack[0][1],oppo_x,oppo_y);
			restoreGrid(maxStack[0][0],maxStack[0][1],digit);
			Voronoi one(grid);

			restore(oldx,oldy,oppo_x,oppo_y);
			restoreGrid(maxStack[0][0],maxStack[0][1],0);

			int * oneresult = one.calculate(digit);

			restore(maxStack[1][0],maxStack[1][1],oppo_x,oppo_y);
			restoreGrid(maxStack[1][0],maxStack[1][1],digit);
			Voronoi two(grid);
			int *tworesult = two.calculate(digit);

			restore(oldx,oldy,oppo_x,oppo_y);
			restoreGrid(maxStack[1][0],maxStack[1][1],0);


			if(digit == 1)
			{
				if(tworesult[0]>oneresult[0])
				{
					restore(maxStack[1][0],maxStack[1][1],oppo_x,oppo_y);
					restoreGrid(maxStack[1][0],maxStack[1][1],digit);
				}
				else if(oneresult[0]>tworesult[0])
				{
					restore(maxStack[0][0],maxStack[0][1],oppo_x,oppo_y);
					restoreGrid(maxStack[0][0],maxStack[0][1],digit);
				}
				else
				{
					int ran = rand()%2;
					if(ran == 0)
					{
						restore(maxStack[1][0],maxStack[1][1],oppo_x,oppo_y);
						restoreGrid(maxStack[1][0],maxStack[1][1],digit);
					}
					else
					{
						restore(maxStack[0][0],maxStack[0][1],oppo_x,oppo_y);
						restoreGrid(maxStack[0][0],maxStack[0][1],digit);
					}
				}
			}
			else
			{
				if(tworesult[1]>oneresult[1])
				{
					restore(maxStack[1][0],maxStack[1][1],oppo_x,oppo_y);
					restoreGrid(maxStack[1][0],maxStack[1][1],digit);
				}
				else if(oneresult[1]>tworesult[1])
				{
					restore(maxStack[0][0],maxStack[0][1],oppo_x,oppo_y);
					restoreGrid(maxStack[0][0],maxStack[0][1],digit);
				}
				else
				{
					int ran = rand()%2;
					if(ran == 0)
					{
						restore(maxStack[1][0],maxStack[1][1],oppo_x,oppo_y);
						restoreGrid(maxStack[1][0],maxStack[1][1],digit);
					}
					else
					{
						restore(maxStack[0][0],maxStack[0][1],oppo_x,oppo_y);
						restoreGrid(maxStack[0][0],maxStack[0][1],digit);
					}
				}
			}
		}
		else
		{
			if(maxStack.empty())
			{

			}
			restore(bestx,besty,oppo_x,oppo_y);
			restoreGrid(bestx,besty,digit);
		}
	}
	int Minimax::max(int alpha,int beta, int depth)
	{
		depth++;
		time(&end);
		//std::cout<<depth<<std::endl;
		double elapsed = difftime(end,start);
		//if end state return value

		//if(elapsed <2 && depth >LIMIT)
			//LIMIT++;
		if((getLoser() || this->getOpponentPlayer()->getLoser()) || depth > LIMIT || elapsed>= 3.5)
		{
			if(getLoser())
				return -MAX;
			if(this->getOpponentPlayer()->getLoser())
				return MAX;

			{
				Voronoi a(grid);
				int * result = a.calculate(digit);

				if(digit==1)
				{
					int value = result[0];
					if(value>60 && a.getSeparated())
						value = MAX;
					delete result;
					return value;
				}
				else
				{
					int value = result[1];
					if(value>60 && a.getSeparated())
						value = MAX;
					delete result;
					return value;
				}
			}
		}

		int value = -MAX;
		std::vector<std::vector<int> > afterstates = possibleMoves();
		int bestx = -1; int besty=-1;
		if(afterstates.size()>6)
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
		//if(elapsed <2 && depth >LIMIT)
			//LIMIT++;
		if((getLoser() || opponent->getLoser()) || (depth > LIMIT || elapsed>= 3.5))
		{
			if(getLoser())
				return -MAX;
			if(opponent->getLoser())
				return MAX;
			Voronoi a(grid);
			int * result = a.calculate(digit);
			if(digit== 1 )
			{
				int value =  result[0];
				if(value>60 && a.getSeparated())
					value = MAX;
				delete result;
				return value;
			}
			else if( digit == 3 )
			{
				int value = result[1];
				if(value>60 && a.getSeparated())
					value = MAX;
				delete result;
				return value;
			}
		}

		int value = MAX;
		std::vector<std::vector<int> > afterstates = opponent->possibleMoves();

		if(afterstates.size()>6)// shuffle the points at the poles, chances are not all would be checked
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
		if(y == 0 || y == 29)
		{
			for(int i =0;i<30;i++)
				(*grid)[y][i] = digit;
		}
		else
			(*grid)[y][x] = digit;
	}
}

