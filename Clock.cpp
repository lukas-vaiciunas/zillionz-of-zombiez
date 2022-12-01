#include "Clock.h"
#include "FontData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

Clock::Clock(float x, float y) :
	sf::Drawable(),
	text_("00:00:00", FontData::getInstance().getFont(), Config::smallFontSize),
	secondTimer_(1.0f),
	numSeconds_(0),
	numMinutes_(0),
	numHours_(0)
{
	text_.setOrigin(
		text_.getLocalBounds().left + text_.getLocalBounds().width * 0.5f,
		text_.getLocalBounds().top + text_.getLocalBounds().height * 0.5f);
	text_.setPosition(x, y);
	text_.setFillColor(sf::Color(236, 236, 236));
	text_.setOutlineColor(sf::Color(0, 0, 0));
	text_.setOutlineThickness(Config::smallFontSize / 8.0f);
}

void Clock::update(float deltaTime)
{
	secondTimer_.update(deltaTime);
	if (secondTimer_.isDone())
	{
		secondTimer_.softReset();

		if (++numSeconds_ >= 60)
		{
			numSeconds_ = 0;
			if (++numMinutes_ >= 60)
			{
				++numHours_;
			}
		}

		this->updateText_();
	}
}

void Clock::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(text_);
}

void Clock::updateText_()
{
	std::string secondString = std::to_string(numSeconds_);
	if (numSeconds_ < 10)
	{
		secondString = "0" + secondString;
	}

	std::string minuteString = std::to_string(numMinutes_);
	if (numMinutes_ < 10)
	{
		minuteString = "0" + minuteString;
	}

	std::string hourString = std::to_string(numHours_);
	if (numHours_ < 10)
	{
		hourString = "0" + hourString;
	}

	text_.setString(hourString + ":" + minuteString + ":" + secondString);
}