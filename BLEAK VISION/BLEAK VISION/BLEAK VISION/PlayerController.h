#pragma once
#include <SFML/Graphics.hpp>

class Player; // I call this class here so the PlayerController knows to expect a player when it's loaded, without having to load the class here.
class GamePlay;

/// <summary>
/// This class is in charge of all the calculations depending on player movement and aiming, letting the player class be less bloated
/// </summary>
class PlayerController
{
public:
	PlayerController(Player& player);
	~PlayerController();

	void inputHandler(const sf::Event t_event);
	void update(float dt, GamePlay& game);
	void mouseAiming(sf::Vector2f t_mouseWorld);

private:
	Player& m_player;
	sf::Vector2f m_speedVector{ 0,0 }; // Current speed vector
	sf::Vector2f m_newPos{ 0,0 }; // New player position after speed vector is added on
	bool isMoving = 0; // Boolean to check if player is moving
	bool m_up = false;
	bool m_down = false;
	bool m_left = false;
	bool m_right = false;
	bool isSprinting = false;
	bool isShooting = false;
	const int m_speedNearlyZero = 1; // This value determines when player's speed is considered "nearly zero" and is used in a statement to set player's speed to 0.
	float m_playerDeceleration = 1;
	sf::Vector2f mousePos = { 0,0 };
	sf::Vector2f m_facingDirection = { 0,0 };
	float m_angleRadians = 0.0f;
	float m_angleDegrees = 0.0f;

};