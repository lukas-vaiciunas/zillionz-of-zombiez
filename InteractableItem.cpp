#include "InteractableItem.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

InteractableItem::InteractableItem(
	float x, float y,
	float angleDeg,
	float lifeSecs,
	const sf::Texture &texture,
	const std::string &interactVerb,
	const std::string &name)
	:
	Interactable(interactVerb, name),
	Collidable(
		x,
		y,
		static_cast<float>(texture.getSize().x),
		static_cast<float>(texture.getSize().y)),
	Living(lifeSecs),
	sf::Drawable(),
	sprite_(texture),
	angleDeg_(angleDeg)
{
	x_ -= width_ * 0.5f;
	y_ -= height_ * 0.5f;

	this->updatePosition_();
}

void InteractableItem::update(float deltaTime)
{
	Living::update(deltaTime);
}

void InteractableItem::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.rotate(
		angleDeg_,
		x_ + width_ * 0.5f,
		y_ + height_ * 0.5f);

	target.draw(sprite_, states);
}

void InteractableItem::updatePosition_()
{
	sprite_.setPosition(x_, y_);
}