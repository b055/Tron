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
		state = new double[231];
		for(int i =0;i<30;i++)
		{
			std::vector<int> temp;
			for(int j = 0;j<30;j++)
			{
				temp.push_back(0);
			}
			grid.push_back(temp);
		}
		turn = 0;
		valid = false;
	}

	void Grid::reset()
	{
		player_one_head_x = 0;
		player_two_head_x = 0;
		player_one_head_y = 0;
		player_two_head_y  = 0;
#pragma omp parallel for
		for(int i =0;i<30;i++)
		{
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

		int one =0;int two = 0;
		for(int i =0;i<30;i++)
		{
			std::vector<int> temp;
			for(int j = 0;j<30;j++)
			{
				temp.push_back(grid[i][j]);
				if(grid[i][j]==1)
					one++;
				else
					two++;
			}
			this->grid.push_back(temp);
		}
		if(one == two )
			turn = 0;
		else
			turn = 1;
		valid = true;

	//	std::cout<<"left this stupid constructore\n";
	}



	Grid& Grid::operator=(Grid const & newGrid)
	{
		player_one_head_x = newGrid.getPlayerOneHeadX();
		player_one_head_y = newGrid.getPlayerOneHeadY();
		player_two_head_x = newGrid.getPlayerTwoHeadX();
		player_two_head_y = newGrid.getPlayerTwoHeadY();
		copy(newGrid.grid.begin(),newGrid.grid.end(),grid.begin());
		return *this;
	}
	Grid& Grid::operator()(Grid& newGrid)
	{
		*(this) = newGrid;
		return *this;
	}
	Grid::~Grid() {
		for(int i = 0;i<30;i++)
			grid[i].~vector();
		grid.~vector();
		delete [] state;
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
	std::vector<int>& Grid::operator[](int x)
	{
		return this->grid[x];
	}
	std::string Grid::printGrid()
	{
	//	std::cout<<"trying to print\n";
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
	 * 6..230 	laplace smoothened probabilities using (current_player_cout +1)/(total_count+12)
	 * 			for each 2x2 square
	*/
	double * Grid::getAfterState(int digit)
	{
		int available = 0;
		int mine=0;
		int other=0;
		int pos = 6;
		int oppo;
		if(digit == 1)
			oppo = 3;
		else
			oppo = 1;
#pragma omp parallel for
		for(int i = 0;i<30;i++)
		{
			for(int j = 0;j<30;j++)
			{
				if(grid[j][i] == digit)//number of ones
				{
#pragma omp critical
					mine++;
				}
				if(grid[j][i] == oppo)//number of twos
				{
#pragma omp critical
					other++;
				}
			}
		}
		//bool finished  = false;

		
		if(grid[player_one_head_y][player_one_head_x] != digit &&
				grid[player_two_head_y][player_two_head_x] != digit &&
				grid[player_one_head_y][player_one_head_x] != 0 &&
				grid[player_two_head_y][player_two_head_x] != 0 )
		{
			finished = true;
			mine++;
		}

		if(mine == other)
		{
			turn = 1;
			state[2] = 1;
		}
		else
		{
			turn = 0;
			state[2] = 0;
		}
		for(int j = 0; j<30;j++)
		{
			for(int i = 0 ;i<30;i++)
			{
				if(i%2 ==0 && j%2 == 0)//get the states for every four boxes
				{
					int inner_mine = 0;
					int inner_other = 0;
					int not_zero = 0;
					for(int v = j;v<j+2;v++)
					{
		//std::cout<<"searching for after state\n";
						for(int w = i;w<i+2;w++)
						{
							if(grid[v][w] == mine)
							{
								inner_mine++;
								not_zero++;
								continue;
							}
							if(grid[v][w]==oppo)
							{
								inner_other++;
								not_zero++;
								continue;
							}
							if(grid[v][w]!=0)
							{
								not_zero++;
								continue;
							}
						}
					}

					state[pos] = (inner_mine +1.0)/(not_zero+12.0);//laplace smoothing
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

			}
		}

		state[3] = (available+1-state[1]+1-state[0])/(900.0-58.0);
		state[4] = ((player_one_head_y * 30) -58 + player_one_head_x+1)/(900.0-58.0);
		state[5] = ((player_two_head_y * 30 ) -58 + player_two_head_x +1)/(900.0-58.0);

		/*if (finished){
		for(int i = 0;i<231;i++)
			if(i >5)
			std::cout<<i-5<<" "<<state[i]<<std::endl;
		std::cout<<digit<<std::endl;
		}*/
		return state;
	}


	 /*Array that gives the state of the board
	         * 0 - binary value, 1 if the north pole is occupied
	         * 1 - binary value,  1 if the south pole is occupied
	         * 2 - turn 0 for player one, 1 for player two
	         * 3 - fraction of available spots
	         * 4 - fractional positition of the player one head
	         * 5 - fractional position of player two head
	         *
	         * 6..230       laplace smoothened probabilities using (current_player_cout +1)/(total_count+12)
	         *                      for each 2x2 square
	        */
/*
    double * Grid::getAfterState()
    {
            int available = 0;
            int one=0;
            int two=0;
            int pos = 6;
#pragma omp parallel for
            for(int i = 0;i<30;i++)
            {
                    for(int j = 0;j<30;j++)
                    {
                            if(grid[j][i] == 1)//number of ones
                            {
#pragma omp critical
                                    one++;
                            }
                            if(grid[j][i] == 3)//number of twos
                            {
#pragma omp critical
                                    two++;
                            }
                    }
            }
    //      bool finished  = false;

            if(one == two)
            {
                    turn = 1;
                    state[2] = 1;
            }
            else
            {
                    turn = 0;
                    state[2] = 0;
            }
            if(grid[player_one_head_y][player_one_head_x] != 1 && grid[player_one_head_y][player_one_head_x]!=0)
            {
                    //finished = true;
                    one++;
                    turn = 0;
            }
            if(grid[player_two_head_y][player_two_head_x] != 3 && grid[player_two_head_y][player_two_head_x] !=0)
            {
            //      finished = true;
                    two++;
                    turn = 1;
            }

            for(int j = 0; j<30;j++)
            {
                    for(int i = 0 ;i<30;i++)
                    {
                            if(i%2 ==0 && j%2 == 0)//get the states for every four boxes
                            {
                                    int inner_one = 0;
                                    int inner_two = 0;
                                    int not_zero = 0;
                                    for(int v = j;v<j+2;v++)
                                    {


	  //std::cout<<"searching for after state\n";
	                                                for(int w = i;w<i+2;w++)
	                                                {
	                                                        if(grid[v][w] == 1)
	                                                        {
	                                                                inner_one++;
	                                                                not_zero++;
	                                                                continue;
	                                                        }
	                                                        if(grid[v][w]==3)
	                                                        {
	                                                                inner_two++;
	                                                                not_zero++;
	                                                                continue;
	                                                        }
	                                                        if(grid[v][w]!=0)
	                                                        {
	                                                                not_zero++;
	                                                                continue;
	                                                        }
	                                                }
	                                        }

	                                        if(turn == 0)
	                                        {
	                                                state[pos] = (inner_one +1.0)/(not_zero+12.0);//laplace smoothing
	                                        }
	                                        else
	                                        {
	                                                state[pos] =  (inner_two +1.0)/(not_zero+12.0);//laplace smoothin
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

	                        }
	                }

	                state[3] = (available+1-state[1]+1-state[0])/(900.0-58.0);
	                state[4] = ((player_one_head_y * 30) -58 + player_one_head_x+1)/(900.0-58.0);
	                state[5] = ((player_two_head_y * 30 ) -58 + player_two_head_x +1)/(900.0-58.0);

	             // std::cout<<std::endl<<std::endl<<std::endl;
	             //   if (finished)
	            //    for(int i = 0;i<231;i++)
	             //           if(i >5)
	          //              std::cout<<i-5<<" "<<state[i]<<std::endl;

	                return state;
	        }*/

}
