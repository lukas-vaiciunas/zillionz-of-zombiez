#include "Driver.h"
#include "MainMenuDriverState.h"
#include "GameDriverState.h"
#include "Event.h"
#include "EventQueue.h"
#include "AudioData.h"
#include <SFML/Graphics/RenderTarget.hpp>

Driver::Driver() :
	DriverState(),
	Listener({ EventType::ChangeDriverState, EventType::Quit }),
	state_(nullptr),
	eventQueue_(EventQueue::getInstance()),
	audioData_(AudioData::getInstance()),
	isDone_(false)
{
	this->changeState_(DriverStateType::MainMenu);
}

Driver::~Driver()
{
	this->changeState_(DriverStateType::None);
}

void Driver::onEvent(const Event &ev)
{
	if (ev.getType() == EventType::ChangeDriverState)
	{
		this->changeState_(static_cast<const EventChangeDriverState &>(ev).getDriverStateType());
	}
	else if (ev.getType() == EventType::Quit)
	{
		isDone_ = true;
	}
}

void Driver::updateOnMouseMove(int mouseX, int mouseY)
{
	state_->updateOnMouseMove(mouseX, mouseY);
}

void Driver::updateOnMousePress(sf::Mouse::Button button)
{
	state_->updateOnMousePress(button);
}

void Driver::updateOnMouseRelease(sf::Mouse::Button button)
{
	state_->updateOnMouseRelease(button);
}

void Driver::updateOnKeyPress(sf::Keyboard::Key key)
{
	state_->updateOnKeyPress(key);
}

void Driver::updateOnKeyRelease(sf::Keyboard::Key key)
{
	state_->updateOnKeyRelease(key);
}

void Driver::update(float deltaTime)
{
	eventQueue_.dispatch();
	audioData_.update();

	state_->update(deltaTime);
}

void Driver::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(*state_, states);
}

bool Driver::isDone() const
{
	return isDone_;
}

void Driver::changeState_(DriverStateType stateType)
{
	delete state_;

	switch (stateType)
	{
		case DriverStateType::MainMenu:
			state_ = new MainMenuDriverState();
			break;
		case DriverStateType::Game:
			state_ = new GameDriverState();
			break;
	}
}