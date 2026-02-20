#include "EnemyController.h"
#include "Enemy.h"
#include <math.h>
#include <random>
#include "Weapon.h"
#include "WeaponType.h"
#include "Level.h"

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
void EnemyController::update(float dt, GamePlay& game, sf::Vector2f playerPos, Level& level)
{
	m_playerPos = playerPos;
	for (auto& enemyPtr : m_enemies)
	{
		Enemy& enemy = *enemyPtr;
		enemy.setVelocity(enemy.getSpeedVector()); // sends the new velocity to the enemy where it's updated
		if (enemy.getAttackingPlayer() == true)
		{
			enemy.shooting(dt, game, playerPos, level);
		}
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
		if (enemy.getDistToPlayer() < 500) // if player is in enemy's range, look at player and attack him
		{
			enemy.setFacingDir(t_playerPos - enemy.getPosition()); // Get the direction vector by taking away enemy's position from the player's position
			m_angleRadians = std::atan2(enemy.getFacingDir().y, enemy.getFacingDir().x); // Calculate the angle into radians
			m_angleDegrees = m_angleRadians * 180.0f / 3.14159265f; // calculate the radians into degrees
			m_angleDegrees += 90.f; // add an offset as the sprite is facing up by default
			enemy.updateAim(t_playerPos, m_angleDegrees); // send information to update enemy aim in the enemy class
			enemy.setAttackingPlayer(true);
		}
		else if (enemy.getIsMoving() && enemy.getAttackingPlayer() == false) // if enemy is moving and not attacking player, look where you're walking
		{
			enemy.setFacingDir(enemy.getNewPos() - enemy.getPosition());
			m_angleRadians = std::atan2(enemy.getFacingDir().y, enemy.getFacingDir().x);
			m_angleDegrees = m_angleRadians * 180.0f / 3.1459265f;
			m_angleDegrees += 90.0f;
			enemy.updateAim(t_playerPos, m_angleDegrees);
		}
		else if (enemy.getDistToPlayer() > 2000 && enemy.getAttackingPlayer() == true) // if player walks too far away, stop attacking him
		{
			enemy.setAttackingPlayer(false);
		}
		else if (enemy.getAttackingPlayer() == true) // if attacking player, look at him no matter the range
		{
			enemy.setFacingDir(t_playerPos - enemy.getPosition());
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
		if (enemy.getAttackingPlayer() == true && enemy.getWeaponType() == weaponType::melee) // if enemy has melee, walk towards player
		{
			enemy.setNewPos(m_playerPos);
			enemy.setIsMoving(true);
		}

		if (!enemy.getIsMoving()) // this picks a coordinate for the enemy to walk towards if it's not moving
		{
			randomNo = (rand() % 800) + 1;
			{
				if (randomNo == 1)
				{
					enemy.setNewPos({ enemy.getPosition().x + (rand() % 400) + 50,enemy.getPosition().y + (rand() % 400) + 50 });
					enemy.setIsMoving(true);
				}
				if (randomNo == 2)
				{
					enemy.setNewPos({ enemy.getPosition().x - ((rand() % 400) + 50),enemy.getPosition().y + (rand() % 400) + 50 });
					enemy.setIsMoving(true);
				}
				if (randomNo == 3)
				{
					enemy.setNewPos({ enemy.getPosition().x + (rand() % 400) + 50,enemy.getPosition().y - ((rand() % 400) + 50 )});
					enemy.setIsMoving(true);
				}
				if (randomNo == 4)
				{
					enemy.setNewPos({ enemy.getPosition().x - ((rand() % 400) + 50),enemy.getPosition().y - ((rand() % 400) + 50 )});
					enemy.setIsMoving(true);
				}

			}
		}

		enemy.setSpeedVector({ (enemy.getNewPos().x - enemy.getPosition().x) , (enemy.getNewPos().y - enemy.getPosition().y) }); // set speed after moving

		if (enemy.getAttackingPlayer() == false) // if not attacking player, move at walk speed
		{
			if (enemy.getSpeedVector().x > enemy.getTopSpeed()) // fix speed if faster than walking speed and not engaged
			{
				enemy.setSpeedVector({ enemy.getTopSpeed(),enemy.getSpeedVector().y });
			}
			else if (enemy.getSpeedVector().x < -(enemy.getTopSpeed()))
			{
				enemy.setSpeedVector({ -enemy.getTopSpeed(), enemy.getSpeedVector().y });
			}
			if (enemy.getSpeedVector().y > enemy.getTopSpeed())
			{
				enemy.setSpeedVector({ enemy.getSpeedVector().x, enemy.getTopSpeed() });
			}
			else if (enemy.getSpeedVector().y < -(enemy.getTopSpeed()))
			{
				enemy.setSpeedVector({ enemy.getSpeedVector().x, -enemy.getTopSpeed() });
			}
		}
		if (enemy.getAttackingPlayer() == true) // if attacking player, move at sprint speed
		{
			if (enemy.getSpeedVector().x > enemy.getSprintSpeed()) // fix speed if faster than sprinting speed and engaged
			{
				enemy.setSpeedVector({ enemy.getSprintSpeed(),enemy.getSpeedVector().y });
			}
			else if (enemy.getSpeedVector().x < -(enemy.getSprintSpeed()))
			{
				enemy.setSpeedVector({ -enemy.getSprintSpeed(), enemy.getSpeedVector().y });
			}
			if (enemy.getSpeedVector().y > enemy.getSprintSpeed())
			{
				enemy.setSpeedVector({ enemy.getSpeedVector().x, enemy.getSprintSpeed() });
			}
			else if (enemy.getSpeedVector().y < -(enemy.getSprintSpeed()))
			{
				enemy.setSpeedVector({ enemy.getSpeedVector().x, -enemy.getSprintSpeed() });
			}
		}
		enemy.setVelocity(enemy.getSpeedVector());
		enemy.setDistToGoal(std::sqrt((enemy.getNewPos().x - enemy.getPosition().x) * (enemy.getNewPos().x - enemy.getPosition().x) +
			(enemy.getNewPos().y - enemy.getPosition().y) * (enemy.getNewPos().y - enemy.getPosition().y)));
		if (enemy.getDistToGoal() < 20) // if enemy within 20 pixels of goal, set velocity to 0
		{
			enemy.setVelocity({ 0,0 });
			enemy.setIsMoving(false);
		}
	}
}
