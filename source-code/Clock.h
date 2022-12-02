#pragma once

#include "DurationTimer.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>

class Clock : public sf::Drawable
{
public:
	Clock(float x, float y);

	void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	sf::Text text_;

	DurationTimer secondTimer_;

	uint8_t numSeconds_;
	uint8_t numMinutes_;
	uint8_t numHours_;

	void updateText_();
};