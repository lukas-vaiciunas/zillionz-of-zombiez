#pragma once

#include "Collidable.h"
#include "HumanoidAnimation.h"

class Humanoid :
	public Collidable,
	public sf::Drawable
{
public:
	Humanoid(float x, float y, const HumanoidAnimation &animation);
	virtual ~Humanoid() {}

	void constrain(float x1, float y1, float x2, float y2) override;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
protected:
	HumanoidAnimation animation_;
};