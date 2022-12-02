#include "ParticlePool.h"
#include <SFML/Graphics/RenderTarget.hpp>

ParticlePool::ParticlePool(Pool::PoolType capacity) :
	Pool(capacity),
	sf::Drawable()
{}

void ParticlePool::update(float deltaTime)
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

void ParticlePool::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (Pool::PoolType i = 0; i < numLive_; ++i)
	{
		target.draw(*items_[i], states);
	}
}