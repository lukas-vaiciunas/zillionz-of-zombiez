#pragma once

#include "Particle.h"

class DropParticle : public Particle
{
public:
	DropParticle(
		float x, float y,
		float maxY,
		float velX, float velY,
		float accX, float accY,
		float angleDeg,
		float velAngleDeg,
		float durationSecs,
		uint8_t maxNumBounces,
		const sf::Texture &texture);

	void update(float deltaTime) override;

	bool isFalling() const;
private:
	enum class State : uint8_t
	{
		Falling,
		Still
	};

	State state_;

	float maxY_;
	float maxVelY_;
	uint8_t maxNumBounces_;
	uint8_t numBounces_;
};