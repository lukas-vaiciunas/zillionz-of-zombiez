#pragma once

#include "Collidable.h"
#include "DurationTimer.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Bullet :
	public Collidable,
	public sf::Drawable
{
public:
	Bullet(
		float x, float y,
		float velX, float velY,
		float angleDeg,
		float damage,
		float durationSecs,
		const sf::Texture &texture);

	void update(float deltaTime);

	void kill();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	float getDamage() const;
	bool isLive() const;
private:
	sf::Sprite sprite_;

	DurationTimer durationTimer_;

	float velX_;
	float velY_;
	float angleDeg_;

	float damage_;

	bool isLive_;
};