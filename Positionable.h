#pragma once

class Positionable
{
public:
	Positionable(float x, float y);
	virtual ~Positionable() {}

	float getX() const;
	float getY() const;
protected:
	float x_;
	float y_;
};