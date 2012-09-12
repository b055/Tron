/*
 * Human.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: ivan
 */

#include "Human.h"

namespace tron {

Human::Human(int digit,int w):Player(digit,w){}

Human::~Human() {

}

void Human::play()
{
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
		std::cout<<"playing first move\n";
		srand(time(NULL));
		int x = rand()%width;
		int y =rand()%width;
		if(y ==0){
			(*grid)[0][0] = digit;
			grid->setPlayerOneHead(0,0);
			this->y = 0;
			this->x = 0;
		}
		else if(y== width-1)
		{
			(*grid)[width-1][0] = digit;
			grid->setPlayerOneHead(0,width-1);
			this->y = width-1;
			this->x = 0;
		}
		else{
			grid->setPlayerOneHead(x,y);
			(*grid)[y][x] = digit;
			
			this->y = y;
			this->x = x;
		}

		return;
	}
	else if(count ==1)
	{
		int new_x,new_y;
		if(oppo_y>0 && oppo_y<width-1)
		{
			std::cout<<"middle second move\n";
			new_x = (oppo_x+(width/2))%width;
			new_y = oppo_y;
		}
		else
		{
			std::cout<<"top second move\n";
			new_x = x;
			new_y = width-1-y;
		}
		(*grid)[new_y][new_x] = digit;
		this->x = new_x;
		this->y  =new_y;
		grid->setPlayerTwoHead(new_x,new_y);
		return;
	}
	else
	{
		std::cout<<grid->printGrid();
		std::cout<<"Please play a move"<<"("<<digit<<"): ";

		std::string move;
		getline(std::cin,move);
		std::cout<<std::endl<<std::endl<<move;

		if(move.compare("u") == 0)
		{
			downMove(this->y);
			return;
		}
		else if(move.compare("d") == 0)
		{
			upMove(this->y);
			return;
		}
		else if(move.compare("r") == 0)
		{
			if(x == width-1)
			{
				rightMove(-1);
				return;
			}
			rightMove(this->x);
			return;
		}
		else if(move.compare("l") == 0)
		{
			if(x==0)
			{
				leftMove(width);
				return;
			}
			leftMove(this->x);
			return ;
		}
		else
		{
			int position = atoi(move.c_str());
			if(y == 0)
			{
				(*grid)[1][position] = digit;
				this->x = position;this->y = 1;
				if(digit == 1)
				{
					grid->setPlayerOneHead(position,1);
					grid->setPlayerTwoHead(oppo_x,oppo_y);
				}
				else
				{
					grid->setPlayerTwoHead(position,1);
					grid->setPlayerOneHead(oppo_x,oppo_y);
				}
			}
			else if(y ==width-1)
			{
				(*grid)[width-2][position] = digit;
				this->x = position; this->y = width-2;
				if(digit == 1)
				{
					grid->setPlayerOneHead(position,width-2);
					grid->setPlayerTwoHead(oppo_x,oppo_y);
				}
				else
				{
					grid->setPlayerTwoHead(position,width-2);
					grid->setPlayerOneHead(oppo_x,oppo_y);
				}
			}

			return;
		}
	}
}

//returns afeterstate for up move if possible, otherwise returns null
void Human::upMove(int y){
		this->y = y+1;
		if( y == width-2 )
		{
			if((*grid)[width-1][0] == 0){
				(*grid)[width-1][0] = digit;
				(*grid).setPlayerOneHead(width-1,0);
				this->x = 0;
			}
			return;
		}		
		(*grid)[y+1][x] = digit;

		if(digit == 1)
		{
			grid->setPlayerTwoHead(oppo_x,oppo_y);
			grid->setPlayerOneHead(x,this->y);
		}
		else
		{
			grid->setPlayerOneHead(oppo_x,oppo_y);
			grid->setPlayerTwoHead(x,this->y);
		}

}
//returns afterstate for down move if possible, otherwise returns null
void Human::downMove(int y)
{
	this->y = y-1;
	if( y == 1 )
	{
		if((*grid)[0][0] == 0){
			(*grid)[0][0] = digit;
			(*grid).setPlayerOneHead(0,0);
			this->x = 0;
		}
		return;
	}
	(*grid)[y-1][x] = digit;
	
	if(digit == 1)
	{
		grid->setPlayerTwoHead(oppo_x,oppo_y);
		grid->setPlayerOneHead(x,this->y);
	}
	else
	{
		grid->setPlayerOneHead(oppo_x,oppo_y);
		grid->setPlayerTwoHead(x,this->y);
	}

}
//return afterstate for left move if possible, otherwise returns null
void Human::leftMove(int x)
{
	(*grid)[y][x-1] = digit;

	this->x = x-1;
	this->y = y;
	if(digit == 1)
	{
		grid->setPlayerTwoHead(oppo_x,oppo_y);
		grid->setPlayerOneHead(this->x,y);
	}
	else
	{
		grid->setPlayerOneHead(oppo_x,oppo_y);
		grid->setPlayerTwoHead(this->x,y);
	}
}

//return after state for right move is possible, otherwise return null
	void Human::rightMove(int x)
	{
		(*grid)[y][x+1] = digit;
		this->x = 1+x;
		this->y = y;
		if(digit == 1)
		{
			grid->setPlayerTwoHead(oppo_x,oppo_y);
			grid->setPlayerOneHead(this->x,y);
		}
		else
		{
			grid->setPlayerOneHead(oppo_x,oppo_y);
			grid->setPlayerTwoHead(this->x,y);
		}
	}

}
