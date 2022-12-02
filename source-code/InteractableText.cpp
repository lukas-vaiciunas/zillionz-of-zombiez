#include "InteractableText.h"
#include "FontData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

InteractableText::InteractableText(float x, float y) :
	text_("", FontData::getInstance().getFont(), Config::smallFontSize),
	isActive_(false)
{
	text_.setPosition(x, y);
	text_.setFillColor(sf::Color(236, 236, 236));
	text_.setOutlineColor(sf::Color(0, 0, 0));
	text_.setOutlineThickness(Config::smallFontSize / 8.0f);
}

void InteractableText::set(const std::string &verb, const std::string &interactableName)
{
	text_.setString("[F] " + verb + " " + interactableName);

	text_.setOrigin(
		text_.getLocalBounds().left + text_.getLocalBounds().width * 0.5f,
		text_.getLocalBounds().top + text_.getLocalBounds().height * 0.5f);
}

void InteractableText::activate()
{
	isActive_ = true;
}

void InteractableText::deactivate()
{
	isActive_ = false;
}

void InteractableText::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (!isActive_)
		return;

	target.draw(text_);
}