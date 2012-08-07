//============================================================================
// Name        : Cycles.cpp
// Author      : Ivan Nelson Togboa Cadri
// Version     :
// Copyright   : Your copyright notice
// Description : Tron in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Neural/Network.h"
#include "Game/Game.h"
using namespace tron;
/*
int main() {
	Game *g = new Game();
	Grid *grid = new Grid();

	Player* first = new Player(1);
	Player* second = new Player(2);

	//std::cout<<"before setting grids\n";
	g->setGrid(*grid);
	first->setGrid(*grid);
	second->setGrid(*grid);
	//std::cout<<"finished setting grids\n";
	int turn = 0;
	int count =0;
	Grid** afterstates = new Grid*[30];
#pragma omp parallel for
	for(int i =0;i<30;i++)
		afterstates[i] = new Grid();
	int check = 0;
	while(g->endState() == false)
	{

		if(turn == 0)
		{
			std::cout<<"player one "<<first->getX()<<std::endl;
			first->possibleMoves(afterstates);
			std::cout<<"got possible moves\n";
			for(int a =0;a<30;a++){
				if(afterstates[a]->isValid()){
					g->setGrid(*(afterstates[a]));
					afterstates[a]->isValid(false);
					std::cout<<"valid\n";
					break;
				}
				//std::cout<<"finished loop "<<a<<std::endl;
			}
			first->setHead(g->getGrid());
			first->setGrid((g->getGrid()));
			second->setGrid((g->getGrid()));
			second->setOppoX(first->getX());
			second->setOppoY(first->getY());
			turn = 1;
			//std::cout<<first->printGrid();
			//std::cout<<second->printGrid();
		}
		else
		{
			std::cout<<"player two "<<second->getX()<<std::endl;
			second->possibleMoves(afterstates);

			for(int a =0;a<30;a++){
				if(afterstates[a]->isValid()){
					g->setGrid(*(afterstates[a]));
					break;
				}
			}

			second->setHead(g->getGrid());
			first->setGrid((g->getGrid()));
			//std::cout<<second->printGrid();
			std::cout<<"first grid above\n";
			second->setGrid((g->getGrid()));
			//std::cout<<second->printGrid();

			//if(count>0)
			{
				first->setOppoX(second->getX());
				first->setOppoY(second->getY());
			}
			turn = 0;

		}

		std::cout<<"\n";
		if(g->endState() == false)
			std::cout<<g->printGrid();

		count++;
		check++;
		std::cout<<check<<std::endl;

		#pragma omp parallel for
			for(int i =0;i<30;i++)
				afterstates[i]->isValid(false);
	}
	g->getAfterState();
	std::cout<<"prit original\n";
	std::cout << 1- g->getTurn()<<"  lost" << std::endl;
	return 0;
}
*/
