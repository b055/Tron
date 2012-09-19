/*
 * Game.cpp
 *
 *  Created on: 03 Aug 2012
 *      Author: cdrnel001
 */

#include "Game.h"

namespace tron{
	Game::Game(int w):width(w),grid(new Grid(w)){
	}

	Game::~Game() {
	/*	delete grid;*/
	}
	void Game::setGrid(Grid &newGrid)
	{
		*grid = newGrid;
	}

	std::string Game::printGrid()
	{
		return grid->printGrid();
	}
	void Game::reset()
	{
		grid->reset();
	}
	bool Game::endState()
	{
			return grid->endState();

	}
}
