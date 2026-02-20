#include "GamePlay.h"
#include "Game.h"

GamePlay::GamePlay() : m_pauseText(m_font), m_playerHealth(m_font), m_gameOverText(m_font)
{
	setupGame();
	m_playerCam.setCenter(m_player->getPosition());
	m_playerCam.setSize({ 1920,1080 });
	m_playerCam.zoom(1.0f);
}

GamePlay::~GamePlay()
{
}

void GamePlay::initialise(sf::Font& t_font)
{
	m_font = t_font;
	m_pauseText.setFont(m_font); // Text seen on the screen
	m_pauseText.setString("Game Paused - Press Space to enter Skill Tree");
	m_pauseText.setCharacterSize(42);
	m_pauseText.setFillColor(sf::Color::Red);
	m_pauseText.setStyle(sf::Text::Bold);

	sf::FloatRect textSize = m_pauseText.getGlobalBounds(); // will be used to put the text in the middle
	float xpos = (1920 / 2) - (textSize.size.x / 2);
	m_pauseText.setPosition({ xpos, 1080 * 0.5f });

	m_gameOverText.setFont(m_font); // Text seen on the screen
	m_gameOverText.setString("You have Failed.\n Return to the Main Menu\nBy pressing space");
	m_gameOverText.setCharacterSize(42);
	m_gameOverText.setFillColor(sf::Color::Red);
	m_gameOverText.setStyle(sf::Text::Bold);

	textSize = m_gameOverText.getGlobalBounds(); // will be used to put the text in the middle
	xpos = (1920 / 2) - (textSize.size.x / 2);
	m_gameOverText.setPosition({ xpos, 1080 * 0.5f });

	m_playerHealth.setFont(m_font);
	m_playerHealth.setFillColor(sf::Color::White);
	m_playerHealth.setCharacterSize(40);
	m_playerHealth.setPosition({ 100,100 });

}	

/// <summary>
/// handle user and system events / inputs
/// get key pressed, mouse moves etc. from OS
/// do NOT do game update here
/// </summary>
void GamePlay::processEvents(sf::Event& t_event,sf::RenderWindow& t_window)
{
	if (const auto resized = t_event.getIf<sf::Event::Resized>()) //debugging to see if window resizing works
	{
		sf::Vector2f visibleArea(sf::Vector2f(resized->size));
		m_playerCam.setSize(visibleArea);
	}
	if(const auto keyPressed = t_event.getIf<sf::Event::KeyPressed>()) //user pressed a key
	{
		processKeys(t_event);
		if (!m_pause)
		m_playerController->inputHandler(t_event);
	}
	if(const auto keyReleased = t_event.getIf<sf::Event::KeyReleased>())
	{
		if (!m_pause)
		m_playerController->inputHandler(t_event);
	}
	if (const auto buttonPressed = t_event.getIf<sf::Event::MouseButtonPressed>())
	{
		if (!m_pause)
		m_playerController->inputHandler(t_event);
	}
	if (const auto buttonReleased = t_event.getIf<sf::Event::MouseButtonReleased>())
	{
		if (!m_pause)
		m_playerController->inputHandler(t_event);
	}
}

/// <summary>
/// This function processes all keyboard presses and performs the correct action
/// </summary>
/// <param name="t_event">key press event</param>
void GamePlay::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		if (!m_pause && !m_gameOver)
		{
			m_pause = true;
		}
		else if (m_pause)
		{
			m_pause = false;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
	{
		auto newEnemy = std::make_unique<Enemy>(m_level1.getCurrentWave());
		m_enemies.push_back(std::move(newEnemy));
		refreshEntities();
	}
	if (m_pause)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			Game::currentState = GameState::SkillTree;
		}
	}
	if (m_gameOver)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			Game::currentState = GameState::MainMenu;
		}
	}
}

