#pragma once

#include "TextureData.h"
#include <unordered_map>

class GibData
{
public:
	typedef uint16_t GibId;
	typedef uint8_t GibAmount;
	typedef std::unordered_map<TextureData::TextureId, GibAmount> Gibs;

	GibData();

	const Gibs &getGibs(GibId id) const;
private:
	std::unordered_map<GibId, Gibs> gibMap_;

	void load_(const std::string &filePath);
};