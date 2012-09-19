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
		//std::cout<<"playing first move\n";
		srand(time(NULL));
		int x =4; rand()%width;
		int y =1;rand()%width;

		if(y == 0) y++;
		if(y == width-1) y--;

		grid->setPlayerOneHead(x,y);
		(*grid)[y][x] = digit;

		this->y = y;
		this->x = x;

		return;
	}
	else if(count ==1)
	{
		int new_x,new_y;
		if(oppo_y>0 && oppo_y<width-1)
		{
			//std::cout<<"middle second move\n";
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
		std::vector<int> temp;
		if(move.compare("u") == 0)
		{
			temp = downMove(y);
		}
		else if(move.compare("d") == 0)
		{
			temp = upMove(y);
		}
		else if(move.compare("r") == 0)
		{
			if(x == width-1)
			{
				temp = rightMove(-1);
			}
			else
				temp = rightMove(this->x);
		}
		else if(move.compare("l") == 0)
		{
			if(x==0)
			{
				temp = leftMove(width);
			}
			else{
				temp = leftMove(x);
			}
		}
		else
		{
			int position = atoi(move.c_str());
			temp.push_back(position);
			if(y ==0 )
				temp.push_back(1);
			if(y== width-1)
				temp.push_back(width-2);

		}
		(*grid)[temp[1]][temp[0]] = digit;
		x= temp[0];y = temp[1];
		if(digit == 1)
		{
			grid->setPlayerOneHead(temp[0],temp[1]);
		}
		else
		{
			grid->setPlayerTwoHead(temp[0],temp[1]);
		}
		getOpponentPlayer()->setOpponent(getX(),getY());
		if(temp[1] == 0|| temp[1] == width-1)
			for(int i = 0; i< width;i++)
				(*grid)[temp[1]][i] = digit;
	}
}


}
