#include "Collidable.h"

Collidable::Collidable(float x, float y, float width, float height) :
	Positionable(x, y),
	width_(width),
	height_(height)
{}

void Collidable::constrain(float x1, float y1, float x2, float y2)
{
	if (x_ < x1) x_ = x1;
	if (y_ < y1) y_ = y1;
	if (x_ + width_ > x2) x_ = x2 - width_;
	if (y_ + height_ > y2) y_ = y2 - height_;
}

bool Collidable::isCollidingWith(const Collidable &other) const
{
	return x_ < other.x_ + other.width_
		&& x_ + width_ > other.x_
		&& y_ < other.y_ + other.height_
		&& y_ + height_ > other.y_;
}

bool Collidable::contains(float x, float y) const
{
	return x > x_
		&& y > y_
		&& x < x_ + width_
		&& y < y_ + height_;
}

float Collidable::getWidth() const
{
	return width_;
}

float Collidable::getHeight() const
{
	return height_;
}