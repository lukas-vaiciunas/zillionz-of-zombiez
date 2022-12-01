#pragma once

#include "Pool.h"
#include "Zombie.h"
#include <SFML/Graphics/Drawable.hpp>

class ZombiePool :
	public Pool<Zombie>,
	public sf::Drawable
{
public:
	ZombiePool(Pool::PoolType capacity);

	void update(
		float deltaTime,
		Player &player,
		BulletPool &bulletPool,
		DropParticlePool &dropParticlePool,
		std::vector<CollidableTile *> &collidableTiles);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};