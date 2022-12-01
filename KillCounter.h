#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class KillCounter : public sf::Drawable
{
public:
	KillCounter(float x, float y);

	void increment();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	sf::Sprite skullSprite_;
	sf::Text numKillsText_;

	uint64_t numKills_;
};