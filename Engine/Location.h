struct Location {
	void Add(const Location& val) {
		x += val.x;
		y += val.y;
	}
	bool operator==(const Location& r) const {
		return x == r.x && y == r.y;
	}
	int x;
	int y;
};
