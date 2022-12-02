#include "KillCounter.h"
#include "TextureData.h"
#include "FontData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

KillCounter::KillCounter(float x, float y) :
	sf::Drawable(),
	skullSprite_(TextureData::getInstance().getTexture(12001)),
	numKillsText_("0", FontData::getInstance().getFont(), Config::smallFontSize),
	numKills_(0)
{
	skullSprite_.setPosition(x, y);

	numKillsText_.setOrigin(
		numKillsText_.getLocalBounds().left,
		numKillsText_.getLocalBounds().top + numKillsText_.getLocalBounds().height * 0.5f);
	numKillsText_.setPosition(
		(x + skullSprite_.getLocalBounds().width * 1.5f) * Config::globalScale,
		(y + skullSprite_.getLocalBounds().height * 0.5f) * Config::globalScale);
	numKillsText_.setFillColor(sf::Color(236, 236, 236));
	numKillsText_.setOutlineColor(sf::Color(0, 0, 0));
	numKillsText_.setOutlineThickness(Config::smallFontSize / 8.0f);
}

void KillCounter::increment()
{
	++numKills_;

	numKillsText_.setString(std::to_string(numKills_));
}

void KillCounter::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(skullSprite_, states);
	target.draw(numKillsText_);
}