#pragma once

#include "InteractableItem.h"
#include "Oscillating.h"
#include "Weapon.h"

class WeaponDrop :
	public InteractableItem,
	public Oscillating
{
public:
	WeaponDrop(
		float x, float y, float maxY,
		float angleDeg,
		float lifeSecs,
		Weapon::WeaponId weaponId);

	virtual ~WeaponDrop() {}

	void interact() override;

	virtual void update(float deltaTime) override;

	Weapon::WeaponId getWeaponId() const;
protected:
	Weapon::WeaponId weaponId_;
};