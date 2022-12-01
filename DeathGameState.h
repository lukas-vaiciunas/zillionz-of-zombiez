#pragma once

#include "GameState.h"
#include <SFML/Graphics/Text.hpp>

class DeathGameState : public GameState
{
public:
	DeathGameState(GameDriverState &game);

	void updateOnKeyPress(sf::Keyboard::Key key) override;
	void update(float deltaTime) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	sf::Text deathText_;
	sf::Text mainMenuText_;

	float textAlpha_;
	float velTextAlpha_;

	void updateTextFade_(float deltaTime);
	void drawWorld_(sf::RenderTarget &target, sf::RenderStates states) const;
	void drawHud_(sf::RenderTarget &target, sf::RenderStates states) const;
};