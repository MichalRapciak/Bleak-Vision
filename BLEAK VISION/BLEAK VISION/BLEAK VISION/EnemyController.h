#pragma once
#include <SFML/Graphics.hpp>

class Enemy;

class EnemyController
{
public:
	EnemyController(std::vector<std::unique_ptr<Enemy>>& enemies);
	~EnemyController();

	void update();
	void aimAtPlayer(sf::Vector2f t_playerPos);
	void movementAI();


private:
	std::vector<std::unique_ptr<Enemy>>& m_enemies;
	const int m_speedNearlyZero = 1; // This value determines when enemy's speed is considered "nearly zero" and is used in a statement to set enemy's speed to 0.
	sf::Vector2f playerPos = { 0,0 };
	float m_angleRadians = 0.0f;
	float m_angleDegrees = 0.0f;
	float dx = 0.0f;
	float dy = 0.0f;
	short randomNo = 0;
};