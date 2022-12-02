#pragma once

#include "Collidable.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>

class Button :
	public Collidable,
	public sf::Drawable
{
public:
	Button(
		float cX, float cY,
		const std::string &text,
		const sf::Texture &texture);

	void updateOnMouseMove(int mouseX, int mouseY);
	void updateOnMousePress(sf::Mouse::Button button);
	void updateOnMouseRelease(sf::Mouse::Button button);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool isActivated() const;
private:
	sf::Sprite sprite_;
	sf::Text text_;

	bool isHovered_;
	bool isPressed_;
	bool isActivated_;
};