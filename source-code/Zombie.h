#pragma once

class BulletPool;
class DropParticlePool;
class ZombiePool;
class WeaponDropPool;
class CollidableTile;
class Player;

#include "Humanoid.h"
#include "DurationTimer.h"

class Zombie : public Humanoid
{
public:
	Zombie(
		float x, float y,
		float speed,
		float health,
		float damage,
		float attackCooldownSecs,
		const HumanoidAnimation &animation);

	void update(
		float deltaTime,
		Player &player,
		BulletPool &bulletPool,
		DropParticlePool &dropParticlePool,
		ZombiePool &zombiePool,
		std::vector<CollidableTile *> &collidableTiles);

	bool isLive() const;
private:
	DurationTimer attackCooldownTimer_;

	float speed_;
	float health_;
	float damage_;

	bool isLive_;

	void applySeparationSteering_(ZombiePool &zombiePool, float &velX, float &velY);
	void normalizeVelocity_(float &velX, float &velY);
	void updateAnimation_(float deltaTime, float velX, float velY);
	void updateMovement_(
		float deltaTime,
		float targetX, float targetY,
		ZombiePool &zombiePool,
		std::vector<CollidableTile *> &collidableTiles,
		DropParticlePool &dropParticlePool);
	void updateAttacking_(float deltaTime, Player &player, DropParticlePool &dropParticlePool);
	void updateTileCollisionsX_(
		std::vector<CollidableTile *> &collidableTiles,
		DropParticlePool &dropParticlePool);
	void updateTileCollisionsY_(
		std::vector<CollidableTile *> &collidableTiles,
		DropParticlePool &dropParticlePool);
	void updateBulletCollisions_(
		BulletPool &bulletPool,
		DropParticlePool &dropParticlePool);
	void spawnDrops_();
};