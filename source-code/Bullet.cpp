#include "Bullet.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

Bullet::Bullet(
	float x, float y,
	float velX, float velY,
	float angleDeg,
	float damage,
	float durationSecs,
	const sf::Texture &texture)
	:
	Collidable(
		x, y,
		static_cast<float>(texture.getSize().x),
		static_cast<float>(texture.getSize().y)),
	Positionable(x, y),
	sf::Drawable(),
	sprite_(texture),
	durationTimer_(durationSecs),
	velX_(velX),
	velY_(velY),
	angleDeg_(angleDeg),
	damage_(damage),
	isLive_(true)
{
	x_ -= width_ * 0.5f;
	y_ -= height_ * 0.5f;

	sprite_.setPosition(x_, y_);
}

void Bullet::update(float deltaTime)
{
	durationTimer_.update(deltaTime);
	if (durationTimer_.isDone())
	{
		isLive_ = false;
	}

	x_ += velX_ * deltaTime;
	y_ += velY_ * deltaTime;

	sprite_.setPosition(x_, y_);
}

void Bullet::kill()
{
	isLive_ = false;
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.rotate(
		45.0f + angleDeg_,
		x_ + width_ * 0.5f,
		y_ + height_ * 0.5f);

	target.draw(sprite_, states);
}

float Bullet::getDamage() const
{
	return damage_;
}

bool Bullet::isLive() const
{
	return isLive_;
}