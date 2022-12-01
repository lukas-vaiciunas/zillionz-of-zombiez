#include "DurationTimer.h"

DurationTimer::DurationTimer(float targetSecs) :
	targetSecs_(targetSecs),
	elapsedSecs_(0.0f)
{}

void DurationTimer::update(float deltaTime)
{
	if(!this->isDone())
		elapsedSecs_ += deltaTime;
}

void DurationTimer::hardReset()
{
	elapsedSecs_ = 0.0f;
}

void DurationTimer::softReset()
{
	elapsedSecs_ -= targetSecs_;
}

void DurationTimer::rig()
{
	elapsedSecs_ = targetSecs_;
}

bool DurationTimer::isDone() const
{
	return elapsedSecs_ >= targetSecs_;
}

float DurationTimer::getTargetSecs() const
{
	return targetSecs_;
}

float DurationTimer::getElapsedSecs() const
{
	return elapsedSecs_;
}