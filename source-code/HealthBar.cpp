#include "HealthBar.h"
#include "FontData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

HealthBar::HealthBar(
	float x, float y,
	uint8_t numComponents,
	TextureData::TextureId leftEmptyTextureId,
	TextureData::TextureId middleEmptyTextureId,
	TextureData::TextureId rightEmptyTextureId,
	TextureData::TextureId leftFullTextureId,
	TextureData::TextureId middleFullTextureId,
	TextureData::TextureId rightFullTextureId)
	:
	sf::Drawable(),
	sprites_(numComponents, sf::Sprite()),
	numComponents_(numComponents),
	numFull_(0),
	hpText_("HP", FontData::getInstance().getFont(), Config::smallFontSize),
	leftEmptyTextureId_(leftEmptyTextureId),
	middleEmptyTextureId_(middleEmptyTextureId),
	rightEmptyTextureId_(rightEmptyTextureId),
	leftFullTextureId_(leftFullTextureId),
	middleFullTextureId_(middleFullTextureId),
	rightFullTextureId_(rightFullTextureId)
{
	const TextureData &textureData = TextureData::getInstance();

	sprites_[0].setTexture(textureData.getTexture(leftEmptyTextureId_), true);
	sprites_[0].setPosition(x + hpText_.getLocalBounds().width * 1.25f / Config::globalScale, y);

	for (uint8_t i = 1; i < numComponents_ - 1; ++i)
	{
		sprites_[i].setTexture(textureData.getTexture(middleEmptyTextureId_), true);
		sprites_[i].setPosition(sprites_[i - 1].getPosition().x + sprites_[i - 1].getLocalBounds().width, y);
	}

	sprites_[numComponents_ - 1].setTexture(textureData.getTexture(rightEmptyTextureId_), true);
	sprites_[numComponents_ - 1].setPosition(sprites_[numComponents_ - 2].getPosition().x + sprites_[numComponents_ - 2].getLocalBounds().width, y);

	hpText_.setOrigin(
		hpText_.getLocalBounds().left,
		hpText_.getLocalBounds().top + hpText_.getLocalBounds().height * 0.5f);
	hpText_.setPosition(
		x * Config::globalScale,
		(y + sprites_[0].getLocalBounds().height * 0.5f) * Config::globalScale);
	hpText_.setFillColor(sf::Color(236, 236, 236));
	hpText_.setOutlineColor(sf::Color(0, 0, 0));
	hpText_.setOutlineThickness(Config::smallFontSize / 8.0f);
}

void HealthBar::update(float health, float maxHealth)
{
	uint8_t newNumFull = static_cast<uint8_t>(health / maxHealth * numComponents_);

	if (numFull_ != newNumFull)
	{
		const TextureData &textureData = TextureData::getInstance();

		if (numFull_ < newNumFull)
		{
			uint8_t numToFill = newNumFull - numFull_;

			if (numFull_ == 0)
			{
				sprites_[0].setTexture(textureData.getTexture(leftFullTextureId_));
				++numFull_;
				--numToFill;
			}

			if (newNumFull == numComponents_)
			{
				sprites_[numComponents_ - 1].setTexture(textureData.getTexture(rightFullTextureId_));
				--numToFill;
			}

			for (uint8_t i = 0; i < numToFill; ++i)
			{
				sprites_[numFull_ + i].setTexture(textureData.getTexture(middleFullTextureId_));
			}
		}
		else
		{
			uint8_t numToEmpty = numFull_ - newNumFull;

			if (numFull_ == numComponents_)
			{
				sprites_[numComponents_ - 1].setTexture(textureData.getTexture(rightEmptyTextureId_));
				--numToEmpty;
			}

			if (newNumFull == 0)
			{
				sprites_[0].setTexture(textureData.getTexture(leftEmptyTextureId_));
				--numToEmpty;
			}

			for (uint8_t i = 0; i < numToEmpty; ++i)
			{
				sprites_[newNumFull + i].setTexture(textureData.getTexture(middleEmptyTextureId_));
			}
		}

		numFull_ = newNumFull;
	}
}

void HealthBar::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(hpText_);

	for (const sf::Sprite &sprite : sprites_)
	{
		target.draw(sprite, states);
	}
}