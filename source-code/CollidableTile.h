#pragma once

class BulletPool;
class DropParticlePool;

#include "Tile.h"
#include "Collidable.h"
#include "GibData.h"

class CollidableTile :
	public Tile,
	public Collidable
{
public:
	CollidableTile(
		float x, float y,
		float maxOffset,
		float health,
		GibData::GibId hurtGibId,
		GibData::GibId killGibId,
		const sf::Texture &texture);

	void update(
		float deltaTime,
		BulletPool &bulletPool,
		DropParticlePool &dropParticlePool);

	void hurt(float damage, float sCX, float sCY, DropParticlePool &dropParticlePool);

	CollidableTile clone(float x, float y) const;

	bool isLive() const;
private:
	enum class State : uint8_t
	{
		None,
		ShakeLeft,
		ShakeRight
	};

	State state_;

	GibData::GibId hurtGibId_;
	GibData::GibId killGibId_;

	float health_;

	float maxOffset_;
	float targetOffset_;
	float offset_;
	float velOffset_;
	float offsetAngleRad_;

	bool isLive_;

	void updateShaking_(float deltaTime);
	void updateBulletCollisions_(
		BulletPool &bulletPool,
		DropParticlePool &dropParticlePool);
};