#include "MediumRange.h"
#include "Player.h"
#include <iostream>
#include "Game.h"

/// <summary>
/// Function in charge of the weapon shooting
/// </summary>
void MediumRange::fire(Player& player, Game& game)
{
	float rotationRadians = player.getSprite().getRotation().asRadians() - 1.5708;
	sf::Vector2f facingDirection;
	facingDirection.x = std::cos(rotationRadians);
	facingDirection.y = std::sin(rotationRadians);
	game.spawnProjectile(&player, player.getPosition(), facingDirection, m_weaponBulletSpeed, m_weaponDamage, m_weaponRange, 2);
}

float MediumRange::getRange() const
{
	return m_weaponRange;
}

float MediumRange::getDamage() const
{
	return m_weaponDamage;
}

float MediumRange::getAmmo() const
{
	return m_weaponAmmo;
}

