#include "PausedGameState.h"
#include "GameDriverState.h"
#include "PlayGameState.h"
#include "EventQueue.h"
#include "Event.h"
#include "FontData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

PausedGameState::PausedGameState(GameDriverState &game) :
	GameState(game),
	overlay_(),
	titleText_("Paused", FontData::getInstance().getFont(), Config::largeFontSize),
	resumeButton_(
		Config::windowWidth * 0.5f / Config::globalScale,
		Config::windowHeight * 0.6f / Config::globalScale,
		"Resume",
		TextureData::getInstance().getTexture(10001)),
	quitButton_(
		Config::windowWidth * 0.5f / Config::globalScale,
		Config::windowHeight * 0.8f / Config::globalScale,
		"Quit",
		TextureData::getInstance().getTexture(10001))
{
	overlay_.setPosition(0.0f, 0.0f);
	overlay_.setSize(
		sf::Vector2f(
			static_cast<float>(Config::windowWidth),
			static_cast<float>(Config::windowHeight)));
	overlay_.setFillColor(sf::Color(236, 236, 236, 125));

	titleText_.setOrigin(
		titleText_.getLocalBounds().left + titleText_.getLocalBounds().width * 0.5f,
		titleText_.getLocalBounds().top + titleText_.getLocalBounds().height * 0.5f);
	titleText_.setPosition(Config::windowWidth * 0.5f, Config::windowHeight * 0.25f);
	titleText_.setFillColor(sf::Color(236, 236, 236));
	titleText_.setOutlineColor(sf::Color(0, 0, 0));
	titleText_.setOutlineThickness(Config::largeFontSize / 8.0f);
}

void PausedGameState::updateOnMouseMove(int mouseX, int mouseY)
{
	resumeButton_.updateOnMouseMove(mouseX, mouseY);
	quitButton_.updateOnMouseMove(mouseX, mouseY);
}

void PausedGameState::updateOnMousePress(sf::Mouse::Button button)
{
	resumeButton_.updateOnMousePress(button);
	quitButton_.updateOnMousePress(button);
}

void PausedGameState::updateOnMouseRelease(sf::Mouse::Button button)
{
	resumeButton_.updateOnMouseRelease(button);
	quitButton_.updateOnMouseRelease(button);

	if (resumeButton_.isActivated())
	{
		game_.changeState_(new PlayGameState(game_));
	}
	else if (quitButton_.isActivated())
	{
		EventQueue::getInstance().send(new EventChangeDriverState(DriverStateType::MainMenu));
	}
}

void PausedGameState::updateOnKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Escape)
	{
		game_.changeState_(new PlayGameState(game_));
	}
}

void PausedGameState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	this->drawWorld_(target, states);
	this->drawHud_(target, states);
	this->drawInterface_(target, states);
}

void PausedGameState::drawWorld_(sf::RenderTarget &target, sf::RenderStates states) const
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

void PausedGameState::drawHud_(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(Config::globalScale, Config::globalScale);

	target.draw(game_.healthBar_, states);
	target.draw(game_.killCounter_, states);
	target.draw(game_.clock_, states);
	target.draw(game_.interactableText_, states);
}

void PausedGameState::drawInterface_(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(Config::globalScale, Config::globalScale);
	target.draw(overlay_);
	target.draw(titleText_);
	target.draw(resumeButton_, states);
	target.draw(quitButton_, states);
}