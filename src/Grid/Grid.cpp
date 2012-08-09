/*
 * Grid.cpp
 *
 *  Created on: 06 Aug 2012
 *      Author: Ivan Nelson Togboa Cadri
 *      implements playing grid
 */

#include "Grid.h"
namespace tron{
	//takes player one's head, player_two's head player and the grid
	Grid::Grid()
	{

		grid = new int*[30];
		for(int i =0;i<30;i++)
		{
			grid[i] = new int[30];
			for(int j = 0;j<30;j++)
			{
				grid[i][j] =0;
			}
		}
		turn = 0;
	}

	Grid::Grid(int * player_one,int * player_two, int** grid) {
		// constructor with many parameters
	//	std::cout<<"just started the contructor\n";

		player_one_head_x = player_one[0];
		player_two_head_x = player_two[0];
		player_one_head_y = player_one[1];
		player_two_head_y = player_two[1];

	//	std::cout<<player_one_head_x<<"large constructor"<<std::endl;
		this->grid = new int*[30];
		int one =0;int two = 0;
		for(int i =0;i<30;i++)
		{
			this->grid[i] = new int[30];
			for(int j = 0;j<30;j++)
			{
				this->grid[i][j] =grid[i][j];
				if(grid[i][j]==1)
					one++;
				else
					two++;
			}
		}
		if(one == two )
			turn = 0;
		else
			turn = 1;
		valid = true;

	//	std::cout<<"left this stupid constructore\n";
	}



	Grid& Grid::operator=(Grid& newGrid)
	{
		player_one_head_x = newGrid.getPlayerOneHeadX();
		player_one_head_y = newGrid.getPlayerOneHeadY();
		player_two_head_x = newGrid.getPlayerTwoHeadX();
		player_two_head_y = newGrid.getPlayerTwoHeadY();
		this->valid = newGrid.valid;
		for(int i = 0;i<30;i++)
			for(int j = 0;j<30;j++)
				this->grid[i][j] = newGrid[i][j];
		return *this;
	}
	Grid& Grid::operator()(Grid& newGrid)
	{
		*(this) = newGrid;
		return *this;
	}
	Grid::~Grid() {
		for(int i = 0;i<30;i++)
			delete []grid[i];
	}

	void Grid::setPlayerOneHead(int x, int y )
	{
		player_one_head_x = x,
		player_one_head_y = y;
	}
	void Grid::setPlayerTwoHead(int x, int y)
	{
		player_two_head_x = x;
		player_two_head_y = y;
	}
	int* Grid::operator[](int x)
	{
		if(x<0 ||x>29)
			return 	NULL;
		else
		{
			return this->grid[x];
		}
	}
	std::string Grid::printGrid()
	{
		std::cout<<"trying to print\n";
		std::stringstream str;
		str<<"player one: x "<<player_one_head_x<<" y "<<this->player_one_head_y<<std::endl;
		str<< "player two: x "<<player_two_head_x<<" y "<<player_two_head_y<<std::endl;

		for(int j=0;j<30;j++)
		{
			for(int i =0;i<30;i++){
				str<<grid[j][i];str<<" ";
			}
			str<<"\n";
		}
		return str.str();
	}
	/*Array that gives the state of the board
	 * 0 - binary value, 1 if the north pole is occupied
	 * 1 - binary value,  1 if the south pole is occupied
	 * 2 - turn 0 for player one, 1 for player two
	 * 3 - fraction of available spots
	 * 4 - fractional positition of the player one head
	 * 5 - fractional position of player two head
	 *
	 * 6..231 	laplace smoothened probabilities using (current_player_cout +1)/(total_count+12)
	 * 			for each 2x2 square
	*/
	double * Grid::getAfterState()
	{
		double * state = new double[231];
		int available = 0;
		int one=0;
		int two=0;
		int pos = 6;

		for(int j = 0; j<30;j++)
		{
			for(int i = 0 ;i<30;i++)
			{
				if(i%2 ==0 && j%2 == 0)//get the states for every four boxes
				{
					int inner_one = 0;
					int inner_two = 0;
					int not_zero = 0;
					for(int v = j;v<j+1;v++)
					{
						for(int w = i;w<i+1;w++)
						{
							if(grid[v][w] == 1)
							{
								inner_one++;
								not_zero++;
							}
							else if(grid[v][w]==2)
							{
								inner_two++;
								not_zero++;
							}
						}
					}

					if(turn == 0)
					{
						state[pos] = (inner_two +1.0)/(not_zero+12.0);//laplace smoothing
					}
					else
					{
						state[pos] =  (inner_one +1.0)/(not_zero+12.0);//laplace smoothin
					}
					pos++;
				}
				if(j==0&& state[0] == 0)//north pole
				{
					if(grid[j][i]!=0 )
						state[0] = 1;
				}
				else if(j==29&& state[1] == 0)//south pole
				{
					if(grid[j][i]!=0)
						state[1] = 1;
				}
				if(j != 0 && j!= 29 && grid[j][i]==0)//available spaces
				{
					available++;
				}
				if(grid[j][i] == 1)//number of ones
				{
					one++;
				}
				if(grid[j][i] == 2)//number of twos
				{
					two++;
				}
			}
		}
		if(one == two)
		{
			state[2] = 1;
		}
		else
		{
			state[2] = 0;
		}
		state[3] = (available+1-state[1]+1-state[0])/(900.0-58.0);
		state[4] = ((player_one_head_y * 30) -58 + player_one_head_x+1)/(900.0-58.0);
		state[5] = ((player_two_head_y * 30 ) -58 + player_two_head_x +1)/(900.0-58.0);
		return state;
	}
}