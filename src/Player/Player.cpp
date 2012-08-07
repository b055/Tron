/*
 * Player.cpp
 *
 *  Created on: 03 Aug 2012
 *      Author: Ivan Nelson Togboa Cadri
 */

#include "Player.h"
namespace tron{
	Player::Player(){

	}
	Player::Player(int digit):digit(digit){


	}
	Player::~Player() {
		delete &grid;
	}
	void Player::possibleMoves(Grid** result)
	{
		//check if at poles and get possible moves
		//check if at edges and get possible moves
		int count = 0;
		for(int i = 0;i<30;i++)
		{
			if(count>1)
				break;
			for(int j = 0 ;j<30;j++)
			{
				if(count>1)
					break;
				if(grid[i][j]!=0){
					count++;
				}
			}
		}
		if(count == 0)///first move
		{
			std::cout<<"playing first movve\n";
			srand(time(NULL));
			int x = rand()%30;
			int y = rand()%30;
			(*result[0]) = grid;
			(*result[0])[y][x] = digit;
			(*result[0]).setPlayerOneHeadX(x);
			(*result[0]).setPlayerOneHeadY(y);
			(*result[0]).isValid(true);
			std::cout<<"out of here\n";
			return;
		}
		else if(count ==1)
		{
			//PLAYING SECOND MOVE
			std::cout<<"playing second move\n";
			(*result[0]) = grid;
			//std::cout<<"made copy\n";

			if(oppo_y>0&& oppo_y<29)
			{
				int new_x = (oppo_x+15)%30;
				int new_y = oppo_y;
				(*result[0]).setPlayerOneHead(oppo_x,oppo_y);
				(*result[0]).setPlayerTwoHead(new_x,new_y);
				(*result[0]).isValid(true);
				(*result[0])[new_y][new_x] = digit;

			}else
			{
				int new_x = oppo_x;
				int new_y = 29-oppo_y;
				(*result[0]).setPlayerOneHead(oppo_x,oppo_y);
				(*result[0]).setPlayerTwoHead(new_x,new_y);
				(*result[0]).isValid(true);
				(*result[0])[new_y][new_x] = digit;
			}
			return;
		}
		else if(this->y==0)//top
		{
			std::cout<<"topMoves\n";
			topMoves(result);
		}
		else if (this->y==29)//bottom
		{
			std::cout<<"bottommoves\n";
			bottomMoves(result);
		}
		else//somewhere in the middle
		{
			std::cout<<"middlemoves\n";
			middleMoves(result);
		}

	}
	//print players grid
	std::string Player::printGrid()
	{

		return this->grid.printGrid();
	}
	//possible moves for a player at the top
	void Player::topMoves(Grid** result)
	{
#pragma omp parallel for
		for(int i = 0;i<30;i++)
		{
			if(grid[1][i]==0)
			{
				(*result[i]) = grid;
				(*result[i])[1][i]=digit;
				if(digit == 1)
				{
					(*result[i]).setPlayerOneHead(i,1);
					(*result[i]).setPlayerTwoHead(oppo_x,oppo_y);
				}
				else
				{
					(*result[i]).setPlayerTwoHead(i,1);
					(*result[i]).setPlayerOneHead(oppo_x,oppo_y);
				}
				(*result[i] ).isValid(true);
			}
			else
			{
				result[i]->isValid(false);
			}
		}
	}

	//possible moves for a player at the bottom
	void Player::bottomMoves(Grid** result)

	{
#pragma omp parallel for
		for(int i = 0; i<30;i++)
		{
			if(grid[28][i]==0)
			{
				(*result[i] ) = grid;

				(*result[i] )[28][i] = digit;
				int * two = new int[2];
				int * one = new int[2];
				if(digit == 1)
				{
					(*result[i] ).setPlayerOneHead(i,28);
					(*result[i] ).setPlayerTwoHead(oppo_x,oppo_y);
				}
				else
				{
					(*result[i] ).setPlayerOneHead(oppo_x,oppo_y);
					(*result[i] ).setPlayerTwoHead(i,28);

				}
				(*result[i] ).isValid(true);
			}
			else
			{
				result[i]->isValid(false);
			}
		}
	}

