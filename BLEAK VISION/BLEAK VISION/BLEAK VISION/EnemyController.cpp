#include "EnemyController.h"
#include "Enemy.h"
#include <math.h>
#include <random>

EnemyController::EnemyController(std::vector<std::unique_ptr<Enemy>>& enemies) : m_enemies(enemies)
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
	for (auto& enemyPtr : m_enemies)
	{
		Enemy& enemy = *enemyPtr;
		enemy.setVelocity(m_speedVector); // sends the new velocity to the enemy where it's updated
	}
}

/// <summary>
/// Function that aims at the player
/// </summary>
/// <param name="t_playerPos"></param>
void EnemyController::aimAtPlayer(sf::Vector2f t_playerPos)
{
	for (auto& enemyPtr : m_enemies)
	{
		Enemy& enemy = *enemyPtr;
		dx = t_playerPos.x - enemy.getPosition().x;
		dy = t_playerPos.y - enemy.getPosition().y;
		enemy.setDistToPlayer(std::sqrt((dx * dx) + (dy * dy))); // distance from player
		if (enemy.getDistToPlayer() < 500)
		{
			enemy.setFacingDir(t_playerPos - enemy.getPosition()); // Get the direction vector by taking away enemy's position from the player's position
			m_angleRadians = std::atan2(enemy.getFacingDir().y, enemy.getFacingDir().x); // Calculate the angle into radians
			m_angleDegrees = m_angleRadians * 180.0f / 3.14159265f; // calculate the radians into degrees
			m_angleDegrees += 90.f; // add an offset as the sprite is facing up by default
			enemy.updateAim(t_playerPos, m_angleDegrees); // send information to update enemy aim in the enemy class
		}
		else if (enemy.getIsMoving())
		{
			enemy.setFacingDir(enemy.getNewPos() - enemy.getPosition());
			m_angleRadians = std::atan2(enemy.getFacingDir().y, enemy.getFacingDir().x);
			m_angleDegrees = m_angleRadians * 180.0f / 3.1459265f;
			m_angleDegrees += 90.0f;
			enemy.updateAim(t_playerPos, m_angleDegrees);
		}
	}
}

/// <summary>
/// Function for enemy movement and AI
/// </summary>
void EnemyController::movementAI()
{
	for (auto& enemyPtr : m_enemies)
	{
		Enemy& enemy = *enemyPtr;
		if (!enemy.getIsMoving()) // this picks a coordinate for the enemy to walk towards if it's not moving
		{
			randomNo = (rand() % 500) + 1;
			{
				if (randomNo == 1)
				{
					enemy.setNewPos({ enemy.getPosition().x + (rand() % 50) + 50,enemy.getPosition().y + (rand() % 50) + 50 });
					enemy.setIsMoving(true);
				}
				if (randomNo == 2)
				{
					enemy.setNewPos({ enemy.getPosition().x - (rand() % 50) + 50,enemy.getPosition().y + (rand() % 50) + 50 });
					enemy.setIsMoving(true);
				}
				if (randomNo == 3)
				{
					enemy.setNewPos({ enemy.getPosition().x + (rand() % 50) + 50,enemy.getPosition().y - (rand() % 50) + 50 });
					enemy.setIsMoving(true);
				}
				if (randomNo == 4)
				{
					enemy.setNewPos({ enemy.getPosition().x - (rand() % 50) + 50,enemy.getPosition().y - (rand() % 50) + 50 });
					enemy.setIsMoving(true);
				}

			}
		}
		enemy.setVelocity( { (enemy.getNewPos().x - enemy.getPosition().x) , (enemy.getNewPos().y - enemy.getPosition().y)});
		enemy.setDistToGoal(std::sqrt((enemy.getNewPos().x - enemy.getPosition().x) * (enemy.getNewPos().x - enemy.getPosition().x) +
			(enemy.getNewPos().y - enemy.getPosition().y) * (enemy.getNewPos().y - enemy.getPosition().y)));
		if (enemy.getDistToGoal() < 20)
		{
			enemy.setVelocity({ 0,0 });
			enemy.setIsMoving(false);
		}
	}
}
