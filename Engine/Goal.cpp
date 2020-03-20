#include "Goal.h"

Goal::Goal(std::mt19937 & rng, const Board & brd, const Snake & snake)
{
	Respawn(rng, brd, snake);
}


void Goal::Respawn(std::mt19937 & rng, const Board& brd, const Snake & snake)
{
	std::uniform_int_distribution<int> xDist(brd.getLeftBorder() + 1, brd.getGridWidth() - 2 - brd.getRightBorder());
	std::uniform_int_distribution<int> yDist(brd.getUpBorder() + 1, brd.getGridHeight() - 2 - brd.getDownBorder());

	Location newLoc;
	do {
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.isInTile(newLoc, 0, 0));

	loc = newLoc;
}

void Goal::Draw(Board & brd) const
{
	brd.DrawCell(loc, c, 2);
}

const Location & Goal::GetLocation() const
{
	return loc;
}
