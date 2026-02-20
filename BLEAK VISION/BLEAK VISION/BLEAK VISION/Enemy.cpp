#include "Enemy.h"
#include "Level.h"
#include "Player.h"
#include <random>
#include "Weapon.h"
#include "Melee.h"
#include "ShortRange.h"
#include "MediumRange.h"
#include "LongRange.h"

Enemy::Enemy(int wave) : m_enemySprite(m_enemyTexture), m_weaponSprite(m_weaponTxt)
{
	if (!m_enemyTexture.loadFromFile("Assets/Player/playerplaceholder.png", false, sf::IntRect({ 0,0 }, { 200, 200 }))) // if texture doesnt load, output text
	{
		std::cout << "Texture not loaded." << std::endl;
	}
	m_enemyPosition = { 2300,1900 };
	m_enemySprite.setTexture(m_enemyTexture);
	m_enemySprite.setTextureRect(sf::IntRect({ 0,0 }, { 200,200 }));
	m_enemySprite.setOrigin({ 100,100 });
	m_enemySprite.setScale({ 0.3f,0.3f });
	m_enemySprite.setColor(sf::Color::Red);
	m_enemySprite.setPosition(m_enemyPosition);

	m_meleeStats = { 1.0f - (0.05f * wave), 0.f, 3.f + (3.f * wave), 50.f + (20.f * wave)}; // cooldown - speed - damage - range
	m_shortStats = { 0.80f - (0.05f * wave), 600.f + (50.0f * wave), 4.f + (4.f * wave), 300.f + (25.f * wave)};
	m_mediumStats = { 2.0f - (0.05f * wave), 900.f + (50.0f * wave), 8.f + (4.f * wave), 500.f + (25.f * wave)};
	m_longStats = { 3.5f - (0.05f * wave), 1600.f + (50.0f * wave), 16.f + (4.f * wave), 2000.f + (25.f * wave) };
	m_enemyHealth = 20 + (5.f * wave);
	m_enemySprintSpeed = 140 + (20.f * wave);

	pickRandomWeapon();
}

Enemy::~Enemy()
{

}



/// <summary>
/// Function used to update player position
/// </summary>
/// <param name="dt"></param>
void Enemy::update(float dt, Level& level, Player& player)
{
	if (!isDead)
	{
		if (m_enemyHealth <= 0)
		{
			player.addSoul();
			isDead = true;
		}
		m_enemyMovement = m_enemyVelocity * dt; // Multiply by delta time - time between frames - to make sure movement is always at constant speed
		moveWithCollisions(m_enemyMovement, level);
		m_enemySprite.setPosition(m_enemyPosition);
		if (m_weapon) // if a weapon is created, keep it glued to the player
		{
			m_weaponSprite.setPosition({ m_enemyPosition.x, m_enemyPosition.y });
			m_weaponSprite.setRotation(m_enemySprite.getRotation());
			m_weaponSprite.setColor(sf::Color::Red);
			m_weapon->updateCooldown(dt);
		}

	}
}

/// <summary>
/// Function used to update player aiming
/// </summary>
/// <param name="t_mousePos"></param>
/// <param name="facingDir"></param>
void Enemy::updateAim(sf::Vector2f t_playerPos, float facingDir)
{
	if (!isDead)
	{
		m_enemyAim = t_playerPos;
		m_enemySprite.setRotation(sf::degrees(facingDir));
	}
}

/// <summary>
/// This function is in charge of shooting
/// </summary>
/// <param name="dt"></param>
void Enemy::shooting(float dt, GamePlay& game, sf::Vector2f playerPos, Level& level)
{
	if (m_weapon && hasLineOfSight(playerPos, level) == true) //if holding a weapon and you have a line of sight, try shoot.
	{
		m_weapon->tryFire(dt, *this, game); // *this passes this (the enemy) to the weapon
	}
	else
	{
	}
}

/// <summary>
/// This is in charge
/// </summary>
/// <param name="movement"></param>
/// <param name="level"></param>
void Enemy::moveWithCollisions(sf::Vector2f movement, Level& level)
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

void Enemy::moveAxis(float dx, float dy, Level& level)
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
					if (dx > 0) box.position.x = x * tileSize - box.size.x / 1.95f; // if moving right, set player to the left edge of the right tile
					else if (dx < 0) box.position.x = x * tileSize + tileSize + box.size.x / 1.95f; // if moving left, set player to right edge of the left tile

					setPosition({ box.position.x, getPosition().y }); // set new position - now fixed away from the wall
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
					if (dy > 0) box.position.y = y * tileSize - box.size.y / 1.95f; // if moving down
					else if (dy < 0) box.position.y = y * tileSize + tileSize + box.size.y / 1.95f; // if moving up

					setPosition({ getPosition().x, box.position.y });
				}
			}
		}
	}
}

void Enemy::pickRandomWeapon()
{
	randomNo = (rand() % 40) + 1;
	if (randomNo < 25)
	{
		m_weapon = std::make_unique<Melee>(&m_meleeStats); // Creates Melee Weapon instance
		m_weaponType = weaponType::melee;
	}
	else if (randomNo < 35)
	{
		m_weapon = std::make_unique<ShortRange>(&m_shortStats);
		m_weaponType = weaponType::short_range;
	}
	else if (randomNo < 39)
	{
		m_weapon = std::make_unique<MediumRange>(&m_mediumStats);
		m_weaponType = weaponType::medium_range;
	}
	else if (randomNo <= 41)
	{
		m_weapon = std::make_unique<LongRange>(&m_longStats);
		m_weaponType = weaponType::long_range;
	}
	m_weaponSprite.setTexture(m_weapon->getTxt()); // Takes texture of current weapon (in this case melee in the melee class)
	sf::Vector2i txtSize = { (int)m_weaponSprite.getTexture().getSize().x, (int)m_weaponSprite.getTexture().getSize().y }; // gets the size of the texture
	m_weaponSprite.setTextureRect(sf::IntRect({ 0,0 }, { txtSize.x, txtSize.y })); // sets the texture rectangle to the size of the texture - so you can actually see it
	m_weaponSprite.setOrigin({ txtSize.x / 2.0f, txtSize.y / 2.0f }); // sets texture position to the middle of the texture. Will be different later
}

bool Enemy::hasLineOfSight(sf::Vector2f playerPos, Level& level)
{
	sf::Vector2f direction = playerPos - m_enemyPosition; // get direction of line of sight
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y); // get the distance bullet has to travel

	direction /= length; // normalize the direction

	float checkSize = 25.0f; // check every 1/4 of a box ( box is 100px)
	sf::Vector2f currentCheck = m_enemyPosition; // current point being checked

	for (float travelled = 0; travelled < length; travelled += checkSize) // loop to check boxes on the way to player
	{
		sf::Vector2i tile = { (int)currentCheck.x / 100, (int)currentCheck.y / 100 }; // current tile

		if (level.isSolid({ tile.x, tile.y }) == true) // if current tile is wall
		{
			return false; // no line of sight
		}
		currentCheck += direction * checkSize; // change current check to the next point

	}

	return true;
}
