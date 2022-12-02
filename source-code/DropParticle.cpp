#include "DropParticle.h"

DropParticle::DropParticle(
	float x, float y,
	float maxY,
	float velX, float velY,
	float accX, float accY,
	float angleDeg,
	float velAngleDeg,
	float durationSecs,
	uint8_t maxNumBounces,
	const sf::Texture &texture)
	:
	Particle(x, y, velX, velY, accX, accY, angleDeg, velAngleDeg, durationSecs, texture),
	state_(State::Falling),
	maxY_(maxY),
	maxVelY_(velY),
	maxNumBounces_(maxNumBounces),
	numBounces_(0)
{}

void DropParticle::update(float deltaTime)
{
	switch (state_)
	{
		case State::Falling:
			this->updateMovement_(deltaTime);

			if (y_ >= maxY_)
			{
				y_ = maxY_;

				if (++numBounces_ <= maxNumBounces_)
				{
					velY_ = maxVelY_ / (numBounces_ + 1);
				}
				else
				{
					state_ = State::Still;
				}
			}

			this->updatePosition_();
			break;
		case State::Still:
			this->updateDuration_(deltaTime);
			break;
	}
}

bool DropParticle::isFalling() const
{
	return state_ == State::Falling;
}