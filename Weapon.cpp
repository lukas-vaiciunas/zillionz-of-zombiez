#include "Weapon.h"
#include "BulletPool.h"
#include "DropParticlePool.h"
#include "RandGen.h"
#include "AudioData.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

Weapon::Weapon(
	WeaponId id,
	float cX, float cY,
	float offset,
	float barrelOffset,
	uint8_t numBullets,
	float bulletSpeed,
	float bulletDamage,
	float bulletDurationSecs,
	float bulletSpreadRad,
	float cooldownSecs,
	TextureData::TextureId bulletTextureId,
	TextureData::TextureId ejectTextureId,
	const sf::Texture &texture,
	const std::string &name)
	:
	sf::Drawable(),
	face_(Face::None),
	sprite_(texture),
	cooldownTimer_(cooldownSecs),
	name_(name),
	id_(id),
	width_(static_cast<float>(texture.getSize().x)),
	height_(static_cast<float>(texture.getSize().y)),
	cX_(cX),
	cY_(cY),
	velX_(0.0f),
	velY_(0.0f),
	fX_(0.0f),
	fY_(0.0f),
	focusOffsetX_(0.0f),
	focusOffsetY_(0.0f),
	offset_(offset),
	recoilOffset_((width_ + height_) * 0.5f / 8.0f),
	currRecoilOffset_(0.0f),
	velRecoilOffset_(recoilOffset_ / cooldownSecs),
	numBullets_(numBullets),
	bulletSpeed_(bulletSpeed),
	bulletDamage_(bulletDamage),
	bulletDurationSecs_(bulletDurationSecs),
	bulletSpreadRad_(bulletSpreadRad),
	bulletTextureId_(bulletTextureId),
	angleRad_(0.0f),
	angleDeg_(0.0f),
	barrelOffset_(-height_ * 0.5f + barrelOffset),
	currBarrelOffset_(0.0f),
	barrelCX_(0.0f),
	barrelCY_(0.0f),
	barrelAngleRad_(0.0f),
	barrelAngleDeg_(0.0f),
	ejectOffset_(-width_ * 0.1f),
	ejectCX_(0.0f),
	ejectCY_(0.0f),
	ejectTextureId_(ejectTextureId),
	isFiring_(false)
{
	sprite_.setOrigin(
		width_ * 0.5f,
		height_ * 0.5f);

	cooldownTimer_.rig();
}

void Weapon::update(
	float deltaTime,
	BulletPool &bulletPool,
	DropParticlePool &dropParticlePool)
{
	this->updatePositionAngle_();
	this->updateFace_();
	this->updateBarrelPosition_(angleRad_);
	this->updateBarrelAngle_();
	this->updateEjectPosition_(angleRad_);
	this->updateRecoilOffset_(deltaTime);
	this->updateFiring_(deltaTime, bulletPool, dropParticlePool);

	float totalOffset = offset_ - currRecoilOffset_;
	sprite_.setPosition(
		cX_ + totalOffset * cosf(angleRad_),
		cY_ + totalOffset * sinf(angleRad_));
}

void Weapon::setVelX(float velX)
{
	velX_ = velX;
}

void Weapon::setVelY(float velY)
{
	velY_ = velY;
}

void Weapon::setCenter(float cX, float cY)
{
	cX_ = cX;
	cY_ = cY;
}

void Weapon::setOffset(float offset)
{
	offset_ = offset;
}

void Weapon::setRawFocus(float fX, float fY)
{
	fX_ = fX;
	fY_ = fY;
}

void Weapon::setRawFocusOffset(float offsetX, float offsetY)
{
	focusOffsetX_ = offsetX;
	focusOffsetY_ = offsetY;
}

void Weapon::setIsFiring(bool isFiring)
{
	isFiring_ = isFiring;
}

void Weapon::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	const sf::Vector2f &spritePos = sprite_.getPosition();

	states.transform.rotate(barrelAngleDeg_, spritePos.x, spritePos.y);

	target.draw(sprite_, states);
}

const sf::Texture &Weapon::getTexture() const
{
	return *sprite_.getTexture();
}

const std::string &Weapon::getName() const
{
	return name_;
}

Weapon::WeaponId Weapon::getId() const
{
	return id_;
}

float Weapon::getWidth() const
{
	return width_;
}

float Weapon::getHeight() const
{
	return height_;
}

void Weapon::updatePositionAngle_()
{
	float dX = (fX_ + focusOffsetX_) - cX_;
	float dY = (fY_ + focusOffsetY_) - cY_;

	angleRad_ = atan2f(dY, dX);
	angleDeg_ = angleRad_ * 180.0f / Constants::pi;
}

void Weapon::updateBarrelPosition_(float angleRad)
{
	float cos = cosf(angleRad);
	float sin = sinf(angleRad);

	float barrelOffsetX = sprite_.getLocalBounds().width * 0.5f - 0.5f;
	float barrelOffsetY = currBarrelOffset_;

	barrelCX_ = sprite_.getPosition().x + barrelOffsetX * cos - barrelOffsetY * sin;
	barrelCY_ = sprite_.getPosition().y + barrelOffsetX * sin + barrelOffsetY * cos;
}