	//possible moves for a player somewhere in the middle of the sphere
	void Player::middleMoves(Grid** result)
	{
		std::cout<<"starting middle moves\n";

		int count =0;
		if(this->y ==28)//almost bottom
		{
			bool check = true;

			for(int i =0;i<30;i++)
			{
				if(grid[29][i]!=0)
				{
					check = false;
					break;
				}
			}
			if(check){//add move to bottom pole
				result[count++]= &downMove(28);
			}
			//add up
			result[count++] = &upMove(y);
		}
		else if(this->y ==1)//almost top
		{
			bool check = true;
			for(int i =0;i<30;i++)
			{
				if(grid[0][i]!=0)
				{
					check = false;
					break;
				}
			}
			if(check){//add move to top pole
				result[count++]= &upMove(1);
			}
			//add down
			result[count++] = &downMove(y);
		}
		else
		{
			//normal y's
			result[count++] = &upMove(y);
			result[count++] = &downMove(y);
		}
		if(this->x==29)//right edge
		{
			std::cout<<"right edge\n";
			if(grid[this->y][0]==0)//can wrap around the right
			{
				result[count++] = &rightMove(-1);
			}
			//add left

			result[count++] = &leftMove(x);
		}
		else if(x==0)//left edge
		{
			if(grid[this->y][29]==0){//can wrap around the left
				result[count++] = &leftMove(30);
			}
			//add right
			result[count++] = &rightMove(x);
		}
		else
		{//normal x's
			result[count++] = &leftMove(x);
			result[count++] = &rightMove(x);
		}
	}
	//returns afeterstate for up move if possible, otherwise returns null
	Grid& Player::upMove(int y){
		std::cout<<"up move\n";
		Grid *final = new Grid();

		if(this->grid[y+1][x]==0)
		{
			*final = (grid);
			(*final)[y+1][x] = digit;

			if(digit == 1)
			{
				(*final).setPlayerOneHead(x,y+1);
				(*final).setPlayerTwoHead(oppo_x,oppo_y);
			}
			else
			{
				(*final).setPlayerOneHead(oppo_x,oppo_y);
				(*final).setPlayerTwoHead(x,y+1);
			}
			(*final).isValid(true);
			return (*final);
		}
		else {
			(*final).isValid(false);
			return (*final);
		}
	}
	//returns afterstate for down move if possible, otherwise returns null
	Grid& Player::downMove(int y)
	{
		std::cout<<"down move\n";
		Grid *final = new Grid();
		if(this->grid[y-1][x]==0)
		{
			*final = (grid);
			(*final)[y-1][x] = digit;

			if(digit == 1)
			{
				(*final).setPlayerOneHead(x,y-1);
				(*final).setPlayerTwoHead(oppo_x,oppo_y);
			}
			else
			{
				(*final).setPlayerOneHead(oppo_x,oppo_y);
				(*final).setPlayerTwoHead(x,y-1);
			}
			(*final).isValid(true);
			return *final;
		}
		else{
			(*final).isValid(false);
			return *(final);
		}
	}
	//return afterstate for left move if possible, otherwise returns null
	Grid& Player::leftMove(int x)
	{
		std::cout<<"left move\n";
		Grid *final = new Grid();
		if(this->grid[y][x-1]==0)
		{
			*final = (grid);
			(*final)[y][x-1] = digit;

			if(digit == 1)
			{
				(*final).setPlayerOneHead(x-1,y);
				(*final).setPlayerTwoHead(oppo_x,oppo_y);
			}
			else
			{
				(*final).setPlayerOneHead(oppo_x,oppo_y);
				(*final).setPlayerTwoHead(x-1,y);
			}
			(*final).isValid(true);
			return *final;
		}
		else {
			(*final).isValid(false);
			return (*final);
		}
	}

	//return after state for right move is possible, otherwise return null
	Grid& Player::rightMove(int x)
	{
		std::cout<<"right move\n";

		Grid *final = new Grid();
		if(this->grid[y][x+1]==0)
		{
			*final = (grid);
			(*final)[y][x+1] = digit;

			if(digit == 1)
			{
				(*final).setPlayerOneHead(x+1,y);
				(*final).setPlayerTwoHead(oppo_x,oppo_y);
			}
			else
			{
				(*final).setPlayerOneHead(oppo_x,oppo_y);
				(*final).setPlayerTwoHead(x+1,y);

			}
			(*final).isValid(true);
			return *final;
		}
		else{
			(*final).isValid(false);
			return *(final);
		}
	}


	void Player::setHead(Grid& newgrid)
	{
		if(digit == 1)
		{
			x= newgrid.getPlayerOneHeadX();
			y = newgrid.getPlayerOneHeadY();
		}
		else
		{
			x= newgrid.getPlayerTwoHeadX();
			y = newgrid.getPlayerTwoHeadY();
		}

	}
	void Player::setGrid(Grid& newGrid)
	{
		grid = newGrid;
	}
}
