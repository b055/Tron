/*
 * Player.cpp
 *
 *  Created on: 03 Aug 2012
 *      Author: Ivan Nelson Togboa Cadri
 */

#include "Player.h"
namespace tron{
	Player::Player(int digit,int width):digit(digit),width(width),grid(new Grid(width)){
		debug = false;
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
		grid->reset();
	}

	void Player::possibleMoves(Grid & grid,Grid** result)
	{
		//check if at poles and get possible moves
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
				if((grid)[i][j]!=0){
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
			(*result[0]) = grid;
			(*result[0])[y][x] = digit;
			(*result[0]).setPlayerOneHeadX(x);
			(*result[0]).setPlayerOneHeadY(y);
			(*result[0]).isValid(true);
			return;
		}
		else if(count ==1)
		{
			//PLAYING SECOND MOVE
			//std::cout<<"playing second move\n";
			(*result[0]) = grid;
			//std::cout<<"made copy\n";
			int new_x,new_y;
			if(oppo_y>0&& oppo_y<width-1)
			{
				new_x = (oppo_x+(width/2))%width;
				new_y = oppo_y;
				(*result[0]).isValid(true);
				(*result[0])[new_y][new_x] = digit;

			}else
			{
				new_x = oppo_x;
				new_y = width-1-oppo_y;
				(*result[0]).isValid(true);
				(*result[0])[new_y][new_x] = digit;
			}
			this->x = new_x;
			this->y  =new_y;

			(*result[0]).setPlayerOneHead(oppo_x,oppo_y);
			(*result[0]).setPlayerTwoHead(new_x,new_y);
			return;
		}
		else if(this->y==0)//top
		{
			//std::cout<<"topMoves\n";
			topMoves(grid,result);
		}
		else if (this->y==width-1)//bottom
		{
			//std::cout<<"bottommoves\n";
			bottomMoves(grid,result);
		}
		else//somewhere in the middle
		{
			//std::cout<<"middlemoves\n";
			middleMoves(grid,result);
		}
		for(int i = 0;i<width;i++)
		{
			if(result[i]->isValid())
				return;
		}

		//std::cout<<"go to fetch random move\n";
		randomMove(result[0]);

	}
	//print players grid
	std::string Player::printGrid()
	{

		return this->grid->printGrid();
	}
	//possible moves for a player at the top
	void Player::topMoves(Grid& grid,Grid** result)
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
	void Player::bottomMoves(Grid &grid,Grid** result)

	{
		if(debug)
			std::cout<<"getting bottom move"<<std::endl;
//#pragma omp parallel for
		for(int i = 0; i<width;i++)
		{
			if(grid[width-2][i]==0)
			{
				if(debug){
					std::cout<<"true "<<i<<std::endl;
					std::cout<<result[i]->printGrid();
					std::cout<<"other\n";
				}
				(*result[i] ) = grid;
				if(debug)
					std::cout<<result[i]->printGrid();
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
				if(debug)
					std::cout<<"false "<<i<<std::endl;
				result[i]->isValid(false);
			}
		}
	}

	//possible moves for a player somewhere in the middle of the sphere
	void Player::middleMoves(Grid & grid,Grid** result)
	{
		if(debug)
			std::cout<<"starting middle moves\n";

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
				upMove(grid,y,result[count++]);

			}
			//add up

