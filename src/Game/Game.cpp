/*
 * Game.cpp
 *
 *  Created on: 03 Aug 2012
 *      Author: cdrnel001
 */

#include "Game.h"

namespace tron{
	Game::Game() {
		grid = *(new Grid());
	}

	Game::~Game() {

	}
	void Game::setGrid(Grid &newGrid)
	{
		grid = newGrid;
	}

	std::string Game::printGrid()
	{
		return grid.printGrid();
	}
	bool Game::endState()
	{
			//checks for collisions

			for (int i =0;i<30;i++)
			{
				for (int j=0;j<30;j++)
				{
					if (grid[j][i] >2)
						return true;
				}
			}

			int check_top=0;
			int check_bot = 0;

			for (int i = 0;i<30;i++)
			{
				if((grid[0][i]) != 0)
				{
					check_top++;
				}
				if(grid[29][i]!=0)
				{
					check_bot++;
				}
				if(check_top>1|| check_bot>1)
					return true;
			}
			return false;

	}
}
