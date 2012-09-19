/* Why the hell do we have to use windows?
I'm not saying that others shouldn't, but i think we should have the choice
*/

#include "Grid.h"
#include "Minimax.h"
#include "Player.h"
#include "Chamber.h"
#include "Voronoi.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
//#include <iostream>
using namespace tron;


int main(int argc, char * args[]) {
	time_t start;
	time(&start);
	int width = 30;
	Minimax* me;
	Minimax* opponent;

	me = new Minimax(1,width);
	opponent = new Minimax(3,width);
	
	tron::Grid *g = new tron::Grid(args[1]);
	
	me->setGrid(g);
	me->setHead(*g);
	me->setOpponentPlayer(opponent);
	//g->setPlayerOneHeadX((g->getPlayerOneHeadX()+1)%width);
	//std::cout<<g->printGrid();
	opponent->setGrid(g);
	opponent->setHead(*g);
	opponent->setOpponentPlayer(me);	

	me->play(start);
	me->setHead(*g);
	opponent->setHead(*g);
	opponent->setOpponent(me->getX(),me->getY());

	//std::cout<<g->printGrid();
	g->outputFile();
	
	//time_t end;time(&end);
	//std::printf("%f",difftime(end,start));
	return 0;
}
