#pragma once

#include "Positionable.h"
#include <cinttypes>

class Oscillating : public virtual Positionable
{
public:
	Oscillating(float x, float y, float maxY);
	virtual ~Oscillating() {}

	virtual void update(float deltaTime);
private:
	enum class State : uint8_t
	{
		Up,
		Down
	};

	State state_;
	float maxY_;

	void updateOscillationUp_(float deltaTime);
	void updateOscillationDown_(float deltaTime);
};