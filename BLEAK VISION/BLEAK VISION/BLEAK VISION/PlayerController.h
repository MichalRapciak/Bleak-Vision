#pragma once
#include <SFML/Graphics.hpp>

class Player;

class PlayerController
{
public:
	PlayerController(Player& player);
	~PlayerController();

	void playerMovement(const sf::Event t_event, bool isPressed);
	void playerIdle(bool isPressed);

private:
	Player& m_player;
	sf::Vector2f m_speedVector{ 0,0 }; // Current speed vector
	sf::Vector2f m_newPos{ 0,0 }; // New player position after speed vector is added on
	bool isMoving = 0; // Boolean to check if player is moving
};