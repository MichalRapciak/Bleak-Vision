#include "Player.h"
#include "Level.h"
#include "Weapon.h"
#include "Melee.h"
#include "ShortRange.h"
#include "MediumRange.h"
#include "LongRange.h"

/// <summary>
/// Setting up player sprite when the player function is created.
/// </summary>
Player::Player() : m_playerSprite(m_playerTexture), m_weaponSprite(m_weaponTxt), m_playerHalo(m_playerHaloTxt), m_playerHorns(m_playerHornsTxt)
{
	if (!m_playerTexture.loadFromFile("Assets/Player/playerplaceholder.png", false, sf::IntRect({ 0,0 },{ 200, 200 }))) // if texture doesnt load, output text
	{
		std::cout << "Texture not loaded." << std::endl;
	}
	m_playerPosition = { 4600,4800 };
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setTextureRect(sf::IntRect({0,0},{200,200}));
	m_playerSprite.setOrigin({ 100,100 });
	m_playerSprite.setScale({ 0.3f,0.3f });
	m_playerSprite.setPosition(m_playerPosition);
	// Default stats for weapons
	m_meleeStats = {0.5f, 0.f, 10.f, 150.f}; // cooldown - speed - damage - range
	m_shortStats = {0.15f, 600.f, 8.f , 400.f};
	m_mediumStats = {0.40f, 900.f, 16.f, 800.f};
	m_longStats = {1.0f, 1600.f, 32.f, 2400.f};
	m_playerStats = { 20.0f,100.0f, 240.0f,25.0f, 0.1f }; // health, walk speed, sprint speed, accel, regen
	m_playerHealth = m_playerStats.getHealth();

	if (!m_playerHaloTxt.loadFromFile("Assets/Player/playerhalo.png"))
	{
		std::cout << "couldnt load halo txt\n";
	}
	m_playerHalo.setTexture(m_playerHaloTxt);
	m_playerHalo.setTextureRect(sf::IntRect({ 0,0 }, { 200,200 }));
	m_playerHalo.setOrigin({ 100,100 });
	m_playerHalo.setScale({ 0.3f,0.3f });
	m_playerHalo.setPosition(m_playerPosition);
	m_playerHalo.setColor(sf::Color::Transparent);
	if (!m_playerHornsTxt.loadFromFile("Assets/Enemies/horns.png"))
	{
		std::cout << "couldnt load horns txt\n";
	}
	m_playerHorns.setTexture(m_playerHornsTxt);
	m_playerHorns.setTextureRect(sf::IntRect({ 0,0 }, { 200,200 }));
	m_playerHorns.setOrigin({ 100,100 });
	m_playerHorns.setScale({ 0.3f,0.3f });
	m_playerHorns.setPosition(m_playerPosition);
	m_playerHorns.setColor(sf::Color::Transparent);

}

Player::~Player()
{
}

