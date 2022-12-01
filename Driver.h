#pragma once

class EventQueue;
class AudioData;

#include "DriverState.h"
#include "DriverStateType.h"
#include "Listener.h"

class Driver :
	public DriverState,
	public Listener
{
public:
	Driver();
	~Driver();

	void onEvent(const Event &ev) override;

	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnMousePress(sf::Mouse::Button button) override;
	void updateOnMouseRelease(sf::Mouse::Button button) override;
	void updateOnKeyPress(sf::Keyboard::Key key) override;
	void updateOnKeyRelease(sf::Keyboard::Key key) override;
	void update(float deltaTime) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool isDone() const;
private:
	DriverState *state_;

	EventQueue &eventQueue_;
	AudioData &audioData_;

	bool isDone_;

	void changeState_(DriverStateType stateType);
};