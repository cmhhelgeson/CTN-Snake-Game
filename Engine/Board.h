#pragma once
#include "Location.h"
#include "Graphics.h"

class Board {
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c, int sizeReduction);
	int getGridWidth() const;
	int getGridHeight() const;
	bool isInsideBoard(const Location& loc) const;
	void Constrict();
	void unConstrict();
	void DrawBorder();
	int getLeftBorder() const;
	int getRightBorder() const;
	int getUpBorder() const;
	int getDownBorder() const;
private:
	static constexpr int dimensions = 20;
	static constexpr int width = 40;
	static constexpr int height = 30;
	int leftBorder = 0;
	int rightBorder = 0;
	int upBorder = 0;
	int downBorder = 0;
	Graphics& gfx;








};
