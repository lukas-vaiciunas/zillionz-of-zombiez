#include "MainMenuDriverState.h"
#include "Event.h"
#include "EventQueue.h"
#include "TextureData.h"
#include "RandGen.h"
#include "AudioData.h"
#include "FontData.h"
#include "Config.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

MainMenuDriverState::MainMenuDriverState() :
	DriverState(),
	backdropSprites_(),
	titleText_(),
	devText_("Created by Lukas Vaiciunas", FontData::getInstance().getFont(), Config::smallFontSize),
	playButton_(
		Config::windowWidth * 0.5f / Config::globalScale,
		Config::windowHeight * 0.6f / Config::globalScale,
		"Play",
		TextureData::getInstance().getTexture(10001)),
	quitButton_(
		Config::windowWidth * 0.5f / Config::globalScale,
		Config::windowHeight * 0.8f / Config::globalScale,
		"Quit",
		TextureData::getInstance().getTexture(10001))
{
	devText_.setOrigin(
		devText_.getLocalBounds().left + devText_.getLocalBounds().width * 0.5f,
		devText_.getLocalBounds().top + devText_.getLocalBounds().height * 0.5f);
	devText_.setPosition(Config::windowWidth * 0.5f, Config::windowHeight - devText_.getLocalBounds().height);
	devText_.setFillColor(sf::Color(236, 236, 236));
	devText_.setOutlineColor(sf::Color(0, 0, 0));
	devText_.setOutlineThickness(Config::smallFontSize / 8.0f);

	this->buildBackdrop_();

	AudioData::getInstance().playMusic(2);
}

MainMenuDriverState::~MainMenuDriverState()
{
	AudioData::getInstance().stopMusic();
}

void MainMenuDriverState::updateOnMouseMove(int mouseX, int mouseY)
{
	playButton_.updateOnMouseMove(mouseX, mouseY);
	quitButton_.updateOnMouseMove(mouseX, mouseY);
}

void MainMenuDriverState::updateOnMousePress(sf::Mouse::Button button)
{
	playButton_.updateOnMousePress(button);
	quitButton_.updateOnMousePress(button);
}

void MainMenuDriverState::updateOnMouseRelease(sf::Mouse::Button button)
{
	playButton_.updateOnMouseRelease(button);
	quitButton_.updateOnMouseRelease(button);

	if (playButton_.isActivated())
	{
		EventQueue::getInstance().send(new EventChangeDriverState(DriverStateType::Game));
	}
	else if (quitButton_.isActivated())
	{
		EventQueue::getInstance().send(new EventQuit());
	}
}

void MainMenuDriverState::update(float deltaTime)
{
	titleText_.update(deltaTime);
}

void MainMenuDriverState::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(Config::globalScale, Config::globalScale);

	for (const sf::Sprite &sprite : backdropSprites_)
	{
		target.draw(sprite, states);
	}

	target.draw(titleText_);

	target.draw(devText_);

	target.draw(playButton_, states);
	target.draw(quitButton_, states);
}

void MainMenuDriverState::buildBackdrop_()
{
	const TextureData &textureData = TextureData::getInstance();
	std::mt19937 &eng = RandGen::getInstance().getEng();
	std::uniform_int_distribution<TextureData::TextureId> textureIdDis(5001, 5003);

	float invTileSize = 1.0f / (Constants::tileSize * Config::globalScale);

	int16_t numCols = static_cast<uint16_t>(std::ceil(Config::windowWidth * invTileSize));
	int16_t numRows = static_cast<uint16_t>(std::ceil(Config::windowHeight * invTileSize));

	for (uint16_t row = 0; row < numRows; ++row)
	{
		for (uint16_t col = 0; col < numCols; ++col)
		{
			sf::Sprite sprite(textureData.getTexture(textureIdDis(eng)));
			sprite.setPosition(
				static_cast<float>(col * Constants::tileSize),
				static_cast<float>(row * Constants::tileSize));

			backdropSprites_.push_back(std::move(sprite));
		}
	}
}