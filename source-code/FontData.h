#pragma once

#include <SFML/Graphics/Font.hpp>

class FontData
{
public:
	FontData(const FontData &) = delete;
	FontData &operator=(const FontData &) = delete;

	static FontData &getInstance();

	const sf::Font &getFont() const;
private:
	sf::Font font_;

	FontData();
	~FontData() {}
};