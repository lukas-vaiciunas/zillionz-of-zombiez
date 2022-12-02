#include "Positionable.h"

Positionable::Positionable(float x, float y) :
	x_(x),
	y_(y)
{}

float Positionable::getX() const
{
	return x_;
}

float Positionable::getY() const
{
	return y_;
}