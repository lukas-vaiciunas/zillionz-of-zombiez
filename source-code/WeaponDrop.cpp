#include "WeaponDrop.h"
#include "EventQueue.h"
#include "Event.h"
#include "WeaponData.h"
#include "AudioData.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

WeaponDrop::WeaponDrop(
	float x, float y, float maxY,
	float angleDeg,
	float lifeSecs,
	Weapon::WeaponId weaponId)
	:
	InteractableItem(
		x, y,
		angleDeg,
		lifeSecs,
		WeaponData::getInstance().getWeapon(weaponId).getTexture(),
		"equip",
		WeaponData::getInstance().getWeapon(weaponId).getName()),
	Oscillating(x, y, maxY),
	Positionable(x, y),
	weaponId_(weaponId)
{}

void WeaponDrop::interact()
{
	if (!this->isLive())
		return;

	EventQueue::getInstance().send(new EventPickupWeapon(weaponId_));

	AudioData::getInstance().playSound(1);

	this->kill();
}

void WeaponDrop::update(float deltaTime)
{
	InteractableItem::update(deltaTime);
	Oscillating::update(deltaTime);
	this->updatePosition_();
}

Weapon::WeaponId WeaponDrop::getWeaponId() const
{
	return weaponId_;
}