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
		delete grid;
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
			//checks for collisions

			for (int j=0;j<width;j++)
			{
				for (int i =0;i<width;i++)
				{
					if ((*grid)[j][i] != 1 && (*grid)[j][i] != 3 && (*grid)[j][i]!= 0)
					{
						std::cout<<(*grid)[j][i]<<"end game";
						return true;
					}
				}
			}

			int check_top=0;
			int check_bot = 0;

			for (int i = 0;i<width;i++)
			{
				if(((*grid)[0][i]) != 0)
				{
					check_top++;
				}
				if((*grid)[width-1][i]!=0)
				{
					check_bot++;
				}
				if(check_top>1|| check_bot>1){
					std::cout<<"end game poles\n";
					return true;
				}

			}
			return false;

	}
}
