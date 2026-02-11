#include "Game.h"

Game::Game() :
	m_window(sf::VideoMode({ 1920U, 1080U }), "BLEAK VISION"), // Main Window
	m_exitGame{ false } // Closing Window
{
	setupPlayer();
	m_playerCam.setCenter(m_player->getPosition());
	m_playerCam.zoom(1.5f);
	m_playerCam.setSize({ 1920,1080 });
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
	const float fps{ 75.0f }; // 75 FPS is ideal
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
			sf::Vector2f visibleArea(sf::Vector2f(resized->size));
			m_playerCam.setSize(visibleArea);
		}
		if(const auto keyPressed = event->getIf<sf::Event::KeyPressed>()) //user pressed a key
		{
			processKeys(*event);
			m_playerController->inputHandler(*event);
		}
		if(const auto keyReleased = event->getIf<sf::Event::KeyReleased>())
		{
			m_playerController->inputHandler(*event);
		}
		if (const auto buttonPressed = event->getIf<sf::Event::MouseButtonPressed>())
		{
			m_playerController->inputHandler(*event);
		}
		if (const auto buttonReleased = event->getIf<sf::Event::MouseButtonReleased>())
		{
			m_playerController->inputHandler(*event);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
	{
		auto newEnemy = std::make_unique<Enemy>();
		m_enemies.push_back(std::move(newEnemy));
		refreshEntities();
	}
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
	m_enemyController->aimAtPlayer(m_player->getPosition());
	m_enemyController->movementAI();
	mouseWorld = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)); // This gets mouse position in the world, depending on camera/view
	m_playerController->update(t_deltaTime.asSeconds(),*this);
	m_playerController->mouseAiming(mouseWorld);
	m_player->update(t_deltaTime.asSeconds());
	for (auto& enemy : m_enemies)
	{
		enemy->update(t_deltaTime.asSeconds());
	}
	for (auto& projectile : m_projectiles)
	{
		projectile->update(t_deltaTime.asSeconds());
	}
	refreshEntities();
	Collisions::getInstance().update(m_entities);
	m_window.setView(m_playerCam); // Set Camera to player camera
	m_playerCam.setCenter({ (m_player->getPosition().x),(m_player->getPosition().y) }); // Center player camera to the player
}

/// <summary>
/// Draw Frames and Switch Buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_level1.getLevelBG());
	m_window.draw(m_player->getSprite());
	m_window.draw(m_player->getWeaponSprite());
	for (auto& enemy : m_enemies)
	{
		m_window.draw(enemy->getSprite());
	}
	for (auto& projectile : m_projectiles)
	{
		m_window.draw(projectile->getSprite());
	}
	/*
	if (m_player->getWeapon()) {  // check pointer
		m_window.draw(m_player->getWeapon()->getDebugBox());
	}
	*/
	m_window.display();
}

/// <summary>
/// Setting player up, temporarily setting up enemies
/// </summary>
void Game::setupPlayer()
{
	m_player = std::make_unique<Player>();
	m_entities.push_back(m_player.get());
	m_playerController = std::make_unique<PlayerController>(*m_player);
	auto newEnemy = std::make_unique<Enemy>();
	Entity* entityPtr = newEnemy.get();
	m_entities.push_back(entityPtr);
	m_enemies.push_back(std::move(newEnemy));
	m_enemyController = std::make_unique<EnemyController>(m_enemies);
	m_player->setPosition({ 500, 500 });
	if (!m_sProjTxt.loadFromFile("ASSETS/WEAPON/sProjPlaceholder.png"))
	{
		std::cout << "Error loading Small Projectile Texture\n";
	}
	if (!m_mProjTxt.loadFromFile("ASSETS/WEAPON/mProjPlaceholder.png"))
	{
		std::cout << "Error loading Medium Projectile Texture\n";
	}
	if (!m_LProjTxt.loadFromFile("ASSETS/WEAPON/LProjPlaceholder.png"))
	{
		std::cout << "Error loading Large Projectile Texture\n";
	}
}

/// <summary>
/// Function in charge of deleting dead enemies and entities and updating their vectors
/// </summary>
void Game::refreshEntities()
{
	m_entities.clear();
	m_enemies.erase // erase enemies from remove_if's new end point to the old end point of the vector
	(
		std::remove_if // this function gives erase a new end point to the vector by moving "enemy dead" returns to the end of the vector
		(
			m_enemies.begin(), //from the start of the vector
			m_enemies.end(), // to the end of the vector
			[](const std::unique_ptr<Enemy>& e)
			{
				return e->getDead(); // an enemy returns as dead
			}
		),
		m_enemies.end() // the current end point of the vector
	);
	m_projectiles.erase // same as enemies, clears dead projectiles
	(
		std::remove_if
		(
			m_projectiles.begin(),
			m_projectiles.end(),
			[](const std::unique_ptr<Projectile>& p)
			{
				return p->getDead();
			}
		),
		m_projectiles.end()
	);
	if (m_player)
	{
		m_entities.push_back(m_player.get());
	}
	for (auto& enemy : m_enemies)
	{
		m_entities.push_back(enemy.get());
	}
	for (auto& projectiles : m_projectiles)
	{
		m_entities.push_back(projectiles.get());
	}
}
void Game::spawnProjectile(Entity* shooter, const sf::Vector2f& position, const sf::Vector2f& direction, float speed, float damage, float range, int txt)
{
	if (txt == 1)
	{
		m_projectiles.push_back(std::make_unique<Projectile>(shooter, m_sProjTxt, position, direction, speed, damage, range));
	}
	if (txt == 2)
	{
		m_projectiles.push_back(std::make_unique<Projectile>(shooter, m_mProjTxt, position, direction, speed, damage, range));
	}
	if (txt == 3)
	{
		m_projectiles.push_back(std::make_unique<Projectile>(shooter, m_LProjTxt, position, direction, speed, damage, range));
	}
}
