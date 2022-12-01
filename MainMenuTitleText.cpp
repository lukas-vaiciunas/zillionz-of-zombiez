#include "MainMenuTitleText.h"
#include "FontData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

MainMenuTitleText::MainMenuTitleText() :
	sf::Drawable(),
	state_(State::Shrink),
	zillionzText_("Zillionz", FontData::getInstance().getFont(), Config::largeFontSize),
	ofText_("of", FontData::getInstance().getFont(), Config::largeFontSize),
	zombiezText_("Zombiez", FontData::getInstance().getFont(), Config::largeFontSize),
	scale_(1.0f),
	minScale_(0.75f),
	velScale_(1.0f)
{
	zillionzText_.setOrigin(
		zillionzText_.getLocalBounds().left + zillionzText_.getLocalBounds().width * 0.5f,
		zillionzText_.getLocalBounds().top + zillionzText_.getLocalBounds().height * 0.5f);
	zillionzText_.setPosition(
		Config::windowWidth * 0.5f,
		Config::windowHeight * 0.15f);
	zillionzText_.setFillColor(sf::Color(156, 204, 124));
	zillionzText_.setOutlineColor(sf::Color(0, 0, 0));
	zillionzText_.setOutlineThickness(Config::largeFontSize / 8.0f);

	ofText_.setOrigin(
		ofText_.getLocalBounds().left + ofText_.getLocalBounds().width * 0.5f,
		ofText_.getLocalBounds().top + ofText_.getLocalBounds().height * 0.5f);
	ofText_.setPosition(
		Config::windowWidth * 0.5f,
		zillionzText_.getPosition().y + zillionzText_.getLocalBounds().height);
	ofText_.setFillColor(sf::Color(236, 236, 236));
	ofText_.setOutlineColor(sf::Color(0, 0, 0));
	ofText_.setOutlineThickness(Config::largeFontSize / 8.0f);

	zombiezText_.setOrigin(
		zombiezText_.getLocalBounds().left + zombiezText_.getLocalBounds().width * 0.5f,
		zombiezText_.getLocalBounds().top + zombiezText_.getLocalBounds().height * 0.5f);
	zombiezText_.setPosition(
		Config::windowWidth * 0.5f,
		ofText_.getPosition().y + ofText_.getLocalBounds().height);
	zombiezText_.setFillColor(sf::Color(156, 204, 124));
	zombiezText_.setOutlineColor(sf::Color(0, 0, 0));
	zombiezText_.setOutlineThickness(Config::largeFontSize / 8.0f);
}

void MainMenuTitleText::update(float deltaTime)
{
	switch (state_)
	{
		case State::Shrink:
			scale_ -= velScale_ * deltaTime;
			if (scale_ <= minScale_)
			{
				scale_ = minScale_;
				state_ = State::Expand;
			}
			break;
		case State::Expand:
			scale_ += velScale_ * deltaTime;
			if (scale_ >= 1.0f)
			{
				scale_ = 1.0f;
				state_ = State::Shrink;
			}
			break;
	}
}

void MainMenuTitleText::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(
		scale_,
		scale_,
		ofText_.getPosition().x,
		ofText_.getPosition().y);

	target.draw(zillionzText_, states);
	target.draw(ofText_, states);
	target.draw(zombiezText_, states);
}