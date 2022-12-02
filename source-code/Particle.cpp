#include "Particle.h"
#include <SFML/Graphics/RenderTarget.hpp>

Particle::Particle(
	float x, float y,
	float velX, float velY,
	float accX, float accY,
	float angleDeg,
	float velAngleDeg,
	float durationSecs,
	const sf::Texture &texture)
	:
	sf::Drawable(),
	sprite_(texture),
	durationTimer_(durationSecs),
	x_(x),
	y_(y),
	velX_(velX),
	velY_(velY),
	accX_(accX),
	accY_(accY),
	angleDeg_(angleDeg),
	velAngleDeg_(velAngleDeg)
{
	sprite_.setOrigin(
		sprite_.getLocalBounds().width * 0.5f,
		sprite_.getLocalBounds().height * 0.5f);

	sprite_.setPosition(x_, y_);
}

void Particle::update(float deltaTime)
{
	this->updateDuration_(deltaTime);
	this->updateMovement_(deltaTime);
	this->updatePosition_();
}

void Particle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.rotate(
		angleDeg_,
		sprite_.getPosition().x,
		sprite_.getPosition().y);

	target.draw(sprite_, states);
}

bool Particle::isLive() const
{
	return !durationTimer_.isDone();
}

void Particle::updateDuration_(float deltaTime)
{
	durationTimer_.update(deltaTime);
	
	float durationRatioThreshold = 0.9f;
	float durationRatio = durationTimer_.getElapsedSecs() / durationTimer_.getTargetSecs();
	if (durationRatio >= durationRatioThreshold)
	{
		float alphaMult = 1.0f - (durationRatio - durationRatioThreshold) / (1.0f - durationRatioThreshold);
		sprite_.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 * alphaMult)));
	}
}

void Particle::updateMovement_(float deltaTime)
{
	x_ += velX_ * deltaTime;
	y_ += velY_ * deltaTime;
	velX_ += accX_ * deltaTime;
	velY_ += accY_ * deltaTime;
	angleDeg_ += velAngleDeg_ * deltaTime;
}

void Particle::updatePosition_()
{
	sprite_.setPosition(x_, y_);
}