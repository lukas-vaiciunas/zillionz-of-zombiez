#include "SoundPool.h"

SoundPool::SoundPool(Pool::PoolType capacity) :
	Pool(capacity)
{}

void SoundPool::update()
{
	for (Pool::PoolType i = 0; i < numLive_; )
	{
		if (items_[i]->getStatus() == sf::Sound::Status::Stopped)
		{
			delete items_[i];
			this->removeAtIndex_(i);
		}
		else ++i;
	}
}