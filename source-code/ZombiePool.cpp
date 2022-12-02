#include "ZombiePool.h"
#include <SFML/Graphics/RenderTarget.hpp>

ZombiePool::ZombiePool(Pool::PoolType capacity) :
	Pool(capacity),
	sf::Drawable()
{}

void ZombiePool::update(
	float deltaTime,
	Player &player,
	BulletPool &bulletPool,
	DropParticlePool &dropParticlePool,
	std::vector<CollidableTile *> &collidableTiles)
{
	for (Pool::PoolType i = 0; i < numLive_; )
	{
		items_[i]->update(
			deltaTime,
			player,
			bulletPool,
			dropParticlePool,
			*this,
			collidableTiles);

		if (!items_[i]->isLive())
		{
			delete items_[i];
			this->removeAtIndex_(i);
		}
		else ++i;
	}
}

void ZombiePool::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (Pool::PoolType i = 0; i < numLive_; ++i)
	{
		target.draw(*items_[i], states);
	}
}