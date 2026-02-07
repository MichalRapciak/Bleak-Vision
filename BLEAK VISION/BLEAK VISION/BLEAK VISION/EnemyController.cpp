#include "EnemyController.h"
#include "Enemy.h"
#include <math.h>
#include <random>

EnemyController::EnemyController(Enemy& enemy) : m_enemy(enemy)
{
	srand(time(nullptr)); // sets up random seed
}
EnemyController::~EnemyController()
{
}

/// <summary>
/// updating enemy movement - can be turned off if within menus.
/// </summary>
void EnemyController::update()
{
	m_enemy.setVelocity(m_speedVector); // sends the new velocity to the enemy where it's updated
}

/// <summary>
/// Function that aims at the player
/// </summary>
/// <param name="t_playerPos"></param>
void EnemyController::aimAtPlayer(sf::Vector2f t_playerPos)
{
	dx = t_playerPos.x - m_enemy.getPosition().x;
	dy = t_playerPos.y - m_enemy.getPosition().y;
	m_playerDistance = std::sqrt((dx * dx) + (dy * dy)); // distance from player
	if (m_playerDistance < 500)
	{
		m_facingDirection = t_playerPos - m_enemy.getPosition(); // Get the direction vector by taking away enemy's position from the player's position
		m_angleRadians = std::atan2(m_facingDirection.y, m_facingDirection.x); // Calculate the angle into radians
		m_angleDegrees = m_angleRadians * 180.0f / 3.14159265f; // calculate the radians into degrees
		m_angleDegrees += 90.f; // add an offset as the sprite is facing up by default
		m_enemy.updateAim(t_playerPos, m_angleDegrees); // send information to update enemy aim in the enemy class
	}
	else if (isMoving)
	{
		m_facingDirection = m_enemyNewPos - m_enemy.getPosition();
		m_angleRadians = std::atan2(m_facingDirection.y, m_facingDirection.x);
		m_angleDegrees = m_angleRadians * 180.0f / 3.1459265f;
		m_angleDegrees += 90.0f;
		m_enemy.updateAim(t_playerPos, m_angleDegrees);
	}
}

/// <summary>
/// Function for enemy movement and AI
/// </summary>
void EnemyController::movementAI()
{
	if (!isMoving) // this picks a coordinate for the enemy to walk towards if it's not moving
	{
		randomNo = (rand() % 500) + 1;
		{
			if (randomNo == 1)
			{
				m_enemyNewPos.x = m_enemy.getPosition().x + (rand() % 50) + 50;
				m_enemyNewPos.y = m_enemy.getPosition().y + (rand() % 50) + 50;
				isMoving = true;
			}
			if (randomNo == 2)
			{
				m_enemyNewPos.x = m_enemy.getPosition().x - (rand() % 50) + 50;
				m_enemyNewPos.y = m_enemy.getPosition().y + (rand() % 50) + 50;
				isMoving = true;
			}
			if (randomNo == 3)
			{
				m_enemyNewPos.x = m_enemy.getPosition().x + (rand() % 50) + 50;
				m_enemyNewPos.y = m_enemy.getPosition().y - (rand() % 50) + 50;
				isMoving = true;
			}
			if (randomNo == 4)
			{
				m_enemyNewPos.x = m_enemy.getPosition().x - (rand() % 50) + 50;
				m_enemyNewPos.y = m_enemy.getPosition().y - (rand() % 50) + 50;
				isMoving = true;
			}

		}
	}
	m_speedVector = { (m_enemyNewPos.x - m_enemy.getPosition().x) , (m_enemyNewPos.y - m_enemy.getPosition().y)};
	m_distanceFromGoal = std::sqrt((m_enemyNewPos.x - m_enemy.getPosition().x)* (m_enemyNewPos.x - m_enemy.getPosition().x) + 
		(m_enemyNewPos.y - m_enemy.getPosition().y)* (m_enemyNewPos.y - m_enemy.getPosition().y));
	m_enemy.setVelocity(m_speedVector);
	if (m_distanceFromGoal < 20)
	{
		m_speedVector = { 0,0 };
		isMoving = false;
	}
}
