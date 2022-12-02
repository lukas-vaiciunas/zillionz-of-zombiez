#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Tile : public sf::Drawable
{
public:
	Tile(float x, float y, const sf::Texture &texture);
	virtual ~Tile() {}

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
protected:
	sf::Sprite sprite_;
};