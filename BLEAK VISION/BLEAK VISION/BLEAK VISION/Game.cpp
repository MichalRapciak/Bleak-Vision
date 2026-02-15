#include "Game.h"
#include <iostream>

GameState Game::currentState = GameState::License;

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode({ 1920U, 1080U }), "BLEAK VISION" },
	m_exitGame{ false } //when true game will exit

{
	initialiseStates();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}

/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{
	sf::Clock gameClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 75.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 70 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += gameClock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 75 fps
			update(timePerFrame); //75 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	while (auto event = m_window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
				m_window.close();
		switch (currentState)
		{
		case GameState::None:
			break;
		case GameState::License:
			//no process events in license
			break;
		case GameState::Splash:
			m_splashScreen.processInput(*event);
			break;
		case GameState::MainMenu:
			//no event processing method except for update
			break;
		case GameState::Help:
			m_helpScreen.processInput(*event);
			break;
		case GameState::GamePlay:
			m_gamingScreen.processEvents(*event,m_window);
			break;
		default:
			break;
		}
	}
	
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F4))
		{
			m_exitGame = true;
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	switch (currentState)
	{
	case GameState::None:
		break;
	case GameState::License:
		m_licenseScreen.update(t_deltaTime);
		break;
	case GameState::Splash:
		m_splashScreen.update(t_deltaTime);
		break;
	case GameState::MainMenu:
		m_mainMenuScreen.update(t_deltaTime, m_window);
		break;
	case GameState::Help:
		m_helpScreen.update(t_deltaTime);
		break;
	case GameState::GamePlay:
		m_gamingScreen.update(t_deltaTime, m_window);
	default:
		break;
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	switch (currentState)
	{
	case GameState::None:
		break;
	case GameState::License:
		m_licenseScreen.render(m_window);
		break;
	case GameState::Splash:
		m_splashScreen.render(m_window);
		break;
	case GameState::MainMenu:
		m_mainMenuScreen.render(m_window);
		break;
	case GameState::Help:
		m_helpScreen.render(m_window);
		break;
	case GameState::GamePlay:
		m_gamingScreen.render(m_window);
	default:
		break;
	}
	m_window.display();
}

void Game::initialiseStates()
{
	if (!m_font.openFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_licenseScreen.initialise(m_font);
	m_splashScreen.initialise(m_font);
	m_mainMenuScreen.initialise(m_font);
	m_helpScreen.initialise(m_font);
}

