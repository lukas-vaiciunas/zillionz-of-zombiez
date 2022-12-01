#include "HumanoidAnimation.h"
#include <SFML/Graphics/RenderTarget.hpp>

HumanoidAnimation::HumanoidAnimation(
	uint8_t frameWidth, uint8_t frameHeight,
	float frameSecs,
	const sf::Texture &texture)
	:
	sf::Drawable(),
	sprite_(texture),
	frameTimer_(frameSecs),
	state_(State::None),
	frameWidth_(frameWidth),
	frameHeight_(frameHeight),
	frameCol_(0),
	frameColMax_(0),
	frameRow_(0)
{
	this->setState(State::Idle);
}

bool HumanoidAnimation::update(float deltaTime)
{
	frameTimer_.update(deltaTime);

	if (frameTimer_.isDone())
	{
		frameTimer_.softReset();

		this->incrementFrameCol_();
		this->updateSpriteTextureRect_();

		return frameCol_ % 2 == 1;
	}

	return false;
}

void HumanoidAnimation::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

void HumanoidAnimation::setPosition(float x, float y)
{
	sprite_.setPosition(x, y);
}

void HumanoidAnimation::setState(State state)
{
	switch (state)
	{
		case State::Idle:
			frameRow_ = 0;
			frameColMax_ = 2;
			break;
		case State::Move:
			frameRow_ = 1;
			frameColMax_ = 4;
			break;
	}

	frameCol_ %= frameColMax_;
	this->updateSpriteTextureRect_();
}

uint8_t HumanoidAnimation::getFrameWidth() const
{
	return frameWidth_;
}

uint8_t HumanoidAnimation::getFrameHeight() const
{
	return frameHeight_;
}

void HumanoidAnimation::updateSpriteTextureRect_()
{
	sprite_.setTextureRect(
		sf::IntRect(
			frameCol_ * frameWidth_,
			frameRow_ * frameHeight_,
			frameWidth_, 
			frameHeight_));
}

void HumanoidAnimation::incrementFrameCol_()
{
	frameCol_ = (frameCol_ + 1) % frameColMax_;
}