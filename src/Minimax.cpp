
#include <iostream>
#include "Game/Game.h"
#include "Evaluate/Evaluate.h"
#include "Player/Human.h"

using namespace tron;
int main(void)
{
	int width = 10;
	Player* first;
	Human* human;
	Evaluate * ev = new Evaluate(first,human);
		ev->setGap(10);

		Game *g = new Game(width);


		first->setGrid(g->getGrid());
		human->setGrid(g->getGrid());
		while(true)
			{
				double val = 0;
				int turn = int(rand()%2);
				//std::cout<<turn<<"this is the turn"<<std::endl;
				if(turn == 0)
				{
					first->setDigit(1);
					human->setDigit(3);
				}
				else
				{
					first->setDigit(3);
					human->setDigit(1);
				}



				Grid** afterstates = new Grid*[width];
					#pragma omp parallel for
						for(int i =0;i<width;i++)
							afterstates[i] = new Grid(width);
				while(g->endState() == false)
				{
					if(turn == 0)
					{
						first->possibleMoves(afterstates);

						double value = -999999;
						int pos = 0;
						int count = 0;
		#pragma omp parallel for
						for(int a =0;a<width;a++){
							if(afterstates[a] != 0 && afterstates[a]->isValid()){
		#pragma omp atomic
								count++;

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
		//std::cout<<"valid\n";
							}
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
						first->setHead(*g->getGrid());
						human->setOppoX(first->getX());
						human->setOppoY(first->getY());
						turn = 1;

					}
					else
					{
						human->play();
						std::cout<<human->getX()<<human->getY();
						first->setOppoX(human->getX());
						first->setOppoY(human->getY());
						turn = 0;
					}
					//std::cout<<g->printGrid();
					if(g->endState() == true)//game over
					{
						if(turn == 1)
						{
							std::cout <<"Player one  lost" << std::endl;

							fnet->update(-1);
							std::cout<<human->getDigit()<<std::endl;
						//	ev->progress(1);
						}
						else
						{

							std::cout<<"Player two lost"<<std::endl;
							fnet->update(1);
							std::cout<<first->getDigit()<<std::endl;
						//	ev->progress(0);
						}
					}
					else
					{
						if(turn == 1)
						{
							fnet->update(0);
							first->getNet()->setOld(val);
						}
					}
		#pragma omp parallel for
						for(int i =0;i<width;i++)
							if(afterstates[i] != 0)
								afterstates[i]->reset();

				}
				g->reset();
				total++;
			}

			//std::cout<<g->printGrid();
			std::cout<<"prit original\n";


			return 0;
		}
