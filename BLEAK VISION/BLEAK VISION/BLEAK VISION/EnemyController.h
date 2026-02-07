#pragma once
#include <SFML/Graphics.hpp>

class Enemy;

class EnemyController
{
public:
	EnemyController(Enemy& Enemy);
	~EnemyController();

	void update();
	void aimAtPlayer(sf::Vector2f t_playerPos);
	void movementAI();


private:
	Enemy& m_enemy;
	sf::Vector2f m_speedVector{ 0,0 }; // Current speed vector
	sf::Vector2f m_newPos{ 0,0 }; // New enemy position after speed vector is added on
	bool isMoving = 0; // Boolean to check if enemy is moving
	bool m_up = false;
	bool m_down = false;
	bool m_left = false;
	bool m_right = false;
	bool isSprinting = false;
	const int m_speedNearlyZero = 1; // This value determines when enemy's speed is considered "nearly zero" and is used in a statement to set enemy's speed to 0.
	float m_enemyDeceleration = 1;
	sf::Vector2f playerPos = { 0,0 };
	sf::Vector2f m_facingDirection = { 0,0 };
	float m_angleRadians = 0.0f;
	float m_angleDegrees = 0.0f;
	float m_playerDistance = 0.0f;
	float dx = 0.0f;
	float dy = 0.0f;
	short randomNo = 0;
	sf::Vector2f m_enemyNewPos = { 0,0 };
	float m_distanceFromGoal = 0.0f;
};