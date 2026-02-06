#ifndef GAME_HPP
#define GAME_HPP
/// include guards so the file isn't processed twice
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "PlayerController.h"

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

	Player m_player;
	PlayerController m_playerController{ m_player };

	void setupPlayer();
	void processEvents();
	void processKeys(sf::Event t_event);
	bool isAnyKeyPressed();
	void update(sf::Time t_deltaTime);
	void render();

};