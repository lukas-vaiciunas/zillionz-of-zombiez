#pragma once

class ZombiePool;

#include "DurationTimer.h"

class Level
{
public:
	Level(ZombiePool &zombiePool, float spawnRadius, float spawnDelaySecs);

	void update(float deltaTime, float playerX, float playerY);
private:
	ZombiePool &zombiePool_;

	DurationTimer spawnTimer_;
	float spawnRadius_;

	void spawnZombie_(float playerX, float playerY);
};