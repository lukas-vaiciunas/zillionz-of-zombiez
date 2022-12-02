#pragma once

#include "WeaponDrop.h"
#include "Falling.h"

class FallingWeaponDrop :
	public WeaponDrop,
	public Falling
{
public:
	FallingWeaponDrop(
		float x, float y, float maxY,
		float velX, float velY,
		float accX, float accY,
		float angleDeg,
		float lifeSecs,
		uint8_t maxNumBounces,
		Weapon::WeaponId weaponId);

	void update(float deltaTime) override;
private:
	enum class State : uint8_t
	{
		Falling,
		Oscillating
	};

	State state_;
};