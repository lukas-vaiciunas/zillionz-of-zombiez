#pragma once

class BulletPool;
class DropParticlePool;

#include "DurationTimer.h"
#include "TextureData.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Weapon : public sf::Drawable
{
public:
	typedef uint16_t WeaponId;

	Weapon(
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
		const std::string &name);

	void update(
		float deltaTime,
		BulletPool &bulletPool,
		DropParticlePool &dropParticlePool);

	void setVelX(float velX);
	void setVelY(float velY);
	void setCenter(float cX, float cY);
	void setOffset(float offset);
	void setRawFocus(float fX, float fY);
	void setRawFocusOffset(float offsetX, float offsetY);
	void setIsFiring(bool isFiring);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	const sf::Texture &getTexture() const;
	const std::string &getName() const;
	WeaponId getId() const;
	float getWidth() const;
	float getHeight() const;
private:
	enum class Face : uint8_t
	{
		None,
		Left,
		Right
	} face_;

	sf::Sprite sprite_;

	DurationTimer cooldownTimer_;

	std::string name_;

	WeaponId id_;

	float width_;
	float height_;

	float cX_;
	float cY_;
	float velX_;
	float velY_;

	float fX_;
	float fY_;
	float focusOffsetY_;
	float focusOffsetX_;
	float offset_;

	float recoilOffset_;
	float currRecoilOffset_;
	float velRecoilOffset_;

	uint8_t numBullets_;
	float bulletSpeed_;
	float bulletDamage_;
	float bulletDurationSecs_;
	float bulletSpreadRad_;
	TextureData::TextureId bulletTextureId_;

	float angleRad_;
	float angleDeg_;

	float barrelOffset_;
	float currBarrelOffset_;
	float barrelCX_;
	float barrelCY_;
	float barrelAngleRad_;
	float barrelAngleDeg_;

	float ejectOffset_;
	float ejectCX_;
	float ejectCY_;
	TextureData::TextureId ejectTextureId_;

	bool isFiring_;

	void updatePositionAngle_();
	void updateBarrelPosition_(float angleRad);
	void updateBarrelAngle_();
	void updateEjectPosition_(float angleRad);
	void updateFace_();
	void updateFiring_(float deltaTime, BulletPool &bulletPool, DropParticlePool &dropParticlePool);
	void updateRecoilOffset_(float deltaTime);
	void fire_(BulletPool &bulletPool, DropParticlePool &dropParticlePool);
	void ejectCasing_(DropParticlePool &dropParticlePool);
};