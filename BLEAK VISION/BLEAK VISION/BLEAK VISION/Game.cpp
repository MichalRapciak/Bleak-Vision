#include "Game.h"

Game::Game() :
	m_window(sf::VideoMode({ 1920U, 1080U }), "BLEAK VISION"), // Main Window
	m_exitGame{ false } // Closing Window
{
	setupPlayer();
}

Game::~Game()
{
}

/// <summary>
/// Main Game Loop
/// Update 60 times per second
/// Double check to process updates as often as possible, and at least 60 times per second
/// Draw constantly but only update on time
/// If updates run slow then don't render frames
void Game::run()
{
	sf::Clock gameClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero; // set up game clock and time between frames
	const float fps{ 60.0f }; // 60 FPS is ideal
	sf::Time timePerFrame = sf::seconds(1.0f / fps); //how many seconds = 1fps
	while (m_window.isOpen())
	{
		processEvents(); // Process controls as often as possible
		timeSinceLastUpdate += gameClock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // Process events at least 60fps
			update(timePerFrame);
		}
		render(); // Render as often as possible
	}
}

/// <summary>
/// handle user and system events / inputs
/// get key pressed, mouse moves etc. from OS
/// do NOT do game update here
/// </summary>
void Game::processEvents()
{
	//sf::Event event();
	while (const auto event = m_window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			m_window.close();
		else if (const auto resized = event->getIf<sf::Event::Resized>()) //debugging to see if window resizing works
		{
			std::cout << "new width: " << resized->size.x << std::endl;
			std::cout << "new height: " << resized->size.y << std::endl;
		}
		else if(const auto keyPressed = event->getIf<sf::Event::KeyPressed>()) //user pressed a key
		{
			processKeys(*event);
		}
	}
}

/// <summary>
/// This function processes all keyboard presses and performs the correct action
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		m_exitGame = true;
	}
	else
	{
		m_playerController.playerMovement(t_event, true);
	}
}

/// <summary>
/// Checks if any key is pressed (used to start deceleration)
/// </summary>
/// <returns></returns>
bool Game::isAnyKeyPressed()
{
	for (int k = -1; k < sf::Keyboard::KeyCount; ++k)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)))
			return true;
	}
	return false;
}

/// <summary>
/// Updates the Game World
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	m_playerController.playerIdle(isAnyKeyPressed());
}

/// <summary>
/// Draw Frames and Switch Buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_player.getSprite());
	m_window.display();
}

/// <summary>
/// Setting player up
/// </summary>
void Game::setupPlayer()
{
	m_player.setPosition({ 500, 500 });
}