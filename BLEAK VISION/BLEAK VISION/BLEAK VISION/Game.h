#ifndef GAME_HPP
#define GAME_HPP
/// include guards so the file isn't processed twice
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "PlayerController.h"
#include "Enemy.h"
#include "EnemyController.h"
#include "Level.h"
#include "Collisions.h"

#endif

class Game
{
public:
	Game(); // main game function
	~Game();
	void run();

private:
	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control on exiting game

	std::unique_ptr<Player> m_player;
	std::unique_ptr<PlayerController> m_playerController;
	sf::Vector2f mouseWorld = { 0,0 };
	sf::View m_playerCam; // Player-centered camera
	Level m_level1;

	std::vector<Entity*> m_entities;
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	std::unique_ptr<EnemyController> m_enemyController;

	void setupPlayer();
	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void refreshEntities();

};