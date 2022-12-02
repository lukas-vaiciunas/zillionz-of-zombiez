#pragma once

#include "InteractableItem.h"
#include "Oscillating.h"
#include "Falling.h"
#include "FoodData.h"

class FoodDrop :
	public InteractableItem,
	public Oscillating,
	public Falling
{
public:
	FoodDrop(
		float x, float y, float maxY,
		float velX, float velY,
		float accX, float accY,
		float angleDeg,
		float lifeSecs,
		uint8_t maxNumBounces,
		FoodData::Id foodId);

	void interact() override;

	void update(float deltaTime) override;
private:
	enum class State : uint8_t
	{
		Falling,
		Oscillating
	};

	State state_;
	FoodData::Id foodId_;
};