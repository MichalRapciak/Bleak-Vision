#include "LongRange.h"
#include "Player.h"
#include <iostream>
#include "GamePlay.h"

/// <summary>
/// Function in charge of the weapon shooting
/// </summary>
void LongRange::fire(Player& player, GamePlay& game)
{
	float rotationRadians = player.getSprite().getRotation().asRadians() - 1.5708f;
	sf::Vector2f facingDirection;
	facingDirection.x = std::cos(rotationRadians);
	facingDirection.y = std::sin(rotationRadians);
	game.spawnProjectile(&player, player.getPosition(), facingDirection, m_stats->getProjSpeed(), m_stats->getDamage(), m_stats->getRange(), 3);
}

