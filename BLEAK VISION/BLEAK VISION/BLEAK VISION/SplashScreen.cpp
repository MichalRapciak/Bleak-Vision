#include <iostream>
#include "SplashScreen.h"
#include "Game.h"

SplashScreen::SplashScreen() : m_splashText(m_font), m_splashBackground(m_splashBackgroundTexture)
{
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::initialise(sf::Font& t_font)
{
	m_font = t_font;
	if (!m_splashBackgroundTexture.loadFromFile("ASSETS/IMAGES/splashbg.png"))
	{
		std::cout << "Error loading splash screen background";
	}
	m_splashBackgroundTexture.setRepeated(true); // might not be needed if the final background is a full screen image
	m_splashBackground.setTexture(m_splashBackgroundTexture);
	m_splashBackground.setTextureRect(sf::IntRect({ 0, 0 }, { static_cast<int>(1920), static_cast<int>(1080) })); // sets it to the size of the window
	m_splashBackground.setPosition({ 0, 0 });

	m_splashText.setFont(m_font); // Text seen on the screen
	m_splashText.setString("Press space to continue");
	m_splashText.setCharacterSize(42);
	m_splashText.setFillColor(sf::Color::Red);
	m_splashText.setStyle(sf::Text::Bold);

	sf::FloatRect textSize = m_splashText.getGlobalBounds(); // will be used to put the text in the middle
	float xpos = (1920 / 2) - (textSize.size.x / 2);
	m_splashText.setPosition({ xpos, 1080 * 0.5f });

	m_anyKeyPressed = false;
}

void SplashScreen::update(sf::Time& t_deltaTime)
{
	if (m_anyKeyPressed)
	{
		Game::currentState = GameState::MainMenu;
	}
}

void SplashScreen::processInput(sf::Event& t_event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		m_anyKeyPressed = true;
	}
}

void SplashScreen::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_splashText);
}
