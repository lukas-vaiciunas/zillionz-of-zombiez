#pragma once

#include "CollidableTile.h"

class CollidableTileData
{
public:
	typedef uint16_t Id;

	CollidableTileData();

	const CollidableTile &getCollidableTile(Id id) const;
private:
	std::unordered_map<Id, CollidableTile> collidableTiles_;

	void load_(const std::string &filePath);
};