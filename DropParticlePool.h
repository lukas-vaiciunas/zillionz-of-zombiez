#pragma once

class ParticlePool;

#include "Pool.h"
#include "DropParticle.h"
#include "GibData.h"
#include <SFML/Graphics/Drawable.hpp>

class DropParticlePool :
	public Pool<DropParticle>,
	public sf::Drawable
{
public:
	DropParticlePool(Pool::PoolType capacity, ParticlePool &particlePool);

	void update(float deltaTime);

	void spawnBloodSplatter(float x, float y, float maxY, Pool::PoolType numParticles);
	void spawnGibs(float x, float y, float maxY, GibData::GibId gibId);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	ParticlePool &particlePool_;

	GibData gibData_;
};