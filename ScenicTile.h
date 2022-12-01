#pragma once

#include "Tile.h"
#include "Positionable.h"

class ScenicTile :
	public Tile,
	public Positionable
{
public:
	ScenicTile(float x, float y, const sf::Texture &texture);
};