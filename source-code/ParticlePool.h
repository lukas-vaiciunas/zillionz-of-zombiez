#pragma once

#include "Pool.h"
#include "Particle.h"

class ParticlePool :
	public Pool<Particle>,
	public sf::Drawable
{
public:
	ParticlePool(Pool::PoolType capacity);

	void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};