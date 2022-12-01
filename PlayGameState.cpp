#include "PlayGameState.h"
#include "GameDriverState.h"
#include "PausedGameState.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

PlayGameState::PlayGameState(GameDriverState &game) :
	GameState(game)
{}

void PlayGameState::updateOnMouseMove(int mouseX, int mouseY)
{
	game_.player_.updateOnMouseMove(mouseX, mouseY);
}

void PlayGameState::updateOnMousePress(sf::Mouse::Button button)
{
	game_.player_.updateOnMousePress(button);
}

void PlayGameState::updateOnMouseRelease(sf::Mouse::Button button)
{
	game_.player_.updateOnMouseRelease(button);
}

void PlayGameState::updateOnKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Escape)
	{
		game_.changeState_(new PausedGameState(game_));
	}
	else
	{
		game_.player_.updateOnKeyPress(key);
	}
}

void PlayGameState::updateOnKeyRelease(sf::Keyboard::Key key)
{
	game_.player_.updateOnKeyRelease(key);
}

void PlayGameState::update(float deltaTime)
{
	game_.clock_.update(deltaTime);

	game_.player_.update(
		deltaTime,
		game_.camera_.getX(), game_.camera_.getY(),
		game_.bulletPool_,
		game_.dropParticlePool_,
		game_.interactableItemPool_,
		game_.interactableText_,
		game_.map_.getVisibleCollidableTiles());
	game_.zombiePool_.update(
		deltaTime,
		game_.player_,
		game_.bulletPool_,
		game_.dropParticlePool_,
		game_.map_.getVisibleCollidableTiles());
	game_.interactableItemPool_.update(deltaTime);
	game_.bulletPool_.update(deltaTime);
	game_.particlePool_.update(deltaTime);
	game_.dropParticlePool_.update(deltaTime);
	game_.map_.update(deltaTime, game_.bulletPool_, game_.dropParticlePool_);

	game_.player_.constrain(0.0f, 0.0f, game_.map_.getWidth(), game_.map_.getHeight());

	game_.level_.update(deltaTime, game_.player_.getX(), game_.player_.getY());

	game_.centerCameraOnPlayer_();
	game_.updateMapVisibility_();
}

void PlayGameState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	this->drawWorld_(target, states);
	this->drawHud_(target, states);
}

void PlayGameState::drawWorld_(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(Config::globalScale, Config::globalScale);
	states.transform.translate(-game_.camera_.getX(), -game_.camera_.getY());

	target.draw(game_.map_, states);
	target.draw(game_.particlePool_, states);
	target.draw(game_.bulletPool_, states);
	target.draw(game_.player_, states);
	target.draw(game_.zombiePool_, states);
	target.draw(game_.interactableItemPool_, states);
	target.draw(game_.dropParticlePool_, states);
}

void PlayGameState::drawHud_(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(Config::globalScale, Config::globalScale);

	target.draw(game_.healthBar_, states);
	target.draw(game_.killCounter_, states);
	target.draw(game_.clock_, states);
	target.draw(game_.interactableText_, states);
}