/// <summary>
/// Updates the Game World
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void GamePlay::update(sf::Time& t_deltaTime, sf::RenderWindow& t_window)
{
	if (m_player->getDead())
	{
		m_gameOver = true;
	}
	if (!m_pause && !m_gameOver)
	{
		m_enemyController->aimAtPlayer(m_player->getPosition());
		m_enemyController->movementAI();
		m_enemyController->update(t_deltaTime.asSeconds(), *this, m_player->getPosition(), m_level1);
		mouseWorld = t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window)); // This gets mouse position in the world, depending on camera/view
		m_playerController->update(t_deltaTime.asSeconds(), *this);
		m_playerController->mouseAiming(mouseWorld);
		m_player->update(t_deltaTime.asSeconds(), m_level1);
		m_level1.update(*this);
		for (auto& enemy : m_enemies)
		{
			enemy->update(t_deltaTime.asSeconds(), m_level1, *m_player);
		}
		for (auto& projectile : m_projectiles)
		{
			projectile->update(t_deltaTime.asSeconds(), m_level1);
		}
		Collisions::getInstance().update(m_entities);
		refreshEntities();
		m_playerCam.setCenter({ (m_player->getPosition().x),(m_player->getPosition().y) }); // Center player camera to the player
	}
}

/// <summary>
/// Draw Frames and Switch Buffers
/// </summary>
void GamePlay::render(sf::RenderWindow& t_window)
{
	t_window.setView(m_playerCam); // Set Camera to player camera
	t_window.draw(m_level1.getLevelBG());
	t_window.draw(m_player->getSprite());
	t_window.draw(m_player->getWeaponSprite());
	for (auto& enemy : m_enemies)
	{
		t_window.draw(enemy->getSprite());
		t_window.draw(enemy->getWeaponSprite());
	}
	for (auto& projectile : m_projectiles)
	{
		t_window.draw(projectile->getSprite());
	}
	t_window.setView(t_window.getDefaultView());
	t_window.draw(m_playerHealth);
	t_window.setView(m_playerCam); // Set Camera to player camera
	if (m_pause)
	{
		t_window.setView(t_window.getDefaultView());
		sf::RectangleShape overlay;
		overlay.setSize(sf::Vector2f(t_window.getSize()));
		overlay.setFillColor(sf::Color(100, 100, 100, 150));
		t_window.draw(overlay);
		t_window.draw(m_pauseText);
		t_window.setView(m_playerCam);
	}
	if (m_gameOver)
	{
		t_window.setView(t_window.getDefaultView());
		sf::RectangleShape overlay;
		overlay.setSize(sf::Vector2f(t_window.getSize()));
		overlay.setFillColor(sf::Color(50, 50, 50, 100));
		t_window.draw(overlay);
		t_window.draw(m_gameOverText);
		t_window.setView(m_playerCam);
	}
}

/// <summary>
/// Setting player up, temporarily setting up enemies
/// </summary>
void GamePlay::setupGame()
{
	m_player = std::make_unique<Player>();
	m_entities.push_back(m_player.get());
	m_playerController = std::make_unique<PlayerController>(*m_player);
	auto newEnemy = std::make_unique<Enemy>(m_level1.getCurrentWave());
	Entity* entityPtr = newEnemy.get();
	m_entities.push_back(entityPtr);
	m_enemies.push_back(std::move(newEnemy));
	m_enemyController = std::make_unique<EnemyController>(m_enemies);
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
void GamePlay::refreshEntities()
{
	m_playerHealth.setString("Health: " + std::to_string(static_cast<int>(m_player.get()->getHealth())) + "\n" + "Wave: " + std::to_string(m_level1.getCurrentWave()));
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

	enemiesKilled = m_player.get()->getEnemiesKilled();
}

void GamePlay::spawnProjectile(Entity* shooter, const sf::Vector2f& position, const sf::Vector2f& direction, float speed, float damage, float range, int txt)
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

void GamePlay::spawnEnemy(sf::Vector2f t_pos)
{
	auto newEnemy = std::make_unique<Enemy>(m_level1.getCurrentWave());
	newEnemy->setPosition(t_pos);
	m_enemies.push_back(std::move(newEnemy));
	refreshEntities();
}
