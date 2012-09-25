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
	Minimax* me= new Minimax(1);;
	Minimax* opponent = new Minimax(3);

	
	tron::Grid *g = new tron::Grid(args[1]);
	
	me->setGrid(g);
	me->setHead(*g);
	me->setOpponentPlayer(opponent);


	opponent->setGrid(g);
	opponent->setHead(*g);
	opponent->setOpponentPlayer(me);	

	//me->setX(me->getX()+1);
	//g->setPlayerOneHeadX(me->getX());
	me->play(start);

	me->setHead(*g);
	opponent->setHead(*g);
	opponent->setOpponent(me->getX(),me->getY());

	//std::cout<<g->printGrid();
	g->outputFile();
	
	delete me;
	delete opponent;
	delete g;
	return 0;
}
