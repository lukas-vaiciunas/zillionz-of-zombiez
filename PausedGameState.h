#pragma once

#include "GameState.h"
#include "Button.h"
#include <SFML/Graphics/RectangleShape.hpp>

class PausedGameState : public GameState
{
public:
	PausedGameState(GameDriverState &game);

	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnMousePress(sf::Mouse::Button button) override;
	void updateOnMouseRelease(sf::Mouse::Button button) override;
	void updateOnKeyPress(sf::Keyboard::Key key) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	sf::RectangleShape overlay_;

	sf::Text titleText_;
	
	Button resumeButton_;
	Button quitButton_;

	void drawWorld_(sf::RenderTarget &target, sf::RenderStates states) const;
	void drawHud_(sf::RenderTarget &target, sf::RenderStates states) const;
	void drawInterface_(sf::RenderTarget &target, sf::RenderStates states) const;
};