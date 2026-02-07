#include "Enemy.h"

Enemy::Enemy() : m_enemySprite(m_enemyTexture)
{
	if (!m_enemyTexture.loadFromFile("Assets/Player/playerplaceholder.png", false, sf::IntRect({ 0,0 }, { 200, 200 }))) // if texture doesnt load, output text
	{
		std::cout << "Texture not loaded." << std::endl;
	}
	m_enemyPosition = { 500,40 };
	m_enemySprite.setTexture(m_enemyTexture);
	m_enemySprite.setTextureRect(sf::IntRect({ 0,0 }, { 200,200 }));
	m_enemySprite.setOrigin({ 100,100 });
	m_enemySprite.setScale({ 0.3,0.3 });
	m_enemySprite.setColor(sf::Color::Red);
	m_enemySprite.setPosition(m_enemyPosition);
}

Enemy::~Enemy()
{

}



/// <summary>
/// Function used to update player position
/// </summary>
/// <param name="dt"></param>
void Enemy::update(float dt)
{
	m_enemyPosition += m_enemyVelocity * dt; // Multiply by delta time - time between frames - to make sure movement is always at constant speed
	m_enemySprite.setPosition(m_enemyPosition);
}

/// <summary>
/// Function used to update player aiming
/// </summary>
/// <param name="t_mousePos"></param>
/// <param name="facingDir"></param>
void Enemy::updateAim(sf::Vector2f t_playerPos, float facingDir)
{
	m_enemyAim = t_playerPos;
	m_enemySprite.setRotation(sf::degrees(facingDir));
}