			downMove(grid,y,result[count++]);
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
				downMove(grid,1,result[count++]);
			}
			//add down
			upMove(grid,y,result[count++]);
		}
		else
		{
			//normal y's
			upMove(grid,y,result[count++]);
			downMove(grid,y,result[count++]);
		}
		if(this->x==width-1)//right edge
		{
			//std::cout<<"right edge\n";
			if(grid[this->y][0]==0)//can wrap around the right
			{
				rightMove(grid,-1,result[count++]);
			}
			//add left

			leftMove(grid,x,result[count++]);
		}
		else if(x==0)//left edge
		{
			//std::cout<<"left edge\n";
			if(grid[this->y][width-1]==0){//can wrap around the left
				leftMove(grid,width,result[count++]);
			}
			//add right
			rightMove(grid,x,result[count++]);
		}
		else
		{//normal x's
			leftMove(grid,x,result[count++]);
			rightMove(grid,x,result[count++]);
		}
	}
	//returns afeterstate for up move if possible, otherwise returns null
	void Player::upMove(Grid& grid,int y, Grid * result){
		if(debug)
			std::cout<<"up move\n";
		if(grid[y+1][x]==0)
		{
			*result = grid;
			(*result)[y+1][x] = digit;

			if(digit == 1)
			{
				(*result).setPlayerOneHead(x,y+1);
				(*result).setPlayerTwoHead(oppo_x,oppo_y);
			}
			else
			{
				(*result).setPlayerOneHead(oppo_x,oppo_y);
				(*result).setPlayerTwoHead(x,y+1);
			}
			(*result).isValid(true);
		}
		else {
			(*result).isValid(false);
		}
	}
	//returns afterstate for down move if possible, otherwise returns null
	void Player::downMove(Grid & grid,int y, Grid * result)
	{
		if(debug)
			std::cout<<"down move\n";
		if(grid[y-1][x]==0)
		{
			*result = grid;
			(*result)[y-1][x] = digit;

			if(digit == 1)
			{
				(*result).setPlayerOneHead(x,y-1);
				(*result).setPlayerTwoHead(oppo_x,oppo_y);
			}
			else
			{
				(*result).setPlayerOneHead(oppo_x,oppo_y);
				(*result).setPlayerTwoHead(x,y-1);
			}
			(*result).isValid(true);
		}
		else{
			(*result).isValid(false);
		}
	}
	//return afterstate for left move if possible, otherwise returns null
	void Player::leftMove(Grid& grid,int x, Grid * result)
	{
		if(debug)
			std::cout<<"left move\n";
		if(grid[y][x-1]==0)
		{
			*result = grid;
			(*result)[y][x-1] = digit;

			if(digit == 1)
			{
				(*result).setPlayerOneHead(x-1,y);
				(*result).setPlayerTwoHead(oppo_x,oppo_y);
			}
			else
			{
				(*result).setPlayerOneHead(oppo_x,oppo_y);
				(*result).setPlayerTwoHead(x-1,y);
			}
			(*result).isValid(true);
		}
		else {
			(*result).isValid(false);
		}
	}

	//return after state for right move is possible, otherwise return null
	void Player::rightMove(Grid& grid,int x, Grid * result)
	{
		if(debug)
			std::cout<<"right move\n";

		if(grid[y][x+1]==0)
		{
			*result = grid;
			(*result)[y][x+1] = digit;
			if(debug)
			{
				std::cout<<result->printGrid();
				std::cout<<"difference\n"<<grid.printGrid();
			}
			if(digit == 1)
			{
				(*result).setPlayerOneHead(x+1,y);
				(*result).setPlayerTwoHead(oppo_x,oppo_y);
			}
			else
			{
				(*result).setPlayerOneHead(oppo_x,oppo_y);
				(*result).setPlayerTwoHead(x+1,y);

			}
			(*result).isValid(true);
		}
		else{
			(*result).isValid(false);
		}
	}


	void Player::setHead(Grid& newgrid)
	{
		if(digit == 1)
		{
			x= newgrid.getPlayerOneHeadX();
			y = newgrid.getPlayerOneHeadY();
			oppo_x  = newgrid.getPlayerTwoHeadX();
			oppo_y = newgrid.getPlayerTwoHeadY();
		}
		else
		{
			x= newgrid.getPlayerTwoHeadX();
			y = newgrid.getPlayerTwoHeadY();
			oppo_x= newgrid.getPlayerOneHeadX();
			oppo_y = newgrid.getPlayerOneHeadY();
		}

	}


	/*
	 * make a random move, argument is the current game grid
	 */
	void Player::randomMove(Grid* result)
	{
		//std::cout<<"Making a random move\n";

		*result= *grid;
		std::srand(std::time(NULL));
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
		(*result)[move_y][move_x] = (*result)[move_y][move_x] + digit;
		if(digit == 1)
		{
			(result)->setPlayerOneHead(move_x,move_y);
		}
		else
		{
			(result)->setPlayerTwoHead(move_x,move_y);
		}
		(result)->isValid(true);
	}

}
