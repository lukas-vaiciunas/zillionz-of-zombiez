#include "Tile.h"
#include <SFML/Graphics/RenderTarget.hpp>

Tile::Tile(float x, float y, const sf::Texture &texture) :
	sprite_(texture)
{
	sprite_.setPosition(x, y);
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}