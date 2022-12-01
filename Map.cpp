#include "Map.h"
#include "CollidableTileData.h"
#include "TextureData.h"
#include "RandGen.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <fstream>

Map::Map() :
	scenicTilePartitionPackage_(5, 5, 16),
	collidableTilePartitionPackage_(5, 5, 16),
	width_(5 * 16 * static_cast<float>(Constants::tileSize)),
	height_(5 * 16 * static_cast<float>(Constants::tileSize))
{
	this->init_(80, 80);
}

void Map::update(float deltaTime, BulletPool &bulletPool, DropParticlePool &dropParticlePool)
{
	for (auto it = collidableTilePartitionPackage_.getVisibleItems().begin(); it != collidableTilePartitionPackage_.getVisibleItems().end(); ++it)
	{
		(*it)->update(deltaTime, bulletPool, dropParticlePool);

		if (!(*it)->isLive())
		{
			collidableTilePartitionPackage_.getPartition().remove(*it);
		}
	}

	collidableTilePartitionPackage_.updateVisibleItems();
}

void Map::updateVisibility(float x, float y)
{
	scenicTilePartitionPackage_.updateVisibility(x, y);
	collidableTilePartitionPackage_.updateVisibility(x, y);
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (auto it = scenicTilePartitionPackage_.getVisibleItems().begin(); it != scenicTilePartitionPackage_.getVisibleItems().end(); ++it)
	{
		target.draw(**it, states);
	}

	for (auto it = collidableTilePartitionPackage_.getVisibleItems().begin(); it != collidableTilePartitionPackage_.getVisibleItems().end(); ++it)
	{
		target.draw(**it, states);
	}
}

float Map::getWidth() const
{
	return width_;
}

float Map::getHeight() const
{
	return height_;
}

std::vector<CollidableTile *> &Map::getVisibleCollidableTiles()
{
	return collidableTilePartitionPackage_.getVisibleItems();
}

const std::vector<CollidableTile *> &Map::getVisibleCollidableTiles() const
{
	return collidableTilePartitionPackage_.getVisibleItems();
}

void Map::init_(int32_t numCols, int32_t numRows)
{
	std::vector<std::vector<TextureData::TextureId>> scenicTileTextureIds(numRows, std::vector<TextureData::TextureId>(numCols, 0));

	std::mt19937 &eng = RandGen::getInstance().getEng();
	TextureData &textureData = TextureData::getInstance();
	std::uniform_int_distribution<TextureData::TextureId> textureIdDis(5001, 5003);

	GridPartition<ScenicTile> &scenicTilePartition = scenicTilePartitionPackage_.getPartition();
	GridPartition<CollidableTile> &collidableTilePartition = collidableTilePartitionPackage_.getPartition();

	CollidableTileData collidableTileData;

	for (GridPartition<Tile>::GridSize row = 0; row < numRows; ++row)
	{
		for (GridPartition<Tile>::GridSize col = 0; col < numCols; ++col)
		{
			scenicTileTextureIds[row][col] = textureIdDis(eng);
		}
	}

	collidableTilePartition.add(
		new CollidableTile(collidableTileData.getCollidableTile(6001).clone(
			5.0f * Constants::tileSize,
			5.0f * Constants::tileSize)));

	collidableTilePartition.add(
		new CollidableTile(collidableTileData.getCollidableTile(6001).clone(
			6.0f * Constants::tileSize,
			5.0f * Constants::tileSize)));

	collidableTilePartition.add(
		new CollidableTile(collidableTileData.getCollidableTile(6001).clone(
			5.0f * Constants::tileSize,
			6.0f * Constants::tileSize)));

	this->loadStructure_("data/structures/farm.txt", 31, 31, collidableTileData, scenicTileTextureIds);

	for (GridPartition<Tile>::GridSize row = 0; row < numRows; ++row)
	{
		for (GridPartition<Tile>::GridSize col = 0; col < numCols; ++col)
		{
			scenicTilePartition.add(
				new ScenicTile(
					static_cast<float>(col * Constants::tileSize),
					static_cast<float>(row * Constants::tileSize),
					textureData.getTexture(scenicTileTextureIds[row][col])));
		}
	}
}

void Map::loadStructure_(
	const std::string &filePath,
	int32_t col, int32_t row,
	const CollidableTileData &collidableTileData,
	std::vector<std::vector<TextureData::TextureId>> &scenicTileTextureIds)
{
	std::ifstream in(filePath);
	if (!in.is_open())
	{
		printf("Failed to load structure with file path \"%s\" in Map!", filePath.c_str());
		return;
	}

	const TextureData &textureData = TextureData::getInstance();
	GridPartition<CollidableTile> &collidableTilePartition = collidableTilePartitionPackage_.getPartition();

	int32_t numCols;
	int32_t numRows;
	in >> numCols >> numRows;

	for (int32_t rowIt = 0; rowIt < numRows; ++rowIt)
	{
		for (int32_t colIt = 0; colIt < numCols; ++colIt)
		{
			int32_t textureId;
			in >> textureId;

			if (textureId == 0) continue;

			collidableTilePartition.add(
				new CollidableTile(collidableTileData.getCollidableTile(textureId).clone(
					static_cast<float>((col + colIt) * Constants::tileSize),
					static_cast<float>((row + rowIt) * Constants::tileSize))));
		}
	}

	for (int32_t rowIt = 0; rowIt < numRows; ++rowIt)
	{
		for (int32_t colIt = 0; colIt < numCols; ++colIt)
		{
			int32_t textureId;
			in >> textureId;

			if (textureId == 0) continue;

			scenicTileTextureIds[row + rowIt][col + colIt] = textureId;
		}
	}

	in.close();
}