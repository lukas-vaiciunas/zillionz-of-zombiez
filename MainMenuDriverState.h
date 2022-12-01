#pragma once

#include "DriverState.h"
#include "MainMenuTitleText.h"
#include "Button.h"

class MainMenuDriverState : public DriverState
{
public:
	MainMenuDriverState();
	~MainMenuDriverState();

	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnMousePress(sf::Mouse::Button button) override;
	void updateOnMouseRelease(sf::Mouse::Button button) override;
	void update(float deltaTime) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	std::vector<sf::Sprite> backdropSprites_;

	MainMenuTitleText titleText_;

	sf::Text devText_;

	Button playButton_;
	Button quitButton_;

	void buildBackdrop_();
};