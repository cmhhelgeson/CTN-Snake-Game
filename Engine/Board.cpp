#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx) :
	gfx(gfx)
{
}

void Board::DrawCell(const Location& loc, Color c, int sizeReduction)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	gfx.DrawRectDim(loc.x * dimensions, loc.y * dimensions, dimensions - sizeReduction, dimensions - sizeReduction, c);
}

int Board::getGridWidth() const
{
	return width;
}

int Board::getGridHeight() const
{
	return height;
}

bool Board::isInsideBoard(const Location & loc) const
{
	return loc.x > leftBorder &&
		loc.x < width - rightBorder - 1 &&
		loc.y > upBorder &&
		loc.y < height - downBorder - 1;
}

void Board::Constrict()
{
	leftBorder++;
	rightBorder++;
	upBorder++;
	downBorder++;
}

void Board::unConstrict()
{
	if (leftBorder > 0) {
		leftBorder--;
		rightBorder--;
		upBorder--;
		downBorder--;
	}
}

void Board::DrawBorder()
{
	for (int i = leftBorder; i < getGridWidth() - rightBorder; i++) {
		Location loc1 = { i, upBorder };
		DrawCell(loc1, Colors::Gray, 2);
		Location loc2 = { i, getGridHeight() - 1 - downBorder };
		DrawCell(loc2, Colors::Gray, 2);
	}
	for (int i = upBorder; i < getGridHeight() - downBorder; i++) {
		Location loc1 = { leftBorder, i };
		DrawCell(loc1, Colors::Gray, 2);
		Location loc2 = { getGridWidth() - 1 - rightBorder, i };
		DrawCell(loc2, Colors::Gray, 2);
	}
}

int Board::getLeftBorder() const
{
	return leftBorder;
}

int Board::getRightBorder() const
{
	return rightBorder;
}

int Board::getUpBorder() const
{
	return upBorder;
}

int Board::getDownBorder() const
{
	return downBorder;
}