/// <summary>
/// Function used to update player position
/// </summary>
/// <param name="dt"></param>
void Player::update(float dt, Level& level)
{
	if (!isDead)
	{
		updateReputation();
		if (m_playerHealth <= 0)
		{
			isDead = true;
		}
		if (m_playerHealth < m_playerStats.getHealth())
		{
			m_playerHealth += m_playerStats.getRegen() * dt;
		}

		if (m_rollCooldownTimer > 0)
		{
			m_rollCooldownTimer -= dt;
		}
		if (m_isRolling)
		{
			m_rollTimer += dt;
			m_playerVelocity += m_rollDirection * m_rollSpeed;
			m_playerSprite.rotate(sf::degrees( 1800.f * dt));

			if (m_rollTimer >= m_rollDuration)
			{
				m_isRolling = false;
			}
		}

		m_playerMovement = m_playerVelocity * dt; // Multiply by delta time - time between frames - to make sure movement is always at constant speed
		moveWithCollisions(m_playerMovement, level);
		m_playerSprite.setPosition(m_playerPosition);
		m_playerHalo.setPosition(m_playerPosition);
		m_playerHalo.setRotation(m_playerSprite.getRotation());
		m_playerHorns.setPosition(m_playerPosition);
		m_playerHorns.setRotation(m_playerSprite.getRotation());
		if (m_weapon) // if a weapon is created, keep it glued to the player
		{
			m_weaponSprite.setPosition({ m_playerPosition.x, m_playerPosition.y });
			m_weaponSprite.setRotation(m_playerSprite.getRotation());
			m_weaponSprite.setScale(m_playerSprite.getScale());
			m_weaponSprite.setColor(m_playerSprite.getColor());
			m_weapon->updateCooldown(dt);
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
		if (!m_isRolling)
		{
			m_playerAim = t_mousePos;
			m_playerSprite.setRotation(sf::degrees(facingDir));
		}
	}
}

/// <summary>
/// This function is in charge of shooting
/// </summary>
/// <param name="dt"></param>
void Player::shooting(float dt, GamePlay& game)
{
	if (m_weapon) //if holding a weapon, try shoot. This line is necessary since if the player tries to shoot with no weapon active, the function points to null and crashes the game.
	{
		m_weapon->tryFire(dt,*this,game); // *this passes this (the player) to the weapon
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
			m_weapon = std::make_unique<Melee>(&m_meleeStats); // Creates Melee Weapon instance
			currentWeapon = "Fists";
		}
		else if (t_weaponType == weaponType::short_range) // If you select a melee weapon
		{
			m_weapon = std::make_unique<ShortRange>(&m_shortStats);
			currentWeapon = "Short Spell";
		}
		else if (t_weaponType == weaponType::medium_range)
		{
			m_weapon = std::make_unique<MediumRange>(&m_mediumStats);
			currentWeapon = "Medium Spell";
		}
		else if (t_weaponType == weaponType::long_range)
		{
			m_weapon = std::make_unique<LongRange>(&m_longStats);
			currentWeapon = "Long Spell";
		}
		m_weaponSprite.setTexture(m_weapon->getTxt()); // Takes texture of current weapon (in this case melee in the melee class)
		sf::Vector2i txtSize = { (int)m_weaponSprite.getTexture().getSize().x, (int)m_weaponSprite.getTexture().getSize().y }; // gets the size of the texture
		m_weaponSprite.setTextureRect(sf::IntRect({ 0,0 }, { txtSize.x, txtSize.y })); // sets the texture rectangle to the size of the texture - so you can actually see it
		m_weaponSprite.setOrigin({ txtSize.x / 2.0f, txtSize.y / 2.0f }); // sets texture position to the middle of the texture. Will be different later
	}
}

/// <summary>
/// This is in charge of sending the movement vector to the correct collision checkers
/// </summary>
/// <param name="movement"></param>
/// <param name="level"></param>
void Player::moveWithCollisions(sf::Vector2f movement, Level& level)
{
	float absX = std::abs(movement.x); // x movement made positive
	float absY = std::abs(movement.y); // y movement made positive

	if (absX > absY) // if x movement is bigger than y movement
	{
		moveAxis(movement.x, 0.0f, level); // perform x movement first
		moveAxis(0.0f, movement.y, level); // then y
	}
	else
	{
		moveAxis(0.0f, movement.y, level);
		moveAxis(movement.x, 0.0f, level);
	}
}

/// <summary>
/// This goes through collision checkers
/// </summary>
/// <param name="dx"></param>
/// <param name="dy"></param>
/// <param name="level"></param>
void Player::moveAxis(float dx, float dy, Level& level)
{
	if (dx != 0) // if x movement isnt 0
	{
		setPosition(getPosition() + sf::Vector2f({ dx, dy })); // move the player

		sf::FloatRect box = getBoundingBox(); // get the hitbox of the player
		int tileSize = 100; // one tile is 100 pixels

		int leftTile = (int)std::floor((box.position.x / tileSize)); // tile to the left of player - floor makes sure its an integer
		int topTile = (int)std::floor(box.position.y / tileSize); // tile above the player
		int rightTile = (int)std::floor((box.position.x + box.size.x - 0.001f) / tileSize); // tile to the right of the player the -0.001 is for an offset
		int bottomTile = (int)std::floor((box.position.y + box.size.y - 0.001f) / tileSize); // tile below the player
		
		for (int y = topTile; y <= bottomTile; y++) // go through the tiles surrounding player
		{
			for (int x = leftTile; x <= rightTile; x++)
			{
				if (level.isSolid({ x,y }) == true) // if theres a wall - perform movement correction (take the player out of the wall)
				{
					if (dx > 0) box.position.x = x * tileSize - box.size.x/1.95f; // if moving right, set player to the left edge of the right tile
					else if (dx < 0) box.position.x = x * tileSize + tileSize + box.size.x/1.95f; // if moving left, set player to right edge of the left tile

					setPosition({ box.position.x, getPosition().y }); // set new position - now fixed away from the wall
				}
				if (level.returnTile({ (float)x,(float)y }) == 1)
				{
					takeDamage(2);
				}
			}
		}

	}

	if (dy != 0) // if y movement isnt 0 - same as x
	{
		setPosition(getPosition() + sf::Vector2f({ dx, dy }));

		sf::FloatRect box = getBoundingBox();
		int tileSize = 100;

		int leftTile = (int)std::floor((box.position.x / tileSize));
		int topTile = (int)std::floor(box.position.y / tileSize);
		int rightTile = (int)std::floor((box.position.x + box.size.x - 0.001f) / tileSize);
		int bottomTile = (int)std::floor((box.position.y + box.size.y - 0.001f) / tileSize);

		for (int y = topTile; y <= bottomTile; y++)
		{
			for (int x = leftTile; x <= rightTile; x++)
			{
				if (level.isSolid({ x,y }) == true)
				{
					if (dy > 0) box.position.y = y * tileSize - box.size.y/1.95f; // if moving down
					else if (dy < 0) box.position.y = y * tileSize + tileSize + box.size.y/1.95f; // if moving up

					setPosition({ getPosition().x, box.position.y});
				}
				if (level.returnTile({ (float)x,(float)y }) == 1)
				{
					takeDamage(2);
				}
			}
		}
	}
}

