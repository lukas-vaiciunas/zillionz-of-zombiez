#pragma once

#include "Positionable.h"

class Collidable : public virtual Positionable
{
public:
	Collidable(float x, float y, float width, float height);
	virtual ~Collidable() {}

	virtual void constrain(float x1, float y1, float x2, float y2);

	bool isCollidingWith(const Collidable &other) const;
	bool contains(float x, float y) const;

	float getWidth() const;
	float getHeight() const;
protected:
	float width_;
	float height_;
};