#include "Food.h"

Food::Food(float healAmount, TextureData::TextureId textureId, const std::string &name) :
	name_(name),
	textureId_(textureId),
	healAmount_(healAmount)
{}

TextureData::TextureId Food::getTextureId() const
{
	return textureId_;
}

const std::string &Food::getName() const
{
	return name_;
}

float Food::getHealAmount() const
{
	return healAmount_;
}