#include "Level.h"
#include "ZombiePool.h"
#include "RandGen.h"
#include "TextureData.h"
#include "Constants.h"

Level::Level(ZombiePool &zombiePool, float spawnRadius, float spawnDelaySecs) :
	zombiePool_(zombiePool),
	spawnTimer_(spawnDelaySecs),
	spawnRadius_(spawnRadius)
{}

void Level::update(float deltaTime, float playerX, float playerY)
{
	spawnTimer_.update(deltaTime);

	if (spawnTimer_.isDone() && !zombiePool_.isFull())
	{
		spawnTimer_.softReset();

		this->spawnZombie_(playerX, playerY);
	}
}

void Level::spawnZombie_(float playerX, float playerY)
{
	float spawnAngleRad = std::uniform_real_distribution<float>
		(0.0f, 2 * Constants::pi)
		(RandGen::getInstance().getEng());

	float spawnX = playerX + spawnRadius_ * cosf(spawnAngleRad);
	float spawnY = playerY + spawnRadius_ * sinf(spawnAngleRad);

	zombiePool_.add(
		new Zombie(
			spawnX, spawnY,
			32.0f,
			100.0f,
			10.0f,
			1.0f,
			HumanoidAnimation(8, 8, 0.3f, TextureData::getInstance().getTexture(501))));
}