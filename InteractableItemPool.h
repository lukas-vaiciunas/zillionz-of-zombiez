#pragma once

#include "Pool.h"
#include "InteractableItem.h"
#include "Listener.h"
#include "Weapon.h"

class InteractableItemPool :
	public Pool<InteractableItem>,
	public Listener,
	public sf::Drawable
{
public:
	InteractableItemPool(Pool::PoolType capacity);

	void onEvent(const Event &ev);

	void update(float deltaTime);

	void spawnWeaponDrop(float x, float y, Weapon::WeaponId weaponId);
	void spawnFallingWeaponDrop(float x, float y, float maxY, Weapon::WeaponId weaponId);
	void spawnFoodDrop(float x, float y, float maxY);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};