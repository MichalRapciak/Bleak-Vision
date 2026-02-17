#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"

class Level;
class Player;

/// <summary>
/// This class is in charge of Enemy Data
/// </summary>
class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();


	sf::Vector2f getPosition() { return m_enemyPosition; }
	sf::Sprite getSprite() { return m_enemySprite; }
	void setPosition(sf::Vector2f t_location) { m_enemyPosition = t_location; m_enemySprite.setPosition(m_enemyPosition); }
	void setEnemyTexture(sf::Texture t_texture) { m_enemyTexture = t_texture; std::cout << "set enemy text" << std::endl; }
	sf::Vector2f getVelocity() { return m_enemyVelocity; }
	void setVelocity(sf::Vector2f t_velocity) { m_enemyVelocity = t_velocity; }
	sf::Vector2f getEnemyAim() { return m_enemyAim; }

	float getHealth() const override { return m_enemyHealth; }
	sf::FloatRect getBoundingBox() const override { return sf::FloatRect({ m_enemyPosition.x - 25,m_enemyPosition.y - 25 }, { 50,50 }); }
	void takeDamage(float amount) override { m_enemyHealth -= amount; /*std::cout << "enemy hit for " << amount << " damage!\n";*/ }

	void setEnemyAim(sf::Vector2f t_mousePos) { m_enemyAim = t_mousePos; }
	void updateAim(sf::Vector2f t_playerPos, float facingDir);
	void update(float dt, Level& level, Player& player);
	bool getIsMoving() { return isMoving; }
	sf::Vector2f getFacingDir() { return m_facingDirection; }
	sf::Vector2f getNewPos() { return m_newPos; }
	float getDistToPlayer() { return m_playerDistance; }
	float getDistToGoal() { return m_distanceFromGoal; }
	void setIsMoving(bool t_move) { isMoving = t_move; }
	void setFacingDir(sf::Vector2f t_faceDir) { m_facingDirection = t_faceDir; }
	void setNewPos(sf::Vector2f t_newPos) { m_newPos = t_newPos; }
	void setDistToPlayer(float t_playerDist) { m_playerDistance = t_playerDist; }
	void setDistToGoal(float t_distToGoal) { m_distanceFromGoal = t_distToGoal; }
	bool getDead() { return isDead; }
	void setDead(bool t_dead) { isDead = t_dead; }
	float getTopSpeed() { return m_enemyTopSpeed; }
	sf::Vector2f getSpeedVector() { return m_speedVector; }
	void setSpeedVector(sf::Vector2f t_vector) { m_speedVector = t_vector; }

	void moveWithCollisions(sf::Vector2f movement, Level& level);
	void moveAxis(float dx, float dy, Level& level);


private:
	sf::Sprite m_enemySprite;
	sf::Texture m_enemyTexture;
	sf::Vector2f m_enemyPosition;
	sf::Vector2f m_enemyVelocity{ 0.0,0.0 }; //current enemy speed vector
	sf::Vector2f m_enemyAim{ 0, 0 };
	bool isDamaged = false;
	float m_enemyHealth = 20;
	bool isDead = false;
	// moved from EnemyController
	bool isMoving = 0; // Boolean to check if enemy is moving
	sf::Vector2f m_facingDirection = { 0,0 };
	sf::Vector2f m_newPos{ 0,0 }; // New enemy position after speed vector is added on
	float m_playerDistance = 0.0f;
	float m_distanceFromGoal = 0.0f;
	sf::Vector2f m_enemyMovement;
	sf::Vector2f m_speedVector{ 0,0 }; // Current speed vector
	float m_enemyTopSpeed = 90;

};