#pragma once

#include "Positionable.h"
#include <cinttypes>

class Falling : public virtual Positionable
{
public:
	Falling(
		float x, float y, float maxY,
		float velX, float velY,
		float accX, float accY,
		uint8_t maxNumBounces);

	virtual ~Falling() {}

	void update(float deltaTime);

	bool isDone() const;
private:
	float maxY_;
	float velX_;
	float velY_;
	float maxVelY_;
	float accX_;
	float accY_;
	uint8_t maxNumBounces_;
	uint8_t numBounces_;

	bool isDone_;
};