void Player::startRoll(sf::Vector2f direction)
{
	if (m_rollCooldownTimer > 0)
	{
		return;
	}
	if (m_isRolling)
	{
		return;
	}
	m_isRolling = true;
	m_rollTimer = 0.0f;

	//normalize direction
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (length != 0)
	{
		m_rollDirection = direction / length;
	}
	m_rollCooldownTimer = m_rollCooldown;

}

void Player::tryBuyWeaponUpgrade(WeaponUpgradeType t_type, weaponType t_weapon)
{
	int cost = m_weaponUpgrades.getCost(t_type,t_weapon);
	if (cost > m_playerSouls)
	{
		return;
	}
	m_playerSouls -= cost;
	m_weaponUpgrades.levelUp(t_type, t_weapon);
	recalculateStats();
}

void Player::tryBuyPlayerUpgrade(PlayerUpgradeType t_type)
{
	int cost = m_playerUpgrades.getCost(t_type);
	if (cost > m_playerSouls)
	{
		return;
	}
	m_playerSouls -= cost;
	m_playerUpgrades.levelUp(t_type);
	recalculateStats();
}

void Player::recalculateStats()
{
	m_playerUpgrades.applyPlayerUpgrades(m_playerStats); 
	m_weaponUpgrades.ApplyUpgrades(m_meleeStats, weaponType::melee);
	m_weaponUpgrades.ApplyUpgrades(m_shortStats, weaponType::short_range);
	m_weaponUpgrades.ApplyUpgrades(m_mediumStats, weaponType::medium_range);
	m_weaponUpgrades.ApplyUpgrades(m_longStats, weaponType::long_range);
}

void Player::updateReputation()
{
	m_reputation = 0;

	for (size_t w = 0; w < 4; ++w)
	{
		for (size_t u = 0; u < 4; ++u)
		{
			m_reputation += m_weaponUpgrades.getLevel((WeaponUpgradeType)u, (weaponType)w); // for every spell upgrade level, add reputation
		}
	}

	for (size_t u = 0; u < 5; ++u)
	{
		m_reputation -= m_playerUpgrades.getLevel((PlayerUpgradeType)u) * 2; // for every player upgrade, take reputation away
	}

	if (m_reputation < 0) // if reputation is negative, turn the player red
	{
		m_playerSprite.setColor(sf::Color(255, 255 + std::min(255, (m_reputation * 10)), 255 + std::min(255, (m_reputation * 10)), 255));
		m_playerHorns.setColor(sf::Color(255, 255, 255, 0 + std::min(255,(m_reputation * -20))));
		m_playerHalo.setColor(sf::Color::Transparent);
	}

	if (m_reputation > 0)
	{
		m_playerSprite.setColor(sf::Color::White);
		m_playerHalo.setColor(sf::Color(255, 255, 255, 0 + std::min(255, (m_reputation * 20))));
		m_playerHorns.setColor(sf::Color::Transparent);
	}
}
