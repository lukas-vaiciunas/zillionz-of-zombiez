#include "Humanoid.h"
#include <SFML/Graphics/RenderTarget.hpp>

Humanoid::Humanoid(float x, float y, const HumanoidAnimation &animation) :
	Collidable(x, y, animation.getFrameWidth(), animation.getFrameHeight()),
	Positionable(x, y),
	sf::Drawable(),
	animation_(animation)
{
	animation_.setPosition(x_, y_);
}

void Humanoid::constrain(float x1, float y1, float x2, float y2)
{
	Collidable::constrain(x1, y1, x2, y2);

	animation_.setPosition(x_, y_);
}

void Humanoid::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(animation_, states);
}