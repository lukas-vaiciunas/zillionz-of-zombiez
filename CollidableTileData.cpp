#include "CollidableTileData.h"
#include <fstream>

CollidableTileData::CollidableTileData() :
	collidableTiles_()
{
	this->load_("data/collidable-tiles.txt");
}

const CollidableTile &CollidableTileData::getCollidableTile(Id id) const
{
	return collidableTiles_.find(id)->second;
}

void CollidableTileData::load_(const std::string &filePath)
{
	std::ifstream in(filePath);

	if (!in.is_open())
	{
		printf("Failed to open \"%s\" in CollidableTileData!\n", filePath.c_str());
		return;
	}

	const TextureData &textureData = TextureData::getInstance();

	int32_t numCollidableTiles;
	in >> numCollidableTiles;

	while (numCollidableTiles--)
	{
		int32_t id;
		float maxOffset;
		float health;
		int32_t hurtGibId;
		int32_t killGibId;

		in >> id >> maxOffset >> health >> hurtGibId >> killGibId;

		collidableTiles_.emplace(
			id,
			CollidableTile(0.0f, 0.0f, maxOffset, health, hurtGibId, killGibId, textureData.getTexture(id)));
	}

	in.close();
}