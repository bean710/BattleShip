#include "Coordinate.h"


Coordinate::Coordinate (int a, int b)
{
	x = a;
	y = b;
}


int Coordinate::getX() {
	return x;
}

int Coordinate::getY() {
	return y;
}

Coordinate::~Coordinate()
{
}
