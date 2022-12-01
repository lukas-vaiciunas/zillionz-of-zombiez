#include "Driver.h"
#include "Config.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

void setupConfig();

int main(void)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	const sf::Color windowClearColor(255, 0, 255);

	setupConfig();

	sf::RenderWindow window(
		sf::VideoMode(Config::windowWidth, Config::windowHeight, Config::windowBitsPerPixel),
		"Zillionz of Zombiez",
		sf::Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::Clock deltaClock;
	float deltaTime = deltaClock.restart().asSeconds();

	Driver driver;

	while (window.isOpen() && !driver.isDone())
	{
		sf::Event ev;

		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::MouseMoved)
			{
				driver.updateOnMouseMove(ev.mouseMove.x, ev.mouseMove.y);
			}
			else if (ev.type == sf::Event::MouseButtonPressed)
			{
				driver.updateOnMousePress(ev.mouseButton.button);
			}
			else if (ev.type == sf::Event::MouseButtonReleased)
			{
				driver.updateOnMouseRelease(ev.mouseButton.button);
			}
			else if (ev.type == sf::Event::KeyPressed)
			{
				driver.updateOnKeyPress(ev.key.code);
			}
			else if (ev.type == sf::Event::KeyReleased)
			{
				driver.updateOnKeyRelease(ev.key.code);
			}
			else if (ev.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		deltaTime = deltaClock.restart().asSeconds();

		driver.update(deltaTime);

		window.clear(windowClearColor);
		window.draw(driver);
		window.display();
	}

	return 0;
}

void setupConfig()
{
	sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

	Config::windowWidth = videoMode.width;
	Config::windowHeight = videoMode.height;
	Config::windowBitsPerPixel = videoMode.bitsPerPixel;

	Config::globalScale = (Config::windowWidth + Config::windowHeight) * 0.0025f;

	Config::smallFontSize = static_cast<unsigned int>((Config::windowWidth + Config::windowHeight) * 0.024f);
	Config::mediumFontSize = static_cast<unsigned int>((Config::windowWidth + Config::windowHeight) * 0.032f);
	Config::largeFontSize = static_cast<unsigned int>((Config::windowWidth + Config::windowHeight) * 0.048f);
}