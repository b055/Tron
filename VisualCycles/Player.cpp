/*
 * Player.cpp
 *
 *  Created on: 03 Aug 2012
 *      Author: Ivan Nelson Togboa Cadri
 */

#include "Player.h"
namespace tron{
	Player::Player(int digit):digit(digit){
		//debug = false;
		loser = false;
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

	std::vector<std::vector< int> > Player::possibleMoves()
	{
	//	if(x>=width)
		//	std::cout<<x<<" in possibleMoves() "<<digit<<"  "<<std::endl;
		std::vector<std::vector< int> > result;

		if(y==0)//top
		{
			//if(debug)
				//std::cout<<"topMoves\n";
			result = topMoves();
		}
		else if (y==29)//bottom
		{
			//if(debug)
				//std::cout<<"bottommoves\n";
			result = bottomMoves();
		}
		else//somewhere in the middle
		{
			//std::cout<<"middlemoves\n";
			result = middleMoves();
		}
		if(result.empty())
			result.push_back(randomMove());
		return result;
	}
	//print players grid
	std::string Player::printGrid()
	{
		if(digit == 1)
		{
			std::stringstream str;
			str<<"player one: x "<<x<<" y "<<y<<std::endl;
			str<< "player two: x "<<x<<" y "<<oppo_y<<std::endl;

			for(int j=0;j<30;j++)
			{
				for(int i =0;i<30;i++){
					str<<(*grid)[j][i];str<<" ";
				}
				str<<"\n";
			}
			return str.str();
		}
		else{
			std::stringstream str;

			str<< "player one: x "<<oppo_x<<" y "<<oppo_y<<std::endl;
			str<<"player two: x "<<x<<" y "<<y<<std::endl;

			for(int j=0;j<30;j++)
			{
				for(int i =0;i<30;i++){
					str<<(*grid)[j][i];str<<" ";
				}
				str<<"\n";
			}
			return str.str();
		}
	}
	//possible moves for a player at the top
	std::vector<std::vector< int> > Player::topMoves()
	{
		int count = 0;
		std::vector<std::vector<int > > result;

		for(int i = 0;i<30;i++)
		{
			if((*grid)[1][i]==0)
			{
				std::vector<int> temp;
				temp.push_back(i);
				temp.push_back(1);
				result.push_back(temp);
			}
		}
		return result;
	}

	//possible moves for a player at the bottom
	std::vector<std::vector< int> > Player::bottomMoves()

	{
		std::vector<std::vector< int> > result;
		//if(debug)
		//std::cout<<"getting bottom move"<<std::endl;

	//#pragma omp parallel for
		for(int i = 0; i<30;i++)
		{
			if((*grid)[28][i]==0)
			{
			//	if(debug){
			//		std::cout<<"true "<<i<<std::endl;
			//	}
				std::vector< int> temp;
				temp.push_back(i);
				temp.push_back(28);
				result.push_back(temp);
			}
		}
		return result;
	}

	//possible moves for a player somewhere in the middle of the sphere
	std::vector<std::vector< int> > Player::middleMoves()
	{
		std::vector<std::vector< int> > result;
		//if(debug){
		//	std::cout<<"starting middle moves\n";
		//	std::cout<<" here we are\n";
		//}


		//normal y's
		//if(debug)
		//	std::cout<<"getting normal y's\n";
		std::vector<int> up = upMove(y);
			if(!up.empty()){
				result.push_back(up);
			}
		std::vector<int> down = downMove(y);
			if(!down.empty())
				result.push_back(down);

		if(x==29)//right edge
		{
			//std::cout<<"right edge\n";
			if((*grid)[y][0]==0)//can wrap around the right
			{
				std::vector<int> right = rightMove(-1);
				if(!right.empty())
					result.push_back(right);
			}
			//add left
			std::vector<int> left = leftMove(x);
			if(!left.empty())
				result.push_back(left);
		}
		else if(x==0)//left edge
		{
			//std::cout<<"left edge\n";
			if((*grid)[y][29]==0){//can wrap around the left
				std::vector<int> left = leftMove(30);
				if(!left.empty())
					result.push_back(left);
			}
			//add right
			std::vector<int> right  = rightMove(x);
			if(!right.empty())
				result.push_back(right);
		}
		else
		{//normal x's
			std::vector<int> left =leftMove(x);
			if(!left.empty())
				result.push_back(left);
			std::vector<int> right  = rightMove(x);
			if(!right.empty())
				result.push_back(right);
		}
		return result;
	}
	//returns afeterstate for up move if possible, otherwise returns null
	std::vector< int> Player::upMove(int y){

		std::vector< int> temp;
		//if(debug)
		//	std::cout<<"up move\n";


		if((*grid)[y+1][x]==0)
		{
			temp.push_back(x);
			temp.push_back(y+1);
		}
		return temp;
	}
	//returns afterstate for down move if possible, otherwise returns null
	std::vector< int> Player::downMove(int y)
	{
		std::vector< int> temp;
		//if(debug)
		//	std::cout<<"down move\n";

		if((*grid)[y-1][x]==0)
		{
			temp.push_back(x);
			temp.push_back(y-1);
		}
		return temp;

	}
	//return afterstate for left move if possible, otherwise returns null
	std::vector< int> Player::leftMove(int x)
	{

		std::vector< int> temp;
		//if(debug)
		//	std::cout<<"left move\n";
		if((*grid)[y][x-1]==0)
		{
			temp.push_back(x-1);
			temp.push_back(y);
		}
		return temp;
	}

	//return after state for right move is possible, otherwise return null
	std::vector< int> Player::rightMove(int x)
	{
		std::vector< int> temp;
		//if(debug)
		//	std::cout<<"right move\n";
		if((*grid)[y][x+1]==0)
		{
			temp.push_back(x+1);
			temp.push_back(y);
		}
		return temp;
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
	std::vector< int> Player::randomMove()
	{
		//if(debug)
		//	std::cout<<"Making a random move\n";

		std::vector< int> temp;
		std::srand(time(NULL));
		int move_x = x;
		int move_y = y;
		if(y == 29)	//south pole move
		{
			move_y = 28;
		}
		else if(y == 0)// north pole move
		{
			move_y = 1;
		}

		else//middle move
		{
			move_x = (x+1);
			if(move_x == 30)
				move_x =0;
		}
		temp.push_back(move_x);
		temp.push_back(move_y);
		loser = true;
		priorLosing = (*grid)[move_y][move_x];
		return temp;
	}
}
