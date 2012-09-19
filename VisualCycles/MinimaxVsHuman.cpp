
#include <iostream>
#include "Network.h"
#include "Game.h"
#include "Evaluate.h"
#include "Human.h"
#include <memory>
#include "Minimax.h"
#include "time.h"
using namespace tron;


int main(void) {

	int width = 10;
	Minimax* machine;
	Human* human;

	long total = 0;
	srand(time(NULL));


	machine = new Minimax(1,width);
	human = new Human(3,width);

	Game *g = new Game(width);


	machine->setGrid(g->getGrid());
	human->setGrid(g->getGrid());
	machine->setOpponentPlayer(human);
	human->setOpponentPlayer(machine);

		double val = 0;
		int turn =1;//int(rand()%2);
		if(turn == 0)
		{
			machine->setDigit(1);
			human->setDigit(3);
		}
		else
		{
			machine->setDigit(3);
			human->setDigit(1);
		}

		while(human->getLoser() == false && machine->getLoser() == false)
		{
			if(turn == 0)
			{
				time_t start;
				time(&start);
				machine->play(start);
				machine->setHead(*g->getGrid());
				human->setOpponent(machine->getX(),machine->getY());
				turn = 1;
				time_t end;time(&end);
				std::cout<<difftime(end,start)<<" that's how long the play took\n";
			}
			else
			{
				human->play();
				machine->setOpponent(human->getX(),human->getY());

				turn = 0;
			}

		}
		g->reset();
		total++;
	return 0;
}
