#pragma once

#include "DurationTimer.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class HumanoidAnimation : public sf::Drawable
{
public:
	enum class State : uint8_t
	{
		None,
		Idle,
		Move
	};

	HumanoidAnimation(
		uint8_t frameWidth, uint8_t frameHeight,
		float frameSecs,
		const sf::Texture &texture);

	bool update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void setPosition(float x, float y);
	void setState(State state);

	uint8_t getFrameWidth() const;
	uint8_t getFrameHeight() const;
private:
	sf::Sprite sprite_;

	DurationTimer frameTimer_;

	State state_;

	uint8_t frameWidth_;
	uint8_t frameHeight_;

	uint8_t frameCol_;
	uint8_t frameColMax_;
	uint8_t frameRow_;

	void updateSpriteTextureRect_();
	void incrementFrameCol_();
};