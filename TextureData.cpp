#include "TextureData.h"
#include <fstream>

TextureData::TextureData() :
	textures_()
{
	this->load_("data/textures.txt");
}

TextureData &TextureData::getInstance()
{
	static TextureData instance;
	return instance;
}

const sf::Texture &TextureData::getTexture(TextureId id) const
{
	return textures_.find(id)->second;
}

void TextureData::load_(const std::string &filePath)
{
	std::ifstream in(filePath);

	if (!in.is_open())
	{
		printf("Failed to open \"%s\" in TextureData!\n", filePath.c_str());
		return;
	}

	int numTextures;
	in >> numTextures;

	while (numTextures--)
	{
		int textureId;
		std::string texturePath;

		in >> textureId >> texturePath;

		sf::Texture texture;
		texture.loadFromFile(texturePath);

		textures_.emplace(textureId, std::move(texture));
	}

	in.close();
}