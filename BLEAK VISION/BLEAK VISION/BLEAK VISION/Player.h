#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
public:
	Player();
	~Player();


	
	sf::Vector2f getPosition() { return m_playerPosition; }
	sf::Sprite getSprite() { return m_playerSprite; }
	void setPosition(sf::Vector2f t_location) { m_playerPosition = t_location; m_playerSprite.setPosition(m_playerPosition); }
	void setPlayerTexture(sf::Texture t_texture) { m_playerTexture = t_texture; std::cout << "set player text" << std::endl; }
	float getSpeed() { return m_playerSpeed; }
	sf::Vector2f getVelocity() { return m_playerVelocity; }
	float getTopSpeed() { return m_playerTopSpeed; }
	

private:
	sf::Sprite m_playerSprite;
	sf::Texture m_playerTexture;
	sf::Vector2f m_playerPosition;
	float m_playerSpeed = 1;
	float m_playerTopSpeed = 5;
	sf::Vector2f m_playerVelocity{ 0.0,0.0 };
};