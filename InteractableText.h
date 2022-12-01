#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

class InteractableText : public sf::Drawable
{
public:
	InteractableText(float x, float y);

	void set(const std::string &verb, const std::string &interactableName);

	void activate();
	void deactivate();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	sf::Text text_;

	bool isActive_;
};