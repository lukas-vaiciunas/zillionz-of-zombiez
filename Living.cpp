#include "Living.h"

Living::Living(float lifeSecs) :
	lifeTimer_(lifeSecs),
	isLive_(true)
{}

void Living::update(float deltaTime)
{
	lifeTimer_.update(deltaTime);
	if (lifeTimer_.isDone())
	{
		this->kill();
	}
}

void Living::kill()
{
	isLive_ = false;
}

bool Living::isLive() const
{
	return isLive_;
}