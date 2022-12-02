#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>

class MainMenuTitleText : public sf::Drawable
{
public:
	MainMenuTitleText();

	void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	enum class State : uint8_t
	{
		Shrink,
		Expand
	};

	State state_;

	sf::Text zillionzText_;
	sf::Text ofText_;
	sf::Text zombiezText_;

	float scale_;
	float minScale_;
	float velScale_;
};