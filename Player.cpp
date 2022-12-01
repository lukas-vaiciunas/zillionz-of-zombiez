#include "Player.h"
#include "InteractableItemPool.h"
#include "InteractableText.h"
#include "CollidableTile.h"
#include "DropParticlePool.h"
#include "EventQueue.h"
#include "Event.h"
#include "TextureData.h"
#include "WeaponData.h"
#include "AudioData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

Player::Player(
	float x, float y,
	float speed,
	float health,
	Weapon::WeaponId weaponId,
	const HumanoidAnimation &animation)
	:
	Humanoid(x, y, animation),
	Positionable(x, y),
	Listener({ EventType::PickupWeapon, EventType::HealPlayer }),
	weapon_(WeaponData::getInstance().getWeapon(weaponId)),
	speed_(speed),
	health_(health),
	maxHealth_(health),
	isMovingUp_(false),
	isMovingDown_(false),
	isMovingLeft_(false),
	isMovingRight_(false),
	isLive_(true)
{
	weapon_.setOffset((width_ + height_) * 0.3f + weapon_.getWidth() * 0.5f),
	this->updateWeaponCenter_();
}

void Player::onEvent(const Event &ev)
{
	if (ev.getType() == EventType::PickupWeapon)
	{
		this->equipWeapon_(
			WeaponData::getInstance().getWeapon(
				static_cast<const EventPickupWeapon &>(ev).getWeaponId()));
	}
	else if (ev.getType() == EventType::HealPlayer)
	{
		this->heal(static_cast<const EventHealPlayer &>(ev).getHealth());
	}
}

void Player::updateOnMouseMove(int mouseX, int mouseY)
{
	float invGlobalScale = 1.0f / Config::globalScale;

	weapon_.setRawFocus(mouseX * invGlobalScale, mouseY * invGlobalScale);
}

void Player::updateOnMousePress(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left)
	{
		weapon_.setIsFiring(true);
	}
}

void Player::updateOnMouseRelease(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Button::Left)
	{
		weapon_.setIsFiring(false);
	}
}

void Player::updateOnKeyPress(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Key::W:
			isMovingUp_ = true;
			break;
		case sf::Keyboard::Key::A:
			isMovingLeft_ = true;
			break;
		case sf::Keyboard::Key::S:
			isMovingDown_ = true;
			break;
		case sf::Keyboard::Key::D:
			isMovingRight_ = true;
			break;
		case sf::Keyboard::Key::F:
			isInteracting_ = true;
			break;
	}
}

void Player::updateOnKeyRelease(sf::Keyboard::Key key)
{
	switch (key)
	{
		case sf::Keyboard::Key::W:
			isMovingUp_ = false;
			break;
		case sf::Keyboard::Key::A:
			isMovingLeft_ = false;
			break;
		case sf::Keyboard::Key::S:
			isMovingDown_ = false;
			break;
		case sf::Keyboard::Key::D:
			isMovingRight_ = false;
			break;
		case sf::Keyboard::Key::F:
			isInteracting_ = false;
			break;
	}
}

void Player::update(
	float deltaTime,
	float cameraX, float cameraY,
	BulletPool &bulletPool,
	DropParticlePool &dropParticlePool,
	InteractableItemPool &interactableItemPool,
	InteractableText &interactableText,
	const std::vector<CollidableTile *> &collidableTiles)
{
	this->updatePosition_(deltaTime, collidableTiles);
	this->updateInteractableCollisions_(interactableItemPool, interactableText);

	if(animation_.update(deltaTime)
		&& (isMovingUp_ || isMovingDown_ || isMovingLeft_ || isMovingRight_))
	{
		AudioData::getInstance().playRandomizedSound(22);
	}
	weapon_.setRawFocusOffset(cameraX, cameraY);
	weapon_.update(deltaTime, bulletPool, dropParticlePool);

	if (isInteracting_)
	{
		isInteracting_ = false;

		this->interact_(interactableItemPool);
	}
}

void Player::hurt(float damage, DropParticlePool &dropParticlePool)
{
	dropParticlePool.spawnBloodSplatter(
		x_ + width_ * 0.5f,
		y_ + height_ * 0.5f,
		y_ + height_,
		3);

	health_ -= damage;
	if (health_ <= 0.0f)
	{
		health_ = 0.0f;

		isLive_ = false;

		dropParticlePool.spawnGibs(
			x_ + width_ * 0.5f,
			y_ + height_ * 0.5f,
			y_ + height_,
			8);

		AudioData::getInstance().playRandomizedSound(41);

		EventQueue::getInstance().send(new EventPlayerWasKilled());
	}
	
	EventQueue::getInstance().send(new EventUpdateHealthBar());
}

void Player::heal(float health)
{
	health_ += health;
	if (health_ > maxHealth_)
	{
		health_ = maxHealth_;
	}

	EventQueue::getInstance().send(new EventUpdateHealthBar());
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	Humanoid::draw(target, states);
	target.draw(weapon_, states);
}

