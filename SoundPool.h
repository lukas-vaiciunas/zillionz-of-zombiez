#pragma once

#include "Pool.h"
#include <SFML/Audio/Sound.hpp>

class SoundPool : public Pool<sf::Sound>
{
public:
	SoundPool(Pool::PoolType capacity);

	void update();
};