void Weapon::updateBarrelAngle_()
{
	float dX = (fX_ + focusOffsetX_) - barrelCX_;
	float dY = (fY_ + focusOffsetY_) - barrelCY_;

	barrelAngleRad_ = atan2f(dY, dX);

	float dRad = barrelAngleRad_ - angleRad_;

	float angleDiffRad = atan2f(sinf(dRad), cosf(dRad));
	float threshold = Constants::pi / 8.0f;

	if (angleDiffRad > threshold)
	{
		barrelAngleRad_ = angleRad_ + threshold;
	}
	else if (angleDiffRad < -threshold)
	{
		barrelAngleRad_ = angleRad_ - threshold;
	}

	barrelAngleDeg_ = barrelAngleRad_ * 180.0f / Constants::pi;

	this->updateBarrelPosition_(barrelAngleRad_);
}

void Weapon::updateEjectPosition_(float angleRad)
{
	float cos = cosf(angleRad);
	float sin = sinf(angleRad);

	float ejectOffsetX = ejectOffset_;
	float ejectOffsetY = currBarrelOffset_;

	ejectCX_ = sprite_.getPosition().x + ejectOffsetX * cos - ejectOffsetY * sin;
	ejectCY_ = sprite_.getPosition().y + ejectOffsetX * sin + ejectOffsetY * cos;
}

void Weapon::updateFace_()
{
	switch (face_)
	{
		case Face::None:
			if (angleDeg_ >= -90.0f && angleDeg_ < 90.0f)
			{
				currBarrelOffset_ = barrelOffset_;
				sprite_.setScale(1.0f, 1.0f);
				face_ = Face::Right;
			}
			else if (angleDeg_ < -90.0f || angleDeg_ >= 90.0f)
			{
				currBarrelOffset_ = -barrelOffset_;
				sprite_.setScale(1.0f, -1.0f);
				face_ = Face::Left;
			}
		case Face::Left:
			if (angleDeg_ >= -90.0f && angleDeg_ < 90.0f)
			{
				currBarrelOffset_ = barrelOffset_;
				sprite_.setScale(1.0f, 1.0f);
				face_ = Face::Right;
			}
			break;
		case Face::Right:
			if (angleDeg_ < -90.0f || angleDeg_ >= 90.0f)
			{
				currBarrelOffset_ = -barrelOffset_;
				sprite_.setScale(1.0f, -1.0f);
				face_ = Face::Left;
			}
			break;
	}
}

void Weapon::updateFiring_(float deltaTime, BulletPool &bulletPool, DropParticlePool &dropParticlePool)
{
	cooldownTimer_.update(deltaTime);

	if (!isFiring_ || !cooldownTimer_.isDone()) return;

	cooldownTimer_.softReset();
	this->fire_(bulletPool, dropParticlePool);
}

void Weapon::updateRecoilOffset_(float deltaTime)
{
	if (currRecoilOffset_ <= 0.0f) return;

	currRecoilOffset_ -= velRecoilOffset_ * deltaTime;

	if (currRecoilOffset_ < 0.0f) currRecoilOffset_ = 0.0f;
}

void Weapon::fire_(BulletPool &bulletPool, DropParticlePool &dropParticlePool)
{
	std::mt19937 &eng = RandGen::getInstance().getEng();
	std::uniform_real_distribution<float> bulletSpreadDis(-bulletSpreadRad_ * 0.5f, bulletSpreadRad_ * 0.5f);

	for (uint8_t i = 0; i < numBullets_; ++i)
	{
		if (bulletPool.isFull()) break;

		float bulletAngleRad = barrelAngleRad_ + bulletSpreadDis(eng);
		float bulletAngleDeg = bulletAngleRad * 180.0f / Constants::pi;

		bulletPool.add(
			new Bullet(
				barrelCX_,
				barrelCY_,
				velX_ + bulletSpeed_ * cosf(bulletAngleRad), velY_ + bulletSpeed_ * sinf(bulletAngleRad),
				bulletAngleDeg,
				bulletDamage_,
				bulletDurationSecs_,
				TextureData::getInstance().getTexture(bulletTextureId_)));

		AudioData::getInstance().playRandomizedSound(11);
	}

	currRecoilOffset_ = recoilOffset_;

	this->ejectCasing_(dropParticlePool);
}

void Weapon::ejectCasing_(DropParticlePool &dropParticlePool)
{
	if (dropParticlePool.isFull()) return;

	std::mt19937 &eng = RandGen::getInstance().getEng();
	float velX = std::uniform_real_distribution<float>(-4.0f, 4.0f)(eng);
	float velY = std::uniform_real_distribution<float>(-32.0f, -24.0f)(eng);

	dropParticlePool.add(
		new DropParticle(
			ejectCX_,
			ejectCY_,
			ejectCY_ + height_,
			velX, velY,
			0.0f, 96.0f,
			0.0f,
			velX * 45.0f,
			2.0f,
			2,
			TextureData::getInstance().getTexture(ejectTextureId_)));
}