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
Player::Player() : m_playerSprite(m_playerTexture), m_weaponSprite(m_weaponTxt)
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
	m_playerHealth = 20;
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
		m_playerMovement = m_playerVelocity * dt; // Multiply by delta time - time between frames - to make sure movement is always at constant speed
		moveWithCollisions(m_playerMovement, level);
		m_playerSprite.setPosition(m_playerPosition);
		if (m_weapon) // if a weapon is created, keep it glued to the player
		{
			m_weaponSprite.setPosition({ m_playerPosition.x, m_playerPosition.y });
			m_weaponSprite.setRotation(m_playerSprite.getRotation());
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
		m_playerAim = t_mousePos;
		m_playerSprite.setRotation(sf::degrees(facingDir));
	}
}

/// <summary>
/// This function is in charge of shooting
/// </summary>
/// <param name="dt"></param>
void Player::shooting(float dt, Game& game)
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
			m_weapon = std::make_unique<Melee>(); // Creates Melee Weapon instance
		}
		else if (t_weaponType == weaponType::short_range) // If you select a melee weapon
		{
			m_weapon = std::make_unique<ShortRange>();
		}
		else if (t_weaponType == weaponType::medium_range)
		{
			m_weapon = std::make_unique<MediumRange>();
		}
		else if (t_weaponType == weaponType::long_range)
		{
			m_weapon = std::make_unique<LongRange>();
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
			}
		}
	}
}
