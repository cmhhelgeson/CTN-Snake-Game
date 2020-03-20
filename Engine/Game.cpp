/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ), 
	random(std::random_device()()),
	brd(gfx), 
	snek({20, 15}), 
	goal(random, brd, snek)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{ 
	if (!isGameOver) {
		if (wnd.kbd.KeyIsPressed(VK_UP) && dirMark != downMark && !directionLock) {
			delta_loc = { 0, -1 };
			dirMark = upMark;
			directionLock = true;
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN) && dirMark !=upMark && !directionLock) {
			delta_loc = { 0, 1 };
			dirMark = downMark;
			directionLock = true;
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT) && dirMark != rightMark && !directionLock) {
			delta_loc = { -1, 0 };
			dirMark = leftMark;
			directionLock = true;
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT) && dirMark != leftMark && !directionLock) {
			delta_loc = { 1, 0 };
			dirMark = rightMark;
			directionLock = true;
		}

		if (wnd.kbd.KeyIsPressed(VK_CONTROL) && !lock && jumpCounter == 40) {
			snek.changeJumpState();
			lock = true;
		}

		++snakeMoveCounter;
		if (snakeMoveCounter >= snekMovePeriod) {
			snakeMoveCounter = 0;
			const Location next = snek.GetNextHeadLocation(delta_loc);
			if (!brd.isInsideBoard( next ) || snek.isInTile(next, 1, 0)) {
				isGameOver = true;
			} else {
				const bool eating = next == goal.GetLocation();
				if (eating || wnd.kbd.KeyIsPressed(VK_SPACE)) {
					snek.Grow();
				}
				//if (snek.GetNextHeadLocation(delta_loc).Equals(goal.loc))
				snek.MoveBy(delta_loc);
				directionLock = false;
				if (eating) {
					goal.Respawn(random, brd, snek);
				}

			}
		}

		if (lock == true) {
			jumpCounter--;
			if (jumpCounter <= 0) {
				snek.changeJumpState();
				lock = false;
			}
		}
		else if (lock == false && jumpCounter < 40) {
			jumpCounter++;
		}

		++constrictMoveCounter;
		if (wnd.kbd.KeyIsPressed(VK_ESCAPE) && constrictMoveCounter >= constrictMovePeriod) {
			brd.Constrict();
			constrictMoveCounter = 0;
			if (goal.GetLocation().x == brd.getLeftBorder() || 
				goal.GetLocation().x == brd.getGridWidth() - 1 - brd.getRightBorder() || 
				goal.GetLocation().y == brd.getUpBorder() ||
				goal.GetLocation().y == brd.getGridHeight() - 1 - brd.getDownBorder()) {
				goal.Respawn(random, brd, snek);
			}
		}
		else if (wnd.kbd.KeyIsPressed(VK_BACK) && constrictMoveCounter >= constrictMovePeriod) {
			brd.unConstrict();
			constrictMoveCounter = 0;
		}
	}
}

void Game::ComposeFrame()
{
	snek.Draw(brd);
	goal.Draw(brd);
	brd.DrawBorder();
	if (isGameOver) {
		SpriteCodex::DrawGameOver(360, 250, gfx);
	}
}