float Player::getHealth() const
{
	return health_;
}

float Player::getMaxHealth() const
{
	return maxHealth_;
}

bool Player::isLive() const
{
	return isLive_;
}

void Player::updatePosition_(float deltaTime, const std::vector<CollidableTile *> &collidableTiles)
{
	float velX = 0.0f;
	float velY = 0.0f;

	if (isMovingUp_)
	{
		velY -= speed_;
	}
	if (isMovingDown_)
	{
		velY += speed_;
	}
	if (isMovingLeft_)
	{
		velX -= speed_;
	}
	if (isMovingRight_)
	{
		velX += speed_;
	}

	float currSpeedSq = velX * velX + velY * velY;
	float maxSpeedSq = speed_ * speed_;

	if (currSpeedSq > maxSpeedSq)
	{
		float repairRatio = speed_ / sqrtf(currSpeedSq);

		velX *= repairRatio;
		velY *= repairRatio;
	}

	x_ += velX * deltaTime;
	this->updateCollisionsX_(collidableTiles);

	y_ += velY * deltaTime;
	this->updateCollisionsY_(collidableTiles);

	animation_.setPosition(x_, y_);

	weapon_.setVelX(velX);
	weapon_.setVelY(velY);
	this->updateWeaponCenter_();

	this->updateAnimationState_(velX, velY);
}

void Player::updateCollisionsX_(const std::vector<CollidableTile *> &collidableTiles)
{
	float cX = x_ + width_ * 0.5f;
	
	for (auto it = collidableTiles.begin(); it != collidableTiles.end(); ++it)
	{
		const Collidable &collidable = static_cast<const Collidable &>(**it);
		
		if (this->isCollidingWith(collidable))
		{
			float otherX1 = collidable.getX();
			float otherWidth = collidable.getWidth();
			float otherX2 = otherX1 + otherWidth;

			if (x_ < otherX2 && x_ + width_ > otherX1)
			{	
				float otherCX = otherX1 + otherWidth * 0.5f;

				if (cX < otherCX)
				{
					x_ -= x_ + width_ - otherX1;
				}
				else
				{
					x_ += otherX2 - x_;
				}
			}

			break;
		}
	}
}

void Player::updateCollisionsY_(const std::vector<CollidableTile *> &collidableTiles)
{
	float cY = y_ + height_ * 0.5f;

	for (auto it = collidableTiles.begin(); it != collidableTiles.end(); ++it)
	{
		const Collidable &collidable = static_cast<const Collidable &>(**it);

		if (this->isCollidingWith(collidable))
		{
			float otherY1 = collidable.getY();
			float otherHeight = collidable.getHeight();
			float otherY2 = otherY1 + otherHeight;

			if (y_ < otherY2 && y_ + height_ > otherY1)
			{
				float otherCY = otherY1 + otherHeight * 0.5f;

				if (cY < otherCY)
				{
					y_ -= y_ + height_ - otherY1;
				}
				else
				{
					y_ += otherY2 - y_;
				}
			}

			break;
		}
	}
}

void Player::updateAnimationState_(float velX, float velY)
{
	if (velX != 0.0f || velY != 0.0f)
	{
		animation_.setState(HumanoidAnimation::State::Move);
	}
	else
	{
		animation_.setState(HumanoidAnimation::State::Idle);
	}
}

void Player::updateWeaponCenter_()
{
	weapon_.setCenter(x_ + width_ * 0.5f, y_ + height_ * 0.5f);
}

void Player::updateInteractableCollisions_(
	InteractableItemPool &interactableItemPool,
	InteractableText &interactableText)
{
	interactableText.deactivate();

	for (auto it = interactableItemPool.begin(); it != interactableItemPool.end(); ++it)
	{
		if ((*it)->isLive() && this->isCollidingWith(**it))
		{
			interactableText.set((*it)->getInteractVerb(), (*it)->getName());
			interactableText.activate();

			break;
		}
	}
}

void Player::interact_(InteractableItemPool &interactableItemPool)
{
	for (auto it = interactableItemPool.begin(); it != interactableItemPool.end(); ++it)
	{
		if ((*it)->isLive() && this->isCollidingWith(**it))
		{
			(*it)->interact();
			return;
		}
	}
}

void Player::equipWeapon_(const Weapon &weapon)
{
	EventQueue::getInstance().send(new EventDropWeapon(
		x_ + width_ * 0.5f,
		y_ + height_ * 0.5f,
		y_ + height_, weapon_.getId()));

	weapon_ = weapon;
	weapon_.setOffset((width_ + height_) * 0.3f + weapon_.getWidth() * 0.5f);
}

void Player::resetMovementState_()
{
	isMovingUp_ = false;
	isMovingDown_ = false;
	isMovingLeft_ = false;
	isMovingRight_ = false;
}

void Player::resetWeaponState_()
{
	weapon_.setIsFiring(false);
}