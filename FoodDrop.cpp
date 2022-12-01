#include "FoodDrop.h"
#include "FoodData.h"
#include "EventQueue.h"
#include "Event.h"
#include "AudioData.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

FoodDrop::FoodDrop(
	float x, float y, float maxY,
	float velX, float velY,
	float accX, float accY,
	float angleDeg,
	float lifeSecs,
	uint8_t maxNumBounces,
	FoodData::Id foodId)
	:
	InteractableItem(
		x, y,
		angleDeg,
		lifeSecs,
		TextureData::getInstance().getTexture(FoodData::getInstance().getFood(foodId).getTextureId()),
		"eat",
		FoodData::getInstance().getFood(foodId).getName()),
	Oscillating(x, y, maxY),
	Falling(x, y, maxY, velX, velY, accX, accY, maxNumBounces),
	Positionable(x, y),
	state_(State::Falling),
	foodId_(foodId)
{}

void FoodDrop::interact()
{
	if (!this->isLive()) return;

	EventQueue::getInstance().send(
		new EventHealPlayer(
			FoodData::getInstance().getFood(foodId_).getHealAmount()));

	AudioData::getInstance().playSound(21);

	this->kill();
}

void FoodDrop::update(float deltaTime)
{
	switch (state_)
	{
		case State::Falling:
			Falling::update(deltaTime);
			if (Falling::isDone())
			{
				state_ = State::Oscillating;
			}
			this->updatePosition_();
			break;
		case State::Oscillating:
			InteractableItem::update(deltaTime);
			Oscillating::update(deltaTime);
			this->updatePosition_();
			break;
	}
}