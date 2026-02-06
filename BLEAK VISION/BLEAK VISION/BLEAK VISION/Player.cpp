#include "Player.h"

/// <summary>
/// Setting up player sprite when the player function is created. Temporary.
/// </summary>
Player::Player() : m_playerSprite(m_playerTexture)
{
	if (!m_playerTexture.loadFromFile("Assets/Player/playerplaceholder.png", false, sf::IntRect({ 0,0 },{ 200, 200 }))) // if texture doesnt load, output text
	{
		std::cout << "Texture not loaded." << std::endl;
	}
	m_playerPosition = { 500,500 };
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setTextureRect(sf::IntRect({0,0},{200,200}));
	m_playerSprite.setOrigin({ 100,100 });
	m_playerSprite.setScale({ 0.7,0.7 });
	m_playerSprite.setPosition(m_playerPosition);
}

Player::~Player()
{
}