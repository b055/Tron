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
#include <memory>
using namespace tron;

int main() {
	int width = 10;
	Network* fnet = new Network(231,60,60,1,0.32,0.46,0.6,0.2);
	Network* snet = new Network(231,60,60,1,0.4,0.5,0.44,0.3);

	//Network * fnet = new Network("/home/cdrnel001/Cycles/src/Result/one/2012-8-15-8349.9500.txt");
	//Network * snet = new Network("/home/cdrnel001/one/2012-8-16-182548.2800.txt");
	//std::cout<<"before setting grids\n";
	bool debug = false;

	Player* first;
	Player* second ;

	//std::cout<<"finished setting grids\n";


	long total = 0;
	srand(time(NULL));


	first = new Player(1,width);
	second = new Player(3,width);
	first->setNet(fnet);
	second->setNet(snet);
	Evaluate * ev = new Evaluate(first,second);
	ev->setGap(10);

	Game *g = new Game(width);
	first->setGrid((g->getGrid()));
	second->setGrid((g->getGrid()));
	while(true)
	{

		double val = 0;
		int turn = int(rand()%2);
		std::cout<<turn<<"this is the turn"<<std::endl;
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

		first->getNet()->setOld(0);
		second->getNet()->setOld(0);
		while(g->endState() == false)
		{
			Grid** afterstates = new Grid*[width];
			#pragma omp parallel for
				for(int i =0;i<width;i++)
				{
					afterstates[i] = new Grid(width);
				}

			if(turn == 0)
			{
				if(debug)
					std::cout<<"player one "<<first->getX()<<" "<<first->getY()<<std::endl;

				first->possibleMoves(afterstates);
				//std::cout<<"got possible moves\n";
				double value = -999999;
				int pos = 0;
				int count = 0;
#pragma omp parallel for
				for(int a =0;a<width;a++){
					if(afterstates[a] != 0 && afterstates[a]->isValid()){
#pragma omp atomic
						count++;
						if(debug && first->getY() == width-2)
							std::cout<<afterstates[a]->printGrid()<<std::endl;
						double* out = first->getNet()->feedForward(afterstates[a]->getAfterState(first->getDigit()));
						if(first->getDigit() == 1)
						{
#pragma omp critical
							if(out[0]>=value)
							{
								value = out[0];
								pos = a;
							}
						}
						else
						{
							if(out[1]>=value)
							{
								value = out[1];
								pos = a;
							}
						}

					}
//std::cout<<"valid\n";
				}

				//takes care of exploration 20% chance of taking a random move
				int ran = int(rand()%count);
				float chance = (float)rand()/(float)RAND_MAX;
				int new_count = 0;
				if(chance <0.10)
				{
					for(int a = 0;a<width;a++)
					{
						if(afterstates[a] != 0 &&afterstates[a]->isValid()){
							if(new_count == ran)
							{
								pos = a;
								break;
							}
							new_count++;
						}
					}
				}
				if(first->getDigit() == 1)
				{
					val = first->getNet()->feedForwardSave(afterstates[pos]->getAfterState(first->getDigit()))[0];//to set the hidden nodes to the best values
				}
				else{
					val = first->getNet()->feedForwardSave(afterstates[pos]->getAfterState(first->getDigit()))[1];//to set the hidden nodes to the best values
				}

				g->setGrid(*(afterstates[pos]));
				first->setHead(*(g->getGrid()));
				second->setOppoX(first->getX());
				second->setOppoY(first->getY());
				turn = 1;
				//std::cout<<first->printGrid();
				//std::cout<<second->printGrid();
			}
			else
			{

				if(debug)
					std::cout<<"player two "<<second->getX()<<" "<<second->getY()<<std::endl;
				second->possibleMoves(afterstates);

				double value = -99999;
				int pos = 0;
				int count = 0;
#pragma omp parallel for
				for(int a =0;a<width;a++){
					if(afterstates[a] != 0 &&afterstates[a]->isValid()){
#pragma omp atomic
						count++;
						double* out = second->getNet()->feedForward(afterstates[a]->getAfterState(second->getDigit()));
						if(first->getDigit() == 1)
						{
#pragma omp critical
							if(out[0]>=value)
							{
								value = out[0];
								pos = a;
							}
						}
						else
						{
							if(out[1]>=value)
							{
								value = out[1];
								pos = a;
							}
						}
					}
				}

				//20% chance of exploring new state
				int ran = int(rand()%count);
				float chance = (float)rand()/(float)RAND_MAX;
				int new_count = 0;
				if(chance <0.10)
				{
					for(int a = 0;a<width;a++)
					{
						if(afterstates[a] != 0 &&afterstates[a]->isValid()){
							if(new_count == ran)
							{
								pos = a;
								break;
							}
							new_count++;
						}
					}
				}

				if(second->getDigit() == 1)
					val = second->getNet()->feedForwardSave(afterstates[pos]->getAfterState(second->getDigit()))[0];//to set the hidden nodes to the best values
				else
					val = second->getNet()->feedForwardSave(afterstates[pos]->getAfterState(second->getDigit()))[1];//to set the hidden nodes to the best values


				g->setGrid(*(afterstates[pos]));
				second->setHead(*g->getGrid());
				//std::cout<<second->printGrid();

				//if(count>0)
				{
					first->setOppoX(second->getX());
					first->setOppoY(second->getY());
				}
				turn = 0;

			}

			//std::cout<<"\n";
			//std::cout<<count<<std::endl;
			if(debug)
				std::cout<<g->printGrid();
			if(g->endState() == true)//game over
			{
				if(turn == 1)
				{
					if(debug)
						std::cout <<"Player one  lost" << std::endl;
					snet->update(1);
					fnet->update(-1);
					if(debug)
						std::cout<<second->getDigit()<<std::endl;
					ev->progress(1);
				}
				else
				{
					if(debug)
						std::cout<<"Player two lost"<<std::endl;
					fnet->update(1);
					snet->update(-1);
					std::cout<<first->getDigit()<<std::endl;
					ev->progress(0);
				}
			}
			else
			{
				if(turn == 1)
				{
					fnet->update(0);
					first->getNet()->setOld(val);
				}
				else
				{
					snet->update(0);
					second->getNet()->setOld(val);
				}
			}
			if(debug)
				std::cout<<g->printGrid();
		}
		first->reset();
		second->reset();
		g->reset();
		total++;
	}
	//g->getAfterState();



	return 0;
}
