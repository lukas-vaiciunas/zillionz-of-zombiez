#pragma once

#include "DurationTimer.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Particle : public sf::Drawable
{
public:
	Particle(
		float x, float y,
		float velX, float velY,
		float accX, float accY,
		float angleDeg,
		float velAngleDeg,
		float durationSecs,
		const sf::Texture &texture);

	virtual ~Particle() {}

	virtual void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool isLive() const;
protected:
	sf::Sprite sprite_;

	DurationTimer durationTimer_;

	float x_;
	float y_;
	float velX_;
	float velY_;
	float accX_;
	float accY_;

	float angleDeg_;
	float velAngleDeg_;

	void updateDuration_(float deltaTime);
	void updateMovement_(float deltaTime);
	void updatePosition_();
};