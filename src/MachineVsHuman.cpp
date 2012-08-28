
#include <iostream>
#include "Neural/Network.h"
#include "Game/Game.h"
#include "Evaluate/Evaluate.h"
#include "omp.h"
#include "Player/Human.h"
#include <memory>
#include "Player/Minimax.h"
using namespace tron;


int main(void) {

	int width = 10;
	Minimax* machine;
	Human* human;

	long total = 0;
	srand(time(NULL));


	machine = new Minimax(1,width);
	human = new Human(3,width);
	Evaluate * ev = new Evaluate(machine,human);
	ev->setGap(10);

	Game *g = new Game(width);


	machine->setGrid(g->getGrid());
	human->setGrid(g->getGrid());
	while(true)
	{
		double val = 0;
		int turn =1;// int(rand()%2);
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

		while(g->endState() == false)
		{
			if(turn == 0)
			{
				machine->play();
				machine->setHead(*g->getGrid());
				human->setOpponent(machine->getX(),machine->getY());
				turn = 1;
			}
			else
			{
				human->play();
				machine->setOppoX(human->getX());
				machine->setOppoY(human->getY());
				turn = 0;
			}

		}
		g->reset();
		total++;
	}
	return 0;
}
