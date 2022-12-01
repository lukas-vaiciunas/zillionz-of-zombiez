#pragma once

#include "TextureData.h"

class Food
{
public:
	Food(float healAmount, TextureData::TextureId textureId, const std::string &name);

	const std::string &getName() const;
	TextureData::TextureId getTextureId() const;
	float getHealAmount() const;
private:
	std::string name_;
	TextureData::TextureId textureId_;
	float healAmount_;
};