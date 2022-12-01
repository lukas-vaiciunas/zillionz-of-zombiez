#include "DropParticlePool.h"
#include "ParticlePool.h"
#include "RandGen.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

DropParticlePool::DropParticlePool(Pool::PoolType capacity, ParticlePool &particlePool) :
	Pool(capacity),
	sf::Drawable(),
	particlePool_(particlePool),
	gibData_()
{}

void DropParticlePool::update(float deltaTime)
{
	for (Pool::PoolType i = 0; i < numLive_; )
	{
		items_[i]->update(deltaTime);

		if (!items_[i]->isFalling())
		{
			if (!particlePool_.isFull())
			{
				particlePool_.add(items_[i]);
			}
			else
			{
				delete items_[i];
			}
			this->removeAtIndex_(i);
		}
		else ++i;
	}
}

void DropParticlePool::spawnBloodSplatter(float x, float y, float maxY, Pool::PoolType numParticles)
{
	const TextureData &textureData = TextureData::getInstance();
	std::mt19937 &eng = RandGen::getInstance().getEng();

	std::uniform_real_distribution<float> xVelDis(-16.0f, 16.0f);
	std::uniform_real_distribution<float> yVelDis(-64.0f, -48.0f);
	std::uniform_real_distribution<float> maxYDepthDis(0.0f, Constants::tileSize);
	std::uniform_int_distribution<TextureData::TextureId> textureIdDis(4001, 4003);

	for (Pool::PoolType i = 0; i < numParticles; ++i)
	{
		if (this->isFull()) return;

		float xVel = xVelDis(eng);

		this->add(
			new DropParticle(
				x, y, maxY + maxYDepthDis(eng),
				xVel, yVelDis(eng),
				0.0f, 128.0f,
				0.0f,
				xVel * 8.0f,
				1.0f,
				2,
				textureData.getTexture(textureIdDis(eng))));
	}
}

void DropParticlePool::spawnGibs(float x, float y, float maxY, GibData::GibId gibId)
{
	const TextureData &textureData = TextureData::getInstance();
	std::mt19937 &eng = RandGen::getInstance().getEng();

	std::uniform_real_distribution<float> xVelDis(-16.0f, 16.0f);
	std::uniform_real_distribution<float> yVelDis(-64.0f, -48.0f);
	std::uniform_real_distribution<float> angleDegDis(0.0f, 180.0f);
	std::uniform_real_distribution<float> maxYDepthDis(0.0f, Constants::tileSize);

	const GibData::Gibs &gibs = gibData_.getGibs(gibId);

	for (auto it = gibs.begin(); it != gibs.end(); ++it)
	{
		for (GibData::GibAmount i = 0; i < it->second; ++i)
		{
			if (this->isFull()) return;

			float xVel = xVelDis(eng);

			this->add(
				new DropParticle(
					x, y, maxY + maxYDepthDis(eng),
					xVel, yVelDis(eng),
					0.0f, 128.0f,
					angleDegDis(eng),
					xVel * 8.0f,
					1.0f,
					2,
					textureData.getTexture(it->first)));
		}
	}
}

void DropParticlePool::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (Pool::PoolType i = 0; i < numLive_; ++i)
	{
		target.draw(*items_[i], states);
	}
}