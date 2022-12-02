#pragma once

class GameState;

#include "DriverState.h"
#include "Listener.h"
#include "Map.h"
#include "Camera.h"
#include "Level.h"
#include "Player.h"
#include "ZombiePool.h"
#include "InteractableItemPool.h"
#include "BulletPool.h"
#include "ParticlePool.h"
#include "DropParticlePool.h"
#include "HealthBar.h"
#include "KillCounter.h"
#include "Clock.h"
#include "InteractableText.h"

class GameDriverState :
	public DriverState,
	public Listener
{
public:
	GameDriverState();
	~GameDriverState();

	void onEvent(const Event &ev) override;

	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnMousePress(sf::Mouse::Button button) override;
	void updateOnMouseRelease(sf::Mouse::Button button) override;
	void updateOnKeyPress(sf::Keyboard::Key key) override;
	void updateOnKeyRelease(sf::Keyboard::Key key) override;
	void update(float deltaTime) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	friend class PlayGameState;
	friend class PausedGameState;
	friend class DeathGameState;

	GameState *state_;

	Map map_;
	Camera camera_;
	Level level_;
	Player player_;
	ZombiePool zombiePool_;
	InteractableItemPool interactableItemPool_;
	BulletPool bulletPool_;
	ParticlePool particlePool_;
	DropParticlePool dropParticlePool_;

	HealthBar healthBar_;
	KillCounter killCounter_;
	Clock clock_;
	InteractableText interactableText_;

	void centerCameraOnPlayer_();
	void updateMapVisibility_();
	void changeState_(GameState *state);
	Weapon::WeaponId getRandomStartingWeaponId_() const;
};