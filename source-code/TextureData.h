#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

class TextureData
{
public:
	typedef uint16_t TextureId;

	TextureData(const TextureData &) = delete;
	TextureData &operator=(const TextureData &) = delete;

	static TextureData &getInstance();

	const sf::Texture &getTexture(TextureId id) const;
private:
	std::unordered_map<TextureId, sf::Texture> textures_;

	TextureData();
	~TextureData() {}

	void load_(const std::string &filePath);
};