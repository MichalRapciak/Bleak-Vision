#include "Enemy.h"
#include "Level.h"
#include "Player.h"

Enemy::Enemy() : m_enemySprite(m_enemyTexture)
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
