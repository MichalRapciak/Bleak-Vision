#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "PlayerController.h"
#include "Enemy.h"
#include "EnemyController.h"
#include "Level.h"
#include "Entity.h"
#include "Collisions.h"
#include "Projectile.h"
#include "HitInfo.h"
#include "Weapon.h"

class GamePlay
{
public:
	GamePlay(); // main game function
	~GamePlay();

	void processEvents(sf::Event& t_event,sf::RenderWindow& t_window);
	void processKeys(sf::Event t_event);
	void update(sf::Time& t_deltaTime, sf::RenderWindow& t_window);
	void render(sf::RenderWindow& t_window);
	void initialise(sf::Font& t_font);

	void spawnProjectile(Entity* shooter, const sf::Vector2f& position, const sf::Vector2f& direction, float speed, float damage, float range, int txt);
	int getEnemyCount() { return m_enemies.size(); };
	void spawnEnemy(sf::Vector2f t_pos);
	Player& getPlayer() { return *m_player; }
	int getEnemiesKilled() { return enemiesKilled; }
	void resetEnemiesKilled() { enemiesKilled = 0; m_player.get()->setEnemiesKilled(0); }
	int getPlayerRep() { return playerRep; }

	bool getGameOver() { return m_gameOver; }
	bool getGameWon() { return m_gameWon; }

protected:
	sf::Font m_font;
	sf::Text m_pauseText;
	sf::Text m_gameOverText;
	sf::Text m_playerHealth;
	sf::Text m_gameWonText;

private:
	bool m_pause = false;
	bool m_gameOver = false;
	bool m_gameWon = false;

	std::unique_ptr<Player> m_player;
	std::unique_ptr<PlayerController> m_playerController;
	sf::Vector2f mouseWorld = { 0,0 };
	sf::View m_playerCam; // Player-centered camera
	Level m_level1;

	std::vector<Entity*> m_entities;
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	std::unique_ptr<EnemyController> m_enemyController;

	std::vector<std::unique_ptr<Projectile>> m_projectiles;
	sf::Texture m_sProjTxt;
	sf::Texture m_mProjTxt;
	sf::Texture m_LProjTxt;

	int enemiesKilled = 0;
	int playerRep = 0;
	sf::String currentAlignment = "None";

	void setupGame();
	void refreshEntities();

};