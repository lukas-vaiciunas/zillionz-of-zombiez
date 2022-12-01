#pragma once

class CollidableTileData;

#include "PartitionPackage.h"
#include "ScenicTile.h"
#include "CollidableTile.h"
#include <SFML/Graphics/Drawable.hpp>
#include <string>

class Map : public sf::Drawable
{
public:
	Map();

	void update(float deltaTime, BulletPool &bulletPool, DropParticlePool &dropParticlePool);

	void updateVisibility(float x, float y);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	float getWidth() const;
	float getHeight() const;

	std::vector<CollidableTile *> &getVisibleCollidableTiles();
	const std::vector<CollidableTile *> &getVisibleCollidableTiles() const;
private:
	PartitionPackage<ScenicTile> scenicTilePartitionPackage_;
	PartitionPackage<CollidableTile> collidableTilePartitionPackage_;

	float width_;
	float height_;

	void init_(int32_t numCols, int32_t numRows);
	void loadStructure_(
		const std::string &filePath,
		int32_t col, int32_t row,
		const CollidableTileData &collidableTileData,
		std::vector<std::vector<TextureData::TextureId>> &scenicTileTextureIds);
};