#include "FallingWeaponDrop.h"

FallingWeaponDrop::FallingWeaponDrop(
	float x, float y, float maxY,
	float velX, float velY,
	float accX, float accY,
	float angleDeg,
	float lifeSecs,
	uint8_t maxNumBounces,
	Weapon::WeaponId weaponId)
	:
	WeaponDrop(x, y, maxY, angleDeg, lifeSecs, weaponId),
	Falling(x, y, maxY, velX, velY, accX, accY, maxNumBounces),
	Positionable(x, y),
	state_(State::Falling)
{}

void FallingWeaponDrop::update(float deltaTime)
{
	switch (state_)
	{
		case State::Falling:
			Falling::update(deltaTime);
			if (Falling::isDone())
			{
				state_ = State::Oscillating;
			}
			sprite_.setPosition(x_, y_);
			break;
		case State::Oscillating:
			WeaponDrop::update(deltaTime);
	}
}