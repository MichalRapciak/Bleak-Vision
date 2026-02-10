#include "Player.h"
#include "Weapon.h"
#include "Melee.h"

/// <summary>
/// Setting up player sprite when the player function is created.
/// </summary>
Player::Player() : m_playerSprite(m_playerTexture), m_weaponSprite(m_weaponTxt)
{
	if (!m_playerTexture.loadFromFile("Assets/Player/playerplaceholder.png", false, sf::IntRect({ 0,0 },{ 200, 200 }))) // if texture doesnt load, output text
	{
		std::cout << "Texture not loaded." << std::endl;
	}
	m_playerPosition = { 500,500 };
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setTextureRect(sf::IntRect({0,0},{200,200}));
	m_playerSprite.setOrigin({ 100,100 });
	m_playerSprite.setScale({ 0.3f,0.3f });
	m_playerSprite.setPosition(m_playerPosition);
	m_playerHealth = 20;
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
	if (!isDead)
	{
		m_playerPosition += m_playerVelocity * dt; // Multiply by delta time - time between frames - to make sure movement is always at constant speed
		m_playerSprite.setPosition(m_playerPosition);
		if (m_weapon) // if a weapon is created, keep it glued to the player
		{
			m_weaponSprite.setPosition({ m_playerPosition.x, m_playerPosition.y });
		}
	}
}

/// <summary>
/// Function used to update player aiming
/// </summary>
/// <param name="t_mousePos"></param>
/// <param name="facingDir"></param>
void Player::updateAim(sf::Vector2f t_mousePos, float facingDir)
{
	if (!isDead)
	{
		m_playerAim = t_mousePos;
		m_playerSprite.setRotation(sf::degrees(facingDir));
	}
}

/// <summary>
/// This function is in charge of shooting
/// </summary>
/// <param name="dt"></param>
void Player::shooting(float dt)
{
	if (m_weapon) //if holding a weapon, try shoot. This line is necessary since if the player tries to shoot with no weapon active, the function points to null and crashes the game.
	{
		m_weapon->tryFire(dt,*this); // *this passes this (the player) to the weapon
	}
	else
	{
	}
}

/// <summary>
/// this function is in charge of picking a weapon slot and rendering said weapon
/// </summary>
/// <param name="t_weaponType"></param>
void Player::equipWeapon(weaponType t_weaponType)
{
	if (!isDead)
	{
		if (t_weaponType == weaponType::melee) // If you select a melee weapon
		{
			m_weapon = std::make_unique<Melee>(); // Creates Melee Weapon instance
		}
		m_weaponSprite.setTexture(m_weapon->getTxt()); // Takes texture of current weapon (in this case melee in the melee class)
		sf::Vector2i txtSize = { (int)m_weaponSprite.getTexture().getSize().x, (int)m_weaponSprite.getTexture().getSize().y }; // gets the size of the texture
		m_weaponSprite.setTextureRect(sf::IntRect({ 0,0 }, { txtSize.x, txtSize.y })); // sets the texture rectangle to the size of the texture - so you can actually see it
		m_weaponSprite.setOrigin({ txtSize.x / 2.0f, txtSize.y / 2.0f }); // sets texture position to the middle of the texture. Will be different later
	}
}
