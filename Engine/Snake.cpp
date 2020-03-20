#include "Snake.h"
#include <assert.h>
#include <math.h>

Snake::Snake(const Location& loc)
{
	segments[0].initHead(loc);

}

void Snake::MoveBy(const Location & delta_loc)
{
	for (int i = snakeSize - 1; i > 0; --i) {
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (snakeSize < nSegmentsMax) {
		int mod = snakeSize % 3;
		switch (mod) {
		case 1:
			segments[snakeSize].initBody(Snake::bodyColor);
			break;
		case 2:
			segments[snakeSize].initBody(Snake::bodyColor2);
			break;
		default:
			segments[snakeSize].initBody(Snake::bodyColor3);
			break;
		}
		++snakeSize;
	}
}

void Snake::Draw(Board & brd) const
{
	if (!jumpState) {
		int i = 0;
		while (i < snakeSize) {
		//for (int i = 0; i < snakeSize; i++) {
			if (isInTile(segments[i].getLocation(), 0, i + 1)) {
				for (int j = 0; j < 4; j++) {
					segments[i].DrawSmall(brd);
					i++;
				}
			} else {
				segments[i].Draw(brd);
				i++;
			}
		}
	} else {
		if (snakeSize < 4) {
			for (int i = 0; i < snakeSize; i++) {
				segments[i].DrawSmall(brd);
			}
		} else {
			for (int i = 0; i < 4; i++) {
				segments[i].DrawSmall(brd);
			}
			int j = 4;
			while (j < snakeSize) {
				if (isInTile(segments[j].getLocation(), 0, j + 1)) {
					for (int z = 0; z < 4; z++) {
						segments[j].DrawSmall(brd);
						j++;
					}
				} else {
					segments[j].Draw(brd);
					j++;
				}

			}
			//for (int j = 4; j < snakeSize; j++) {
			//	segments[j].Draw(brd);
			//}
		}
	}
}

Location Snake::GetNextHeadLocation(const Location & delta_loc) const
{
	Location l(segments[0].getLocation());
	l.Add(delta_loc);
	return l;
}


/* Checks whether location intersects with a snake segment, with exceptions for certain segments. */
bool Snake::isInTile(const Location& target, const int& excludeEnd, const int& excludeBegin) const
{
	if (!jumpState) {
		for (int i = 0 + excludeBegin; i < snakeSize - excludeEnd; ++i) {
			if (target == segments[i].getLocation()) {
				return true;
			}
		}
	}
	return false;
}

void Snake::changeJumpState()
{
	if (jumpState) {
		jumpState = false;
		segments[0].ChangeColor(headColor);
	}
	else {
		jumpState = true;
		segments[0].ChangeColor(jumpColor);
	}
}

void Snake::Segment::initHead(const Location& in_loc)
{ 
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::initBody(const Color& color)
{
	c = color;
	
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert( abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
	
}

void Snake::Segment::Draw(Board & brd) const
{
	brd.DrawCell(loc, c, 2);
	
}

void Snake::Segment::DrawSmall(Board& brd) const {
	brd.DrawCell(loc, c, 10);
}

const Location& Snake::Segment::getLocation() const
{
	return loc;
}

void Snake::Segment::ChangeColor(const Color& newColor)
{
	c = newColor;
}
