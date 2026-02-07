#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

/// <summary>
/// This class is in charge of Enemy Data
/// </summary>
class Enemy
{
public:
	Enemy();
	~Enemy();


	sf::Vector2f getPosition() { return m_enemyPosition; }
	sf::Sprite getSprite() { return m_enemySprite; }
	void setPosition(sf::Vector2f t_location) { m_enemyPosition = t_location; m_enemySprite.setPosition(m_enemyPosition); }
	void setEnemyTexture(sf::Texture t_texture) { m_enemyTexture = t_texture; std::cout << "set enemy text" << std::endl; }
	float getSpeed() { return m_enemySpeed; }
	sf::Vector2f getVelocity() { return m_enemyVelocity; }
	void setVelocity(sf::Vector2f t_velocity) { m_enemyVelocity = t_velocity; }
	float getTopSpeed() { return m_enemyTopSpeed; }
	float getSprintSpeed() { return m_enemySprintSpeed; }
	sf::Vector2f getEnemyAim() { return m_enemyAim; }
	void setEnemyAim(sf::Vector2f t_mousePos) { m_enemyAim = t_mousePos; }
	void updateAim(sf::Vector2f t_playerPos, float facingDir);
	void update(float dt);


private:
	sf::Sprite m_enemySprite;
	sf::Texture m_enemyTexture;
	sf::Vector2f m_enemyPosition;
	float m_enemySpeed = 10;
	float m_enemyTopSpeed = 60;
	float m_enemySprintSpeed = 120;
	sf::Vector2f m_enemyVelocity{ 0.0,0.0 };
	sf::Vector2f m_enemyAim{ 0, 0 };

};