#include "CollidableTile.h"
#include "BulletPool.h"
#include "DropParticlePool.h"
#include "AudioData.h"
#include <SFML/Graphics/Texture.hpp>

CollidableTile::CollidableTile(
	float x, float y,
	float maxOffset,
	float health,
	GibData::GibId hurtGibId,
	GibData::GibId killGibId,
	const sf::Texture &texture)
	:
	Tile(x, y, texture),
	Collidable(
		x,
		y,
		static_cast<float>(texture.getSize().x),
		static_cast<float>(texture.getSize().y)),
	Positionable(x, y),
	state_(State::None),
	hurtGibId_(hurtGibId),
	killGibId_(killGibId),
	health_(health),
	maxOffset_(maxOffset),
	targetOffset_(0.0f),
	offset_(0.0f),
	velOffset_(maxOffset * 32.0f),
	offsetAngleRad_(0.0f),
	isLive_(true)
{}

void CollidableTile::update(
	float deltaTime,
	BulletPool &bulletPool,
	DropParticlePool &dropParticlePool)
{
	this->updateShaking_(deltaTime);
	this->updateBulletCollisions_(bulletPool, dropParticlePool);
}

void CollidableTile::hurt(float damage, float sCX, float sCY, DropParticlePool &dropParticlePool)
{
	health_ -= damage;
	if (health_ <= 0.0f)
	{
		health_ = 0.0f;
		isLive_ = false;

		dropParticlePool.spawnGibs(
			x_ + width_ * 0.5f,
			y_ + height_ * 0.5f,
			y_ + height_,
			killGibId_);

		AudioData::getInstance().playRandomizedSound(31);
	}
	else
	{
		AudioData::getInstance().playRandomizedSound(32);
	}

	dropParticlePool.spawnGibs(
		x_ + width_ * 0.5f,
		y_ + height_ * 0.5f,
		y_ + height_,
		hurtGibId_);

	float dX = sCX - (x_ + width_ * 0.5f);
	float dY = sCY - (y_ + height_ * 0.5f);

	offsetAngleRad_ = atan2f(dY, dX);

	state_ = State::ShakeLeft;
	targetOffset_ = maxOffset_;
	offset_ = 0.0f;
}

CollidableTile CollidableTile::clone(float x, float y) const
{
	return CollidableTile(x, y, maxOffset_, health_, hurtGibId_, killGibId_, *sprite_.getTexture());
}

bool CollidableTile::isLive() const
{
	return isLive_;
}

void CollidableTile::updateShaking_(float deltaTime)
{
	switch (state_)
	{
		case State::ShakeLeft:
			offset_ -= velOffset_ * deltaTime;
			if (offset_ <= -targetOffset_)
			{
				offset_ = -targetOffset_;

				targetOffset_ *= 0.8f;
				if (targetOffset_ <= 0.1f)
				{
					offset_ = 0.0f;
					state_ = State::None;
				}
				else state_ = State::ShakeRight;
			}
			sprite_.setPosition(x_ + offset_ * cosf(offsetAngleRad_), y_ + offset_ * sinf(offsetAngleRad_));
			break;
		case State::ShakeRight:
			offset_ += velOffset_ * deltaTime;
			if (offset_ >= targetOffset_)
			{
				offset_ = targetOffset_;

				targetOffset_ *= 0.8f;
				if (targetOffset_ <= 0.1f)
				{
					offset_ = 0.0f;
					state_ = State::None;
				}
				else state_ = State::ShakeLeft;
			}
			sprite_.setPosition(x_ + offset_ * cosf(offsetAngleRad_), y_ + offset_ * sinf(offsetAngleRad_));
			break;
	}
}

void CollidableTile::updateBulletCollisions_(
	BulletPool &bulletPool,
	DropParticlePool &dropParticlePool)
{
	for (auto it = bulletPool.begin(); it != bulletPool.end(); ++it)
	{
		if ((*it)->isLive() && this->isCollidingWith(**it))
		{
			this->hurt(
				(*it)->getDamage(),
				(*it)->getX() + (*it)->getWidth() * 0.5f,
				(*it)->getY() + (*it)->getHeight() * 0.5f,
				dropParticlePool);

			(*it)->kill();
			break;
		}
	}
}