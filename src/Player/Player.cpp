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
	/*	delete &grid;
		delete net;*/
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

	void Player::possibleMoves(Grid & grid,std::vector<Grid>& result)
	{
		//check if at poles and get possible moves
		//check if at edges and get possible moves
		//debug = true;
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
			std::cout<<"playing first movve\n";
			std::srand(time(NULL));
			int x = rand()%width;
			int y = rand()%width;
			Grid *out = new Grid(grid);
			
			if(y ==0){
				(*out)[0][0] = digit;
				out->setPlayerOneHead(0,0);
			}
			else if(y== width-1)
			{
				(*out)[width-1][0] = digit;
				out->setPlayerOneHead(0,width-1);
			}
			else{
				out->setPlayerOneHead(x,y);
				(*out)[y][x] = digit;
			}
			result.push_back(*out);
			return;
		}
		else if(count ==1)
		{
			//PLAYING SECOND MOVE
			std::cout<<"playing second move\n";
			Grid *out = new Grid(grid);
			//std::cout<<"made copy\n";
			int new_x,new_y;
			if(grid.getPlayerOneHeadY()>0&& grid.getPlayerOneHeadY()<width-1)
			{
				new_x = (grid.getPlayerOneHeadX()+(width/2))%width;
				new_y = grid.getPlayerOneHeadY();
				(*out)[new_y][new_x] = digit;

			}else
			{
				new_x = grid.getPlayerOneHeadX();
				new_y = width-1-grid.getPlayerOneHeadY();
				(*out)[new_y][new_x] = digit;
			}
			(*out).setPlayerOneHead(grid.getPlayerOneHeadX(),grid.getPlayerOneHeadY());
			(*out).setPlayerTwoHead(new_x,new_y);
			result.push_back(*out);
			return;
		}
		if(digit == 1)
		{
			if(grid.getPlayerOneHeadY()==0)//top
			{
				//std::cout<<"topMoves\n";
				topMoves(grid,result);
			}
			else if (grid.getPlayerOneHeadY()==width-1)//bottom
			{
				//std::cout<<"bottommoves\n";
				bottomMoves(grid,result);
			}
			else//somewhere in the middle
			{
				//std::cout<<"middlemoves\n";
				middleMoves(grid,result);
			}
			if(result.size()>0)
				return;
			//std::cout<<digit<<" playing a random move here\n ";
			randomMove(grid,result);
		}
		else
		{
			if(grid.getPlayerTwoHeadY()==0)//top
			{
				//std::cout<<"topMoves\n";
				topMoves(grid,result);
			}
			else if (grid.getPlayerTwoHeadY()==width-1)//bottom
			{
				//std::cout<<"bottommoves\n";
				bottomMoves(grid,result);
			}
			else//somewhere in the middle
			{
				//std::cout<<"middlemoves\n";
				middleMoves(grid,result);
			}
			if(result.size() >0)
				return;
		//	std::cout<<digit<<" playing a random move here\n ";
			randomMove(grid,result);
		}


	}
	//print players grid
	std::string Player::printGrid()
	{

		return this->grid->printGrid();
	}	//possible moves for a player at the top
	void Player::topMoves(Grid& grid,std::vector<Grid>& result)
	{
		int count = 0;
		if(digit== 1)
		{
	#pragma omp parallel for
			for(int i = 0;i<width;i++)
			{
				if(grid[1][i]==0)
				{
					Grid *out = new Grid(grid);
					(*out)[1][i]=digit;

					(*out).setPlayerOneHead(i,1);
					result.push_back(*out);
				}
			}

		}
		else
		{

	#pragma omp parallel for
			for(int i = 0;i<width;i++)
			{
				if(grid[1][i]==0)
				{
					Grid *out = new Grid(grid);
					(*out)[1][i]=digit;

					(*out).setPlayerTwoHead(i,1);
					result.push_back(*out);
				}
			}
		}
	}

	//possible moves for a player at the bottom
	void Player::bottomMoves(Grid &grid,std::vector<Grid>& result)

	{
		
		if(debug)
			std::cout<<"getting bottom move"<<std::endl;
		if(digit == 1)
		{
	//#pragma omp parallel for
			for(int i = 0; i<width;i++)
			{
				if(grid[width-2][i]==0)
				{
					if(debug){
						std::cout<<"true "<<i<<std::endl;
						std::cout<<"other\n";
					}
					Grid *out = new Grid(grid);
					(*out)[width-2][i] = digit;

					(*out).setPlayerOneHead(i,width-2);
					result.push_back(*out);
				}

			}
		}
		else
		{
	//#pragma omp parallel for
			for(int i = 0; i<width;i++)
			{
				if(grid[width-2][i]==0)
				{
					if(debug){
						std::cout<<"true "<<i<<std::endl;
						std::cout<<"other\n";
					}
					Grid *out = new Grid(grid);
					(*out)[width-2][i] = digit;

					(*out).setPlayerTwoHead(i,width-2);

					result.push_back(*out);
				}
			}
		}
	}

	//possible moves for a player somewhere in the middle of the sphere
	void Player::middleMoves(Grid & grid,std::vector<Grid>& result)
	{
		if(debug)
			std::cout<<"starting middle moves\n";

		if(digit == 1)
		{
			if(grid.getPlayerOneHeadY() ==width-2)//almost bottom
			{
				
				if(grid[width-1][0]!=0)
				{
					upMove(grid,grid.getPlayerOneHeadY(),result);
				}
				
				//add up

				downMove(grid,grid.getPlayerOneHeadY(),result);
			}
			else if(grid.getPlayerOneHeadY() ==1)//almost top
			{
				if(grid[0][0]!=0)
				{
					downMove(grid,1,result);
				}
				
				//add down
				upMove(grid,grid.getPlayerOneHeadY(),result);
			}
			else
			{
				//normal y's
				upMove(grid,grid.getPlayerOneHeadY(),result);
				downMove(grid,grid.getPlayerOneHeadY(),result);
			}
			if(grid.getPlayerOneHeadX()==width-1)//right edge
			{
				//std::cout<<"right edge\n";
				if(grid[grid.getPlayerOneHeadY()][0]==0)//can wrap around the right
				{
					rightMove(grid,-1,result);
				}
				//add left

				leftMove(grid,grid.getPlayerOneHeadX(),result);
			}
			else if(grid.getPlayerOneHeadX()==0)//left edge
			{
				//std::cout<<"left edge\n";
				if(grid[grid.getPlayerOneHeadY()][width-1]==0){//can wrap around the left
					leftMove(grid,width,result);
				}
				//add right
				rightMove(grid,grid.getPlayerOneHeadX(),result);
			}
			else
			{//normal x's
				leftMove(grid,grid.getPlayerOneHeadX(),result);
				rightMove(grid,grid.getPlayerOneHeadX(),result);
			}

		}
		else
		{
			if(grid.getPlayerTwoHeadY() ==width-2)//almost bottom
			{
				if(grid[width-1][0]!=0)
				{
					upMove(grid,grid.getPlayerOneHeadY(),result);
				}
				//add up

				downMove(grid,grid.getPlayerTwoHeadY(),result);
			}
			else if(grid.getPlayerTwoHeadY() ==1)//almost top
			{
				if(grid[0][0]!=0)
				{
					downMove(grid,1,result);
				}
				//add down
				upMove(grid,grid.getPlayerTwoHeadY(),result);
			}
			else
			{
				//normal y's
				upMove(grid,grid.getPlayerTwoHeadY(),result);
				downMove(grid,grid.getPlayerTwoHeadY(),result);
			}
			if(grid.getPlayerTwoHeadX()==width-1)//right edge
			{
				//std::cout<<"right edge\n";
				if(grid[grid.getPlayerTwoHeadY()][0]==0)//can wrap around the right
				{
					rightMove(grid,-1,result);
				}
				//add left

				leftMove(grid,grid.getPlayerTwoHeadX(),result);
			}
			else if(grid.getPlayerTwoHeadX()==0)//left edge
			{
				//std::cout<<"left edge\n";
				if(grid[grid.getPlayerTwoHeadY()][width-1]==0){//can wrap around the left
					leftMove(grid,width,result);
				}
				//add right
				rightMove(grid,grid.getPlayerTwoHeadX(),result);
			}
			else
			{//normal x's
				leftMove(grid,grid.getPlayerTwoHeadX(),result);
				rightMove(grid,grid.getPlayerTwoHeadX(),result);
			}
		}
	}
	//returns afeterstate for up move if possible, otherwise returns null
	void Player::upMove(Grid& grid,int y, std::vector<Grid>& result){
		if(debug)
			std::cout<<"up move\n";
		if( y == width-2 )
		{
			if(grid[width-1][0] == 0){
				Grid *out = new Grid(grid);
				(*out)[width-1][0] = digit;
				(*out).setPlayerOneHead(width-1,0);
				result.push_back(*out);
			}
		}
		else if(digit ==1 )
		{
			if(grid[y+1][grid.getPlayerOneHeadX()]==0)
			{
				Grid *out = new Grid(grid);
				(*out)[y+1][grid.getPlayerOneHeadX()] = digit;
				(*out).setPlayerOneHead(grid.getPlayerOneHeadX(),y+1);
				result.push_back(*out);
			}
		}
		else
		{
			if(grid[y+1][grid.getPlayerTwoHeadX()]==0)
			{
				Grid *out = new Grid(grid);
				(*out)[y+1][grid.getPlayerTwoHeadX()] = digit;
				(*out).setPlayerTwoHead(grid.getPlayerTwoHeadX(),y+1);
				result.push_back(*out);
			}
		}
	//	if(result.isValid())
		//	std::cout<<"down move\n"<<result.printGrid();
	}
	//returns afterstate for down move if possible, otherwise returns null
	void Player::downMove(Grid & grid,int y, std::vector<Grid>& result)
	{
		if(debug)
			std::cout<<"down move\n";
		if( y == 1 )
		{
			if(grid[0][0] == 0){
				Grid *out = new Grid(grid);
				(*out)[0][0] = digit;
				(*out).setPlayerOneHead(0,0);
				result.push_back(*out);
			}
		}
		else if(digit ==1)
		{
			
			if(grid[y-1][grid.getPlayerOneHeadX()]==0)
			{
				Grid *out = new Grid(grid);
				(*out)[y-1][grid.getPlayerOneHeadX()] = digit;
				(*out).setPlayerOneHead(grid.getPlayerOneHeadX(),y-1);
				result.push_back(*out);
			}
		}
		else
		{
			if(grid[y-1][grid.getPlayerTwoHeadX()]==0)
			{
				Grid *out = new Grid(grid);
				(*out)[y-1][grid.getPlayerTwoHeadX()] = digit;
				(*out).setPlayerTwoHead(grid.getPlayerTwoHeadX(),y-1);
				result.push_back(*out);
			}
		}
	//	if(result.isValid())
		//	std::cout<<y<<" up move\n"<<result.printGrid();

	}
	//return afterstate for left move if possible, otherwise returns null
	void Player::leftMove(Grid& grid,int x, std::vector<Grid>& result)
	{
		if(debug)
			std::cout<<"left move\n";
		if(digit ==1 )
		{
			if(grid[grid.getPlayerOneHeadY()][x-1]==0)
			{
				Grid *out = new Grid(grid);
				(*out)[grid.getPlayerOneHeadY()][x-1] = digit;
				(*out).setPlayerOneHead(x-1,grid.getPlayerOneHeadY());
				result.push_back(*out);
			}
		}
		else
		{
			if(grid[grid.getPlayerTwoHeadY()][x-1]==0)
			{
				Grid *out = new Grid(grid);				
				(*out)[grid.getPlayerTwoHeadY()][x-1] = digit;
				(*out).setPlayerTwoHead(x-1,grid.getPlayerTwoHeadY());
				result.push_back(*out);
			}
		}
	}

	//return after state for right move is possible, otherwise return null
	void Player::rightMove(Grid& grid,int x, std::vector<Grid>& result)
	{
		if(debug)
			std::cout<<"right move\n";
		if(digit ==1 )
		{
			if(grid[grid.getPlayerOneHeadY()][x+1]==0)
			{
				Grid *out = new Grid(grid);
				(*out)[grid.getPlayerOneHeadY()][x+1] = digit;
				(*out).setPlayerOneHead(x+1,grid.getPlayerOneHeadY());
				result.push_back(*out);
			}
		}
		else
		{
			if(grid[grid.getPlayerTwoHeadY()][x+1]==0)
			{
				Grid *out = new Grid(grid);
				(*out)[grid.getPlayerTwoHeadY()][x+1] = digit;
				(*out).setPlayerTwoHead(x+1,grid.getPlayerTwoHeadY());
				result.push_back(*out);
			}
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
	void Player::randomMove(Grid &grid,std::vector<Grid>& result)
	{
		//std::cout<<"Making a random move\n";

		Grid *out = new Grid(grid);
		std::srand(std::time(NULL));
		int move_x;
		int move_y;
		if(digit ==1 )
		{
			move_x = grid.getPlayerOneHeadX();
			move_y = grid.getPlayerOneHeadY();
			if(grid.getPlayerOneHeadY() == width-1)	//south pole move
			{
				move_y = width-2;
			}
			else if(grid.getPlayerOneHeadY() == 0)// north pole move
			{
				move_y = 1;
			}

			else//middle move
			{
				move_x = (grid.getPlayerOneHeadX()+1)%width;
			}
		}
		else
		{
			move_x = grid.getPlayerTwoHeadX();
			move_y = grid.getPlayerTwoHeadY();
			if(grid.getPlayerTwoHeadY() == width-1)	//south pole move
			{
				move_y = width-2;
			}
			else if(grid.getPlayerTwoHeadY() == 0)// north pole move
			{
				move_y = 1;
			}

			else//middle move
			{
				move_x = (grid.getPlayerTwoHeadX()+1)%width;
			}
		}
		(*out)[move_y][move_x] += digit;
		if(digit == 1)
		{
			(*out).setPlayerOneHead(move_x,move_y);
		}
		else
		{
			(*out).setPlayerTwoHead(move_x,move_y);
		}
		(*out).setLoser(digit);
		result.push_back(*out);
		
	}

}
