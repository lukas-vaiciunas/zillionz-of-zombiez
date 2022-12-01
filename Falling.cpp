#include "Falling.h"

Falling::Falling(
	float x, float y, float maxY,
	float velX, float velY,
	float accX, float accY,
	uint8_t maxNumBounces)
	:
	Positionable(x, y),
	maxY_(maxY),
	velX_(velX),
	velY_(velY),
	maxVelY_(velY),
	accX_(accX),
	accY_(accY),
	maxNumBounces_(maxNumBounces),
	numBounces_(0),
	isDone_(false)
{}

void Falling::update(float deltaTime)
{
	x_ += velX_ * deltaTime;
	y_ += velY_ * deltaTime;
	velX_ += accX_ * deltaTime;
	velY_ += accY_ * deltaTime;

	if (y_ >= maxY_)
	{
		y_ = maxY_;

		if (++numBounces_ <= maxNumBounces_)
		{
			velY_ = maxVelY_ / (numBounces_ + 1);
		}
		else
		{
			isDone_ = true;
		}
	}
}

bool Falling::isDone() const
{
	return isDone_;
}