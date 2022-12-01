#include "GameDriverState.h"
#include "PlayGameState.h"
#include "DeathGameState.h"
#include "Event.h"
#include "TextureData.h"
#include "AudioData.h"
#include "RandGen.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

GameDriverState::GameDriverState() :
	DriverState(),
	Listener({ EventType::UpdateHealthBar, EventType::PlayerWasKilled, EventType::EnemyWasKilled }),
	state_(new PlayGameState(*this)),
	map_(),
	camera_(0.0f, 0.0f),
	level_(zombiePool_, std::max(camera_.getViewWidth(), camera_.getViewHeight()) * 1.25f, 1.0f),
	player_(
		map_.getWidth() * 0.5f,
		map_.getHeight() * 0.5f,
		64.0f,
		100.0f,
		this->getRandomStartingWeaponId_(),
		HumanoidAnimation(8, 8, 0.15f, TextureData::getInstance().getTexture(1))),
	zombiePool_(250),
	interactableItemPool_(50),
	bulletPool_(250),
	particlePool_(500),
	dropParticlePool_(250, particlePool_),
	healthBar_(1.0f, 1.0f, 8, 11001, 11002, 11003, 11011, 11012, 11013),
	killCounter_(1.0f, 16.0f),
	clock_(Config::windowWidth * 0.5f, Config::windowHeight * 0.05f),
	interactableText_(Config::windowWidth * 0.5f, Config::windowHeight * 0.9f)
{
	healthBar_.update(player_.getHealth(), player_.getMaxHealth());
	this->centerCameraOnPlayer_();
	this->updateMapVisibility_();

	interactableItemPool_.spawnWeaponDrop(
		map_.getWidth() * 0.5f - Constants::tileSize,
		map_.getHeight() * 0.5f - Constants::tileSize,
		this->getRandomStartingWeaponId_());

	AudioData::getInstance().playMusic(1);
}

GameDriverState::~GameDriverState()
{
	AudioData::getInstance().stopMusic();

	delete state_;
}

void GameDriverState::onEvent(const Event &ev)
{
	if (ev.getType() == EventType::UpdateHealthBar)
	{
		healthBar_.update(player_.getHealth(), player_.getMaxHealth());
	}
	else if (ev.getType() == EventType::PlayerWasKilled)
	{
		this->changeState_(new DeathGameState(*this));
	}
	else if (ev.getType() == EventType::EnemyWasKilled)
	{
		killCounter_.increment();
	}
}

void GameDriverState::updateOnMouseMove(int mouseX, int mouseY)
{
	state_->updateOnMouseMove(mouseX, mouseY);
}

void GameDriverState::updateOnMousePress(sf::Mouse::Button button)
{
	state_->updateOnMousePress(button);
}

void GameDriverState::updateOnMouseRelease(sf::Mouse::Button button)
{
	state_->updateOnMouseRelease(button);
}

void GameDriverState::updateOnKeyPress(sf::Keyboard::Key key)
{
	state_->updateOnKeyPress(key);
}

void GameDriverState::updateOnKeyRelease(sf::Keyboard::Key key)
{
	state_->updateOnKeyRelease(key);
}

void GameDriverState::update(float deltaTime)
{
	state_->update(deltaTime);
}

void GameDriverState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	state_->draw(target, states);
}

void GameDriverState::centerCameraOnPlayer_()
{
	camera_.centerFocus(
		player_.getX() + player_.getWidth() * 0.5f,
		player_.getY() + player_.getHeight() * 0.5f);

	camera_.constrain(0.0f, 0.0f, map_.getWidth(), map_.getHeight());
}

void GameDriverState::updateMapVisibility_()
{
	map_.updateVisibility(camera_.getCenterX(), camera_.getCenterY());
}

void GameDriverState::changeState_(GameState *state)
{
	delete state_;

	state_ = state;
}

Weapon::WeaponId GameDriverState::getRandomStartingWeaponId_() const
{
	std::vector<Weapon::WeaponId> possibleWeaponIds = {
		1001,
		1002,
		1004,
		1301,
		1302,
		1401
	};

	return possibleWeaponIds[std::uniform_int_distribution<size_t>(0, possibleWeaponIds.size() - 1)(RandGen::getInstance().getEng())];
}