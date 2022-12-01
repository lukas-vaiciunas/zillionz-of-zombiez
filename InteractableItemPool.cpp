#include "InteractableItemPool.h"
#include "FallingWeaponDrop.h"
#include "FoodDrop.h"
#include "Event.h"
#include "RandGen.h"
#include <SFML/Graphics/RenderTarget.hpp>

InteractableItemPool::InteractableItemPool(Pool::PoolType capacity) :
	Pool(capacity),
	Listener({ EventType::DropWeapon, EventType::DropFood }),
	sf::Drawable()
{}

void InteractableItemPool::onEvent(const Event &ev)
{
	if (ev.getType() == EventType::DropWeapon)
	{
		const EventDropWeapon &trueEv = static_cast<const EventDropWeapon &>(ev);

		this->spawnFallingWeaponDrop(trueEv.getX(), trueEv.getY(), trueEv.getMaxY(), trueEv.getWeaponId());
	}
	else if (ev.getType() == EventType::DropFood)
	{
		const EventDropFood &trueEv = static_cast<const EventDropFood &>(ev);

		this->spawnFoodDrop(trueEv.getX(), trueEv.getY(), trueEv.getMaxY());
	}
}

void InteractableItemPool::update(float deltaTime)
{
	for (Pool::PoolType i = 0; i < numLive_; )
	{
		items_[i]->update(deltaTime);

		if (!items_[i]->isLive())
		{
			delete items_[i];
			this->removeAtIndex_(i);
		}
		else ++i;
	}
}

void InteractableItemPool::spawnWeaponDrop(float x, float y, Weapon::WeaponId weaponId)
{
	if (this->isFull())
		return;

	this->add(
		new WeaponDrop(
			x, y, y,
			-45.0f,
			60.0f,
			weaponId));
}

void InteractableItemPool::spawnFallingWeaponDrop(float x, float y, float maxY, Weapon::WeaponId weaponId)
{
	if (this->isFull())
		return;

	std::mt19937 &eng = RandGen::getInstance().getEng();

	std::uniform_real_distribution<float> xVelDis(-32.0f, 32.0f);
	std::uniform_real_distribution<float> yVelDis(-48.0f, -32.0f);

	this->add(
		new FallingWeaponDrop(
			x, y, maxY,
			xVelDis(eng), yVelDis(eng),
			0.0f, 128.0f,
			-45.0f,
			60.0f,
			0,
			weaponId));
}

void InteractableItemPool::spawnFoodDrop(float x, float y, float maxY)
{
	if (this->isFull())
		return;

	std::mt19937 &eng = RandGen::getInstance().getEng();

	std::uniform_real_distribution<float> xVelDis(-32.0f, 32.0f);
	std::uniform_real_distribution<float> yVelDis(-48.0f, -32.0f);
	std::uniform_int_distribution<FoodData::Id> foodIdDis(7001, 7004);

	this->add(
		new FoodDrop(
			x, y, maxY,
			xVelDis(eng), yVelDis(eng),
			0.0f, 128.0f,
			0.0f,
			60.0f,
			0,
			foodIdDis(eng)));
}

void InteractableItemPool::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (Pool::PoolType i = 0; i < numLive_; ++i)
	{
		target.draw(*items_[i], states);
	}
}