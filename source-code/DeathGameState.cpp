#include "DeathGameState.h"
#include "GameDriverState.h"
#include "EventQueue.h"
#include "Event.h"
#include "FontData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

DeathGameState::DeathGameState(GameDriverState &game) :
	GameState(game),
	deathText_("You're Zombie Food!", FontData::getInstance().getFont(), Config::smallFontSize),
	mainMenuText_("[ESC] Main Menu", FontData::getInstance().getFont(), Config::smallFontSize),
	textAlpha_(0.0f),
	velTextAlpha_(0.5f)
{
	deathText_.setOrigin(
		deathText_.getLocalBounds().left + deathText_.getLocalBounds().width * 0.5f,
		deathText_.getLocalBounds().top + deathText_.getLocalBounds().height * 0.5f);
	deathText_.setPosition(Config::windowWidth * 0.5f, Config::windowHeight * 0.25f);
	deathText_.setFillColor(sf::Color(208, 112, 112, static_cast<sf::Uint8>(255 * textAlpha_)));
	deathText_.setOutlineColor(sf::Color(0, 0, 0));
	deathText_.setOutlineThickness(Config::smallFontSize / 8.0f);

	mainMenuText_.setOrigin(
		mainMenuText_.getLocalBounds().left + mainMenuText_.getLocalBounds().width * 0.5f,
		mainMenuText_.getLocalBounds().top + mainMenuText_.getLocalBounds().height * 0.5f);
	mainMenuText_.setPosition(Config::windowWidth * 0.5f, Config::windowHeight * 0.75f);
	mainMenuText_.setFillColor(sf::Color(236, 236, 236, static_cast<sf::Uint8>(255 * textAlpha_)));
	mainMenuText_.setOutlineColor(sf::Color(0, 0, 0));
	mainMenuText_.setOutlineThickness(Config::smallFontSize / 8.0f);
}

void DeathGameState::updateOnKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Escape)
	{
		EventQueue::getInstance().send(
			new EventChangeDriverState(
				DriverStateType::MainMenu));
	}
}

void DeathGameState::update(float deltaTime)
{
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

	this->updateTextFade_(deltaTime);
}

void DeathGameState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	this->drawWorld_(target, states);
	this->drawHud_(target, states);

	target.draw(deathText_);
	target.draw(mainMenuText_);
}

void DeathGameState::updateTextFade_(float deltaTime)
{
	if (textAlpha_ >= 1.0f)
		return;

	textAlpha_ += velTextAlpha_ * deltaTime;
	if (textAlpha_ >= 1.0f)
	{
		textAlpha_ = 1.0f;
	}

	sf::Uint8 alpha = static_cast<sf::Uint8>(255 * textAlpha_);

	deathText_.setFillColor(
		sf::Color(
			deathText_.getFillColor().r,
			deathText_.getFillColor().g,
			deathText_.getFillColor().b,
			alpha));

	deathText_.setOutlineColor(
		sf::Color(
			deathText_.getOutlineColor().r,
			deathText_.getOutlineColor().g,
			deathText_.getOutlineColor().b,
			alpha));

	mainMenuText_.setFillColor(
		sf::Color(
			mainMenuText_.getFillColor().r,
			mainMenuText_.getFillColor().g,
			mainMenuText_.getFillColor().b,
			alpha));

	mainMenuText_.setOutlineColor(
		sf::Color(
			mainMenuText_.getOutlineColor().r,
			mainMenuText_.getOutlineColor().g,
			mainMenuText_.getOutlineColor().b,
			alpha));
}

void DeathGameState::drawWorld_(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(Config::globalScale, Config::globalScale);
	states.transform.translate(-game_.camera_.getX(), -game_.camera_.getY());

	target.draw(game_.map_, states);
	target.draw(game_.particlePool_, states);
	target.draw(game_.bulletPool_, states);
	target.draw(game_.zombiePool_, states);
	target.draw(game_.interactableItemPool_, states);
	target.draw(game_.dropParticlePool_, states);
}

void DeathGameState::drawHud_(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(Config::globalScale, Config::globalScale);

	target.draw(game_.healthBar_, states);
	target.draw(game_.killCounter_, states);
	target.draw(game_.clock_, states);
}