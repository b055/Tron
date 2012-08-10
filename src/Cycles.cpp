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
#include "Evaluate/Evaluate.h"
#include "omp.h"
using namespace tron;

int main() {

	Network* net = new Network(231,200,200, 1, 0.4,0.2);
	//std::cout<<"before setting grids\n";


	Player* first;
	Player* second ;
	;
	//std::cout<<"finished setting grids\n";

	Grid** afterstates = new Grid*[30];
#pragma omp parallel for
	for(int i =0;i<30;i++)
		afterstates[i] = new Grid();

	long total = 0;
	srand(time(NULL));


	first = new Player(1);
	second = new Player(3);
	first->setNet(net);
	second->setNet(net);
	Evaluate * ev = new Evaluate(first,second);
	ev->setGap(2);

	Game *g = new Game();

	Grid *grid = new Grid();
	while(total !=10)
	{
		grid->reset();
		int count =0;
		std::cout<<"still believing\n";
		g->setGrid(*grid);
		first->setGrid(*grid);
		second->setGrid(*grid);
		int turn = int(rand()%2);
		if(turn == 0)
		{
			first->setDigit(1);
			second->setDigit(3);
		}
		else
		{
			first->setDigit(3);
			second->setDigit(1);
		}
		while(g->endState() == false)
		{
			std::cout<<"not end state\n";
			if(turn == 0)
			{
				std::cout<<"player one "<<first->getX()<<std::endl;

				first->possibleMoves(afterstates);
				//std::cout<<"got possible moves\n";
				double value = -99999;
				int pos = 0;
		#pragma omp parallel for
				for(int a =0;a<30;a++){
					if(afterstates[a]->isValid()){
						double out = net->feedForward(afterstates[a]->getAfterState());
		#pragma omp critical
						if(out>=value)
						{
							value = out;
							pos = a;
						}
						//std::cout<<"valid\n";
					}
				}
				net->feedForward(afterstates[pos]->getAfterState());//to set the hidden nodes to the best values
				g->setGrid(*(afterstates[pos]));
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

				double value = -99999;
				int pos = 0;
				for(int a =0;a<30;a++){
					if(afterstates[a]->isValid()){
						double out = net->feedForward(afterstates[a]->getAfterState());
		#pragma omp single
						if(out>=value)
						{
							value = out;
							pos = a;
						}
					}
				}
				net->feedForward(afterstates[pos]->getAfterState());
				g->setGrid(*(afterstates[pos]));
				second->setHead(g->getGrid());
				first->setGrid((g->getGrid()));
				//std::cout<<second->printGrid();
			//	std::cout<<"first grid above\n";
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
			//std::cout<<g->printGrid();
			count++;
			std::cout<<count<<std::endl;
			if(g->getAfterState())//game over
			{
				//net->update(1);
			}
			else
			{
			//	net->update(0);
			}
#pragma omp parallel for
				for(int i =0;i<30;i++)
					afterstates[i]->isValid(false);
		}
		if(turn == 1)
		{
			ev->progress(1);
		std::cout <<"Player one  lost" << std::endl;

		}
		else
		{
			ev->progress(0);
			std::cout<<"Player two lost"<<std::endl;
		}
		first->reset();
		second->reset();
		total++;
	}
	//g->getAfterState();

	//std::cout<<g->printGrid();
	std::cout<<"prit original\n";


	return 0;
}
