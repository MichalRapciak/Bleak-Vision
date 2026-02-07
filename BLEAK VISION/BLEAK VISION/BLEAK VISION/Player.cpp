#include "Player.h"

/// <summary>
/// Setting up player sprite when the player function is created.
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
	m_playerSprite.setScale({ 0.3,0.3 });
	m_playerSprite.setPosition(m_playerPosition);
}

Player::~Player()
{
}

/// <summary>
/// Function used to update player position
/// </summary>
/// <param name="dt"></param>
void Player::update(float dt)
{
	m_playerPosition += m_playerVelocity * dt; // Multiply by delta time - time between frames - to make sure movement is always at constant speed
	m_playerSprite.setPosition(m_playerPosition);
}

/// <summary>
/// Function used to update player aiming
/// </summary>
/// <param name="t_mousePos"></param>
/// <param name="facingDir"></param>
void Player::updateAim(sf::Vector2f t_mousePos, float facingDir)
{
	m_playerAim = t_mousePos;
	m_playerSprite.setRotation(sf::degrees(facingDir));
}