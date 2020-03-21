#pragma once
#include "Board.h"
class Snake {
private:
	class Segment {
	public:
		void initHead(const Location& in_loc);
		void initBody(const Color& color);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		void DrawSmall(Board& brd) const;
		const Location& getLocation() const;
		void ChangeColor(const Color& newColor);
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw(Board& brd) const;
	Location GetNextHeadLocation(const Location& delta_loc) const;
	bool isInTile(const Location& target, const int& excludeEnd, const int& excludeBegin) const;
	void changeJumpState();
private:
	static constexpr Color headColor = Colors::Red;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr Color bodyColor2 = Colors::Green2;
	static constexpr Color bodyColor3 = Colors::Green3;
	static constexpr Color jumpColor = Colors::Magenta;
	static constexpr Color dumbColor = Colors::Black;//colors are wonderful
	static constexpr int nSegmentsMax = 600;
	bool jumpState = false;
	Segment segments[nSegmentsMax];
	int snakeSize = 1;
};
