#pragma once

#include "Interactable.h"
#include "Collidable.h"
#include "Living.h"
#include <SFML/Graphics/Sprite.hpp>

class InteractableItem :
	public Interactable,
	public Collidable,
	public Living,
	public sf::Drawable
{
public:
	InteractableItem(
		float x, float y,
		float angleDeg,
		float lifeSecs,
		const sf::Texture &texture,
		const std::string &interactVerb,
		const std::string &name);

	virtual ~InteractableItem() {}

	virtual void interact() override = 0;

	virtual void update(float deltaTime);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
protected:
	sf::Sprite sprite_;
	float angleDeg_;

	void updatePosition_();
};