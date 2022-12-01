#include "FontData.h"

FontData::FontData() :
	font_()
{
	font_.loadFromFile("font/chary___.ttf");
}

FontData &FontData::getInstance()
{
	static FontData instance;
	return instance;
}

const sf::Font &FontData::getFont() const
{
	return font_;
}