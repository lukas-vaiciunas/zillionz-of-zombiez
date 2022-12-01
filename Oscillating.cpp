#include "Oscillating.h"
#include "Constants.h"

Oscillating::Oscillating(float x, float y, float maxY) :
	Positionable(x, y),
	state_(State::Up),
	maxY_(maxY)
{}

void Oscillating::update(float deltaTime)
{
	switch (state_)
	{
		case State::Up:
			this->updateOscillationUp_(deltaTime);
			break;
		case State::Down:
			this->updateOscillationDown_(deltaTime);
			break;
	}
}

void Oscillating::updateOscillationUp_(float deltaTime)
{
	float minY = maxY_ - Constants::tileSize * 0.5f;

	float velY = Constants::tileSize * y_ / minY;
	y_ -= velY * deltaTime;

	if (y_ <= minY)
	{
		y_ = minY;
		state_ = State::Down;
	}
}

void Oscillating::updateOscillationDown_(float deltaTime)
{
	float velY = Constants::tileSize * maxY_ / y_;
	y_ += velY * deltaTime;

	if (y_ >= maxY_)
	{
		y_ = maxY_;
		state_ = State::Up;
	}
}