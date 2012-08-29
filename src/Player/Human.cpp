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
		std::cout<<"playing first movve\n";
		srand(time(NULL));
		int x = rand()%width;
		int y =rand()%width;

		grid->setPlayerOneHead(x,y);
		this->y = y;
		this->x = x;
		(*grid)[y][x] = digit;

		grid->isValid(true);
		return;
	}
	else if(count ==1)
	{
		int new_x,new_y;
		if(oppo_y>0&& oppo_y<width-1)
		{
			std::cout<<"middle second move\n";
			new_x = (oppo_x+(width/2))%width;
			new_y = oppo_y;


			grid->isValid(true);
			(*grid)[new_y][new_x] = digit;

		}

		else
		{
			std::cout<<"top second move\n";
			new_x = x;
			new_y = width-1-y;
			grid->isValid(true);
			(*grid)[new_y][new_x] = digit;
		}

		this->x = new_x;
		this->y  =new_y;
		grid->setPlayerTwoHead(new_x,new_y);
		grid->setPlayerOneHead(oppo_x,oppo_y);
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
			//std::cout<<"caught up move\n";
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
			//std::cout<<"caught right move\n";
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
			//std::cout<<"caught left move\n";
			if(x==0)
			{
				leftMove(width);
				grid->setPlayerOneHeadX(x);
				grid->setPlayerOneHeadY(y);
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
			grid->isValid(true);

			return;
		}
	}
}

//returns afeterstate for up move if possible, otherwise returns null
void Human::upMove(int y){
		(*grid)[y+1][x] = digit;

		this->x = x;
		this->y = y+1;
		if(digit == 1)
		{
			grid->setPlayerTwoHead(oppo_x,oppo_y);
			grid->setPlayerOneHead(x,y);
		}
		else
		{
			grid->setPlayerOneHead(oppo_x,oppo_y);
			grid->setPlayerTwoHead(x,y);
		}
		grid->isValid(true);

}
//returns afterstate for down move if possible, otherwise returns null
void Human::downMove(int y)
{
	(*grid)[y-1][x] = digit;
	this->x = x;
	this->y = y-1;
	if(digit == 1)
	{
		grid->setPlayerTwoHead(oppo_x,oppo_y);
		grid->setPlayerOneHead(x,y);
	}
	else
	{
		grid->setPlayerOneHead(oppo_x,oppo_y);
		grid->setPlayerTwoHead(x,y);
	}
	grid->isValid(true);

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
		grid->setPlayerOneHead(x,y);
	}
	else
	{
		grid->setPlayerOneHead(oppo_x,oppo_y);
		grid->setPlayerTwoHead(x,y);
	}
	grid->isValid(true);
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
			grid->setPlayerOneHead(x,y);
		}
		else
		{
			grid->setPlayerOneHead(oppo_x,oppo_y);
			grid->setPlayerTwoHead(x,y);
		}
		grid->isValid(true);
	}

}
