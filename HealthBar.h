#pragma once

#include "TextureData.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class HealthBar : public sf::Drawable
{
public:
	HealthBar(
		float x, float y,
		uint8_t numComponents,
		TextureData::TextureId leftEmptyTextureId,
		TextureData::TextureId middleEmptyTextureId,
		TextureData::TextureId rightEmptyTextureId,
		TextureData::TextureId leftFullTextureId,
		TextureData::TextureId middleFullTextureId,
		TextureData::TextureId rightFullTextureId);

	void update(float health, float maxHealth);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	std::vector<sf::Sprite> sprites_;
	uint8_t numComponents_;
	uint8_t numFull_;

	sf::Text hpText_;

	TextureData::TextureId leftEmptyTextureId_;
	TextureData::TextureId middleEmptyTextureId_;
	TextureData::TextureId rightEmptyTextureId_;

	TextureData::TextureId leftFullTextureId_;
	TextureData::TextureId middleFullTextureId_;
	TextureData::TextureId rightFullTextureId_;
};