#pragma once

class InteractableItemPool;
class InteractableText;
class CollidableTile;

#include "Humanoid.h"
#include "Listener.h"
#include "Weapon.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

class Player :
	public Humanoid,
	public Listener
{
public:
	Player(
		float x, float y,
		float speed,
		float health,
		Weapon::WeaponId weaponId,
		const HumanoidAnimation &animation);

	void onEvent(const Event &ev) override;

	void updateOnMouseMove(int mouseX, int mouseY);
	void updateOnMousePress(sf::Mouse::Button button);
	void updateOnMouseRelease(sf::Mouse::Button button);
	void updateOnKeyPress(sf::Keyboard::Key key);
	void updateOnKeyRelease(sf::Keyboard::Key key);
	void update(
		float deltaTime,
		float cameraX, float cameraY,
		BulletPool &bulletPool,
		DropParticlePool &dropParticlePool,
		InteractableItemPool &interactableItemPool,
		InteractableText &interactableText,
		const std::vector<CollidableTile *> &collidableTiles);

	void hurt(float damage, DropParticlePool &dropParticlePool);
	void heal(float health);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	float getHealth() const;
	float getMaxHealth() const;

	bool isLive() const;
private:
	Weapon weapon_;

	float speed_;
	float health_;
	float maxHealth_;

	bool isMovingUp_;
	bool isMovingDown_;
	bool isMovingLeft_;
	bool isMovingRight_;
	bool isInteracting_;

	bool isLive_;

	void updatePosition_(float deltaTime, const std::vector<CollidableTile *> &collidableTiles);
	void updateCollisionsX_(const std::vector<CollidableTile *> &collidableTiles);
	void updateCollisionsY_(const std::vector<CollidableTile *> &collidableTiles);
	void updateAnimationState_(float velX, float velY);
	void updateWeaponCenter_();
	void updateInteractableCollisions_(
		InteractableItemPool &interactableItemPool,
		InteractableText &interactableText);
	void interact_(InteractableItemPool &interactableItemPool);
	void equipWeapon_(const Weapon &weapon);
	void resetMovementState_();
	void resetWeaponState_();
};