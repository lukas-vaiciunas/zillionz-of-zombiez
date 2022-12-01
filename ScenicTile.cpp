#include "ScenicTile.h"

ScenicTile::ScenicTile(float x, float y, const sf::Texture &texture) :
	Tile(x, y, texture),
	Positionable(x, y)
{}