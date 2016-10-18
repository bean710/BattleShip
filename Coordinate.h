#pragma once

class Coordinate {
public:
	Coordinate(int, int);
	~Coordinate();
	int getX();
	int getY();
protected:
	int x, y;
};