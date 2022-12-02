#include "Zombie.h"
#include "BulletPool.h"
#include "DropParticlePool.h"
#include "ZombiePool.h"
#include "CollidableTile.h"
#include "Player.h"
#include "EventQueue.h"
#include "Event.h"
#include "WeaponData.h"
#include "AudioData.h"
#include "RandGen.h"

Zombie::Zombie(
	float x, float y,
	float speed,
	float health,
	float damage,
	float attackCooldownSecs,
	const HumanoidAnimation &animation)
	:
	Humanoid(x, y, animation),
	Positionable(x, y),
	attackCooldownTimer_(attackCooldownSecs),
	speed_(speed),
	health_(health),
	damage_(damage),
	isLive_(true)
{}

void Zombie::update(
	float deltaTime,
	Player &player,
	BulletPool &bulletPool,
	DropParticlePool &dropParticlePool,
	ZombiePool &zombiePool,
	std::vector<CollidableTile *> &collidableTiles)
{
	this->updateMovement_(
		deltaTime,
		player.getX() + player.getWidth() * 0.5f,
		player.getY() + player.getHeight() * 0.5f,
		zombiePool,
		collidableTiles,
		dropParticlePool);

	this->updateAttacking_(deltaTime, player, dropParticlePool);

	this->updateBulletCollisions_(bulletPool, dropParticlePool);
}

bool Zombie::isLive() const
{
	return isLive_;
}

void Zombie::applySeparationSteering_(ZombiePool &zombiePool, float &velX, float &velY)
{
	float cX = x_ + width_ * 0.5f;
	float cY = y_ + height_ * 0.5f;

	float threshold = std::max(width_, height_) * 1.5f;
	float thresholdSq = threshold * threshold;

	float velXComponent = 0.0f;
	float velYComponent = 0.0f;

	for (auto it = zombiePool.begin(); it != zombiePool.end(); ++it)
	{
		if (this == *it) continue;

		float otherCX = (*it)->getX() + (*it)->getWidth() * 0.5f;
		float otherCY = (*it)->getY() + (*it)->getHeight() * 0.5f;

		float dX = otherCX - cX;
		float dY = otherCY - cY;

		float distanceSq = dX * dX + dY * dY;
		
		if (distanceSq <= thresholdSq)
		{
			velXComponent -= (dX != 0.0f) ? threshold / dX * threshold : threshold;
			velYComponent -= (dY != 0.0f) ? threshold / dY * threshold : threshold;
		}
	}

	velX += velXComponent;
	velY += velYComponent;
}

void Zombie::normalizeVelocity_(float &velX, float &velY)
{
	float currSpeedSq = velX * velX + velY * velY;
	float maxSpeedSq = speed_ * speed_;

	if (currSpeedSq > maxSpeedSq)
	{
		float repairRatio = speed_ / sqrtf(currSpeedSq);

		velX *= repairRatio;
		velY *= repairRatio;
	}
}

void Zombie::updateAnimation_(float deltaTime, float velX, float velY)
{
	animation_.setPosition(x_, y_);

	if (velX != 0.0f || velY != 0.0f)
	{
		animation_.setState(HumanoidAnimation::State::Move);
	}
	else
	{
		animation_.setState(HumanoidAnimation::State::Idle);
	}

	animation_.update(deltaTime);
}

void Zombie::updateMovement_(
	float deltaTime,
	float targetX, float targetY,
	ZombiePool &zombiePool,
	std::vector<CollidableTile *> &collidableTiles,
	DropParticlePool &dropParticlePool)
{
	float dX = targetX - (x_ + width_ * 0.5f);
	float dY = targetY - (y_ + height_ * 0.5f);

	float angleToTargetRad = atan2f(dY, dX);

	float velX = speed_ * cosf(angleToTargetRad);
	float velY = speed_ * sinf(angleToTargetRad);

	this->applySeparationSteering_(zombiePool, velX, velY);

	this->normalizeVelocity_(velX, velY);

	x_ += velX * deltaTime;
	this->updateTileCollisionsX_(collidableTiles, dropParticlePool);

	y_ += velY * deltaTime;
	this->updateTileCollisionsY_(collidableTiles, dropParticlePool);

	this->updateAnimation_(deltaTime, velX, velY);
}

