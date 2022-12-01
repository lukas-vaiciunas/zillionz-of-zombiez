#include "Button.h"
#include "FontData.h"
#include "Config.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

Button::Button(
	float cX, float cY,
	const std::string &text,
	const sf::Texture &texture)
	:
	Collidable(
		cX,
		cY,
		static_cast<float>(texture.getSize().x),
		static_cast<float>(texture.getSize().y)),
	Positionable(cX, cY),
	sf::Drawable(),
	sprite_(texture),
	text_(text, FontData::getInstance().getFont(), Config::smallFontSize),
	isHovered_(false),
	isPressed_(false),
	isActivated_(false)
{
	x_ -= width_ * 0.5f;
	y_ -= height_ * 0.5f;

	sprite_.setPosition(x_, y_);

	text_.setOrigin(
		text_.getLocalBounds().left + text_.getLocalBounds().width * 0.5f,
		text_.getLocalBounds().top + text_.getLocalBounds().height * 0.5f);
	text_.setPosition(cX * Config::globalScale, cY * Config::globalScale);
	text_.setFillColor(sf::Color(236, 236, 236));
	text_.setOutlineColor(sf::Color(0, 0, 0));
	text_.setOutlineThickness(Config::smallFontSize / 8.0f);
}

void Button::updateOnMouseMove(int mouseX, int mouseY)
{
	float invGlobalScale = 1.0f / Config::globalScale;
	float relMouseX = mouseX * invGlobalScale;
	float relMouseY = mouseY * invGlobalScale;

	bool wasHovered = isHovered_;

	isHovered_ = this->contains(relMouseX, relMouseY);

	if (isHovered_ && !wasHovered)
	{
		sprite_.setColor(sf::Color(200, 200, 200, 255));
	}
	else if (!isHovered_ && wasHovered)
	{
		sprite_.setColor(sf::Color(255, 255, 255, 255));
	}
}

void Button::updateOnMousePress(sf::Mouse::Button button)
{
	isPressed_ = isHovered_ && button == sf::Mouse::Button::Left;

	if (isPressed_)
	{
		sprite_.setColor(sf::Color(175, 175, 175, 255));
	}
}

void Button::updateOnMouseRelease(sf::Mouse::Button button)
{
	isActivated_ = isPressed_ && button == sf::Mouse::Button::Left;
	isPressed_ = false;

	if (isActivated_)
	{
		sprite_.setColor(sf::Color(255, 255, 255, 255));
	}
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
	target.draw(text_);
}

bool Button::isActivated() const
{
	return isActivated_;
}