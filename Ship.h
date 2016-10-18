#pragma once
#include "Coordinate.h"

class Ship {
public:
	Ship(int x1, int y1, int dir, int length);
	~Ship();

protected:
	Coordinate *positions;
};