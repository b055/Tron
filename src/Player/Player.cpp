/*
 * Player.cpp
 *
 *  Created on: 03 Aug 2012
 *      Author: Ivan Nelson Togboa Cadri
 */

#include "Player.h"
namespace tron{
	Player::Player(){
		width  = 10;
		grid = *new Grid();
	}
	Player::Player(int digit):digit(digit){
		width = 10;
		grid = *new Grid();

		finalRight =new Grid();
		finalLeft=new Grid();
		finalUp=new Grid();
		finalDown=new Grid();
		finalRandom=new Grid();
	}
	Player::~Player() {
		delete &grid;
		delete net;
	}
	void Player::reset()
	{
		digit = 0;
		oppo_x = 0;
		oppo_y = 0;
		x = 0;
		y = 0;
		grid.reset();
	}

	void Player::possibleMoves(Grid** result)
	{
		//check if at poles and get possible moves
		//check if at edges and get possible moves
		int count = 0;
		for(int i = 0;i<width;i++)
		{
			if(count>1)
				break;
			for(int j = 0 ;j<width;j++)
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
			//std::cout<<"playing first movve\n";
			srand(time(NULL));
			int x = rand()%width;
			int y = rand()%width;
			(*result[0]) = grid;
			(*result[0]).getAfterState(digit);
			(*result[0])[y][x] = digit;
			(*result[0]).setPlayerOneHeadX(x);
			(*result[0]).setPlayerOneHeadY(y);
			(*result[0]).isValid(true);
			//std::cout<<"playefd first move";
			return;
		}
		else if(count ==1)
		{
			//PLAYING SECOND MOVE
			//std::cout<<"playing second move\n";
			(*result[0]) = grid;
			//std::cout<<"made copy\n";

			if(oppo_y>0&& oppo_y<width-1)
			{
				int new_x = (oppo_x+(width/2))%width;
				int new_y = oppo_y;
				(*result[0]).setPlayerOneHead(oppo_x,oppo_y);
				(*result[0]).setPlayerTwoHead(new_x,new_y);
				(*result[0]).isValid(true);
				(*result[0])[new_y][new_x] = digit;

			}else
			{
				int new_x = oppo_x;
				int new_y = width-1-oppo_y;
				(*result[0]).setPlayerOneHead(oppo_x,oppo_y);
				(*result[0]).setPlayerTwoHead(new_x,new_y);
				(*result[0]).isValid(true);
				(*result[0])[new_y][new_x] = digit;
			}
			//std::cout<<"finished second\n";
			return;
		}
		else if(this->y==0)//top
		{
			//std::cout<<"topMoves\n";
			topMoves(result);
		}
		else if (this->y==width-1)//bottom
		{
			//std::cout<<"bottommoves\n";
			bottomMoves(result);
		}
		else//somewhere in the middle
		{
			//std::cout<<"middlemoves\n";
			middleMoves(result);
		}
		for(int i = 0;i<width;i++)
		{
			if(result[i]->isValid())
				return;
		}
		//std::cout<<"go to fetch random move\n";
		(result[0]) = &randomMove();

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
		for(int i = 0;i<width;i++)
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
		for(int i = 0; i<width;i++)
		{
			if(grid[width-2][i]==0)
			{
				(*result[i] ) = grid;

				(*result[i] )[width-2][i] = digit;
				if(digit == 1)
				{
					(*result[i] ).setPlayerOneHead(i,width-2);
					(*result[i] ).setPlayerTwoHead(oppo_x,oppo_y);
				}
				else
				{
					(*result[i] ).setPlayerOneHead(oppo_x,oppo_y);
					(*result[i] ).setPlayerTwoHead(i,width-2);

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
		//std::cout<<"starting middle moves\n";

		int count =0;
		if(this->y ==width-2)//almost bottom
		{
			bool check = true;

			for(int i =0;i<width;i++)
			{
				if(grid[width-1][i]!=0)
				{
					check = false;
					break;
				}
			}
			if(check){//add move to bottom pole
				result[count++]= &upMove(width-2);
			}
			//add up
			result[count++] = &downMove(y);
		}
		else if(this->y ==1)//almost top
		{
			bool check = true;
			for(int i =0;i<width;i++)
			{
				if(grid[0][i]!=0)
				{
					check = false;
					break;
				}
			}
			if(check){//add move to top pole
				result[count++]= &downMove(1);
			}
			//add down
			result[count++] = &upMove(y);
		}
		else
		{
			//normal y's
			result[count++] = &upMove(y);
			result[count++] = &downMove(y);
		}
		if(this->x==width-1)//right edge
		{
			//std::cout<<"right edge\n";
			if(grid[this->y][0]==0)//can wrap around the right
			{
				result[count++] = &rightMove(-1);
			}
			//add left

			result[count++] = &leftMove(x);
		}
		else if(x==0)//left edge
		{
			//std::cout<<"left edge\n";
			if(grid[this->y][width-1]==0){//can wrap around the left
				result[count++] = &leftMove(width);
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
		//std::cout<<"up move\n";
		if(this->grid[y+1][x]==0)
		{
			*finalUp = (grid);
			(*finalUp)[y+1][x] = digit;

			if(digit == 1)
			{
				(*finalUp).setPlayerOneHead(x,y+1);
				(*finalUp).setPlayerTwoHead(oppo_x,oppo_y);
			}
			else
			{
				(*finalUp).setPlayerOneHead(oppo_x,oppo_y);
				(*finalUp).setPlayerTwoHead(x,y+1);
			}
			(*finalUp).isValid(true);
			return (*finalUp);
		}
		else {
			(*finalUp).isValid(false);
			return (*finalUp);
		}
	}
	//returns afterstate for down move if possible, otherwise returns null
	Grid& Player::downMove(int y)
	{
		//std::cout<<"down move\n";
		if(this->grid[y-1][x]==0)
		{
			*finalDown = (grid);
			(*finalDown)[y-1][x] = digit;

			if(digit == 1)
			{
				(*finalDown).setPlayerOneHead(x,y-1);
				(*finalDown).setPlayerTwoHead(oppo_x,oppo_y);
			}
			else
			{
				(*finalDown).setPlayerOneHead(oppo_x,oppo_y);
				(*finalDown).setPlayerTwoHead(x,y-1);
			}
			(*finalDown).isValid(true);
			return *finalDown;
		}
		else{
			(*finalDown).isValid(false);
			return *(finalDown);
		}
	}
	//return afterstate for left move if possible, otherwise returns null
	Grid& Player::leftMove(int x)
	{
		//std::cout<<"left move\n";
		if(this->grid[y][x-1]==0)
		{
			*finalLeft = (grid);
			(*finalLeft)[y][x-1] = digit;

			if(digit == 1)
			{
				(*finalLeft).setPlayerOneHead(x-1,y);
				(*finalLeft).setPlayerTwoHead(oppo_x,oppo_y);
			}
			else
			{
				(*finalLeft).setPlayerOneHead(oppo_x,oppo_y);
				(*finalLeft).setPlayerTwoHead(x-1,y);
			}
			(*finalLeft).isValid(true);
			return *finalLeft;
		}
		else {
			(*finalLeft).isValid(false);
			return (*finalLeft);
		}
	}

	//return after state for right move is possible, otherwise return null
	Grid& Player::rightMove(int x)
	{
		//std::cout<<"right move\n";

		if(this->grid[y][x+1]==0)
		{
			*finalRight = (grid);
			(*finalRight)[y][x+1] = digit;

			if(digit == 1)
			{
				(*finalRight).setPlayerOneHead(x+1,y);
				(*finalRight).setPlayerTwoHead(oppo_x,oppo_y);
			}
			else
			{
				(*finalRight).setPlayerOneHead(oppo_x,oppo_y);
				(*finalRight).setPlayerTwoHead(x+1,y);

			}
			(*finalRight).isValid(true);
			return *finalRight;
		}
		else{
			(*finalRight).isValid(false);
			return *(finalRight);
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

	/*
	 * make a random move, argument is the current game grid
	 */
	Grid& Player::randomMove()
	{
		//std::cout<<"Making a random move\n";

		*finalRandom= grid;
		srand(time(NULL));
		int move_x= x;
		int move_y = y;
		if(this->y == width-1)	//south pole move
		{
			move_x = rand() %width;
			move_y = width-2;
		}
		else if(this->y == 0)// north pole move
		{
			move_x= rand() %width;
			move_y = 1;
		}
		else if(this->x == 0)
		{
			int move = int(rand() % 4);
			if(move == 0)
			{
				move_y = y+1;
			}
			else if(move == 1)
			{
				move_y = y-1;
			}
			else if(move == 2)
			{
				move_x = x+1;
			}
			else if(move == 3)
			{
				move_x = width-1;
			}
		}
		else if(this->x==width-1)
		{
			int move = int(rand() % 4);
			if(move == 0)
			{
				move_y = y+1;
			}
			else if(move == 1)
			{
				move_y = y-1;
			}
			else if(move == 2)
			{
				move_x = 0;
			}
			else if(move == 3)
			{
				move_x = x-1;
			}
		}
		else//middle move
		{
			int move = int(rand() % 4);
			if(move == 0)
			{
				move_y = y+1;
			}
			else if(move == 1)
			{
				move_y = y-1;
			}
			else if(move == 2)
			{
				move_x = x+1;
			}
			else if(move == 3)
			{
				move_x = x-1;
			}
		}
		(*finalRandom)[move_y][move_x] = (*finalRandom)[move_y][move_x] + digit;
		if(digit == 1)
		{
			(finalRandom)->setPlayerOneHead(move_x,move_y);
		}
		else
		{
			(finalRandom)->setPlayerTwoHead(move_x,move_y);
		}
		(finalRandom)->isValid(true);
		return (*finalRandom);
	}
}