void Zombie::updateAttacking_(float deltaTime, Player &player, DropParticlePool &dropParticlePool)
{
	attackCooldownTimer_.update(deltaTime);

	if (attackCooldownTimer_.isDone() && player.isLive() && this->isCollidingWith(player))
	{
		attackCooldownTimer_.softReset();

		player.hurt(damage_, dropParticlePool);

		AudioData::getInstance().playRandomizedSound(42);
	}
}

void Zombie::updateTileCollisionsX_(
	std::vector<CollidableTile *> &collidableTiles,
	DropParticlePool &dropParticlePool)
{
	float cX = x_ + width_ * 0.5f;

	for (auto it = collidableTiles.begin(); it != collidableTiles.end(); ++it)
	{
		const Collidable &collidable = static_cast<const Collidable &>(**it);

		if (this->isCollidingWith(collidable))
		{
			float otherX1 = collidable.getX();
			float otherWidth = collidable.getWidth();
			float otherX2 = otherX1 + otherWidth;

			if (x_ < otherX2 && x_ + width_ > otherX1)
			{
				float otherCX = otherX1 + otherWidth * 0.5f;

				if (cX < otherCX)
				{
					x_ -= x_ + width_ - otherX1;
				}
				else
				{
					x_ += otherX2 - x_;
				}
			}

			if (attackCooldownTimer_.isDone())
			{
				attackCooldownTimer_.softReset();

				(*it)->hurt(damage_, x_ + width_ * 0.5f, y_ + height_ * 0.5f, dropParticlePool);
			}

			break;
		}
	}
}

void Zombie::updateTileCollisionsY_(
	std::vector<CollidableTile *> &collidableTiles,
	DropParticlePool &dropParticlePool)
{
	float cY = y_ + height_ * 0.5f;

	for (auto it = collidableTiles.begin(); it != collidableTiles.end(); ++it)
	{
		const Collidable &collidable = static_cast<const Collidable &>(**it);

		if (this->isCollidingWith(collidable))
		{
			float otherY1 = collidable.getY();
			float otherHeight = collidable.getHeight();
			float otherY2 = otherY1 + otherHeight;

			if (y_ < otherY2 && y_ + height_ > otherY1)
			{
				float otherCY = otherY1 + otherHeight * 0.5f;

				if (cY < otherCY)
				{
					y_ -= y_ + height_ - otherY1;
				}
				else
				{
					y_ += otherY2 - y_;
				}
			}

			if (attackCooldownTimer_.isDone())
			{
				attackCooldownTimer_.softReset();

				(*it)->hurt(damage_, x_ + width_ * 0.5f, y_ + height_ * 0.5f, dropParticlePool);
			}

			break;
		}
	}
}

void Zombie::updateBulletCollisions_(
	BulletPool &bulletPool,
	DropParticlePool &dropParticlePool)
{
	for (auto it = bulletPool.begin(); it != bulletPool.end(); ++it)
	{
		if ((*it)->isLive() && this->isCollidingWith(**it))
		{
			health_ -= (*it)->getDamage();
			if (health_ <= 0.0f)
			{
				health_ = 0.0f;
				isLive_ = false;

				dropParticlePool.spawnGibs(
					x_ + width_ * 0.5f,
					y_ + height_ * 0.5f,
					y_ + height_,
					3);

				AudioData::getInstance().playRandomizedSound(41);

				this->spawnDrops_();

				EventQueue::getInstance().send(new EventEnemyWasKilled());
			}

			dropParticlePool.spawnBloodSplatter(
				x_ + width_ * 0.5f,
				y_ + height_ * 0.5f,
				y_ + height_,
				3);

			(*it)->kill();
			break;
		}
	}
}

void Zombie::spawnDrops_()
{
	const WeaponData &weaponData = WeaponData::getInstance();
	std::mt19937 &eng = RandGen::getInstance().getEng();

	float roll = std::uniform_real_distribution<float>(0.0f, 1.0f)(eng);

	if (roll >= 0.95f)
	{
		const std::vector<Weapon::WeaponId> weaponIds = weaponData.getWeaponIds();

		Weapon::WeaponId weaponId = weaponIds[std::uniform_int_distribution<size_t>(0, weaponIds.size() - 1)(eng)];

		EventQueue::getInstance().send(
			new EventDropWeapon(
				x_ + width_ * 0.5f,
				y_ + height_ * 0.5f,
				y_ + height_,
				weaponId));
	}
	else if (roll >= 0.9f)
	{
		EventQueue::getInstance().send(
			new EventDropFood(
				x_ + width_ * 0.5f,
				y_ + height_ * 0.5f,
				y_ + height_));
	}
}