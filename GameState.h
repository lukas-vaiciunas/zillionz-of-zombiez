#pragma once

class GameDriverState;

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

class GameState : public sf::Drawable
{
public:
	GameState(GameDriverState &game);
	virtual ~GameState() {}

	virtual void updateOnMouseMove(int mouseX, int mouseY) {}
	virtual void updateOnMousePress(sf::Mouse::Button button) {}
	virtual void updateOnMouseRelease(sf::Mouse::Button button) {}
	virtual void updateOnKeyPress(sf::Keyboard::Key key) {}
	virtual void updateOnKeyRelease(sf::Keyboard::Key key) {}
	virtual void update(float deltaTime) {}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override {}
protected:
	GameDriverState &game_;
};