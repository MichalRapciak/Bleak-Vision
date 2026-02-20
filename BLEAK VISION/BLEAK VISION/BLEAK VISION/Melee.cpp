#include "Melee.h"
#include "Player.h"
#include "Enemy.h"
#include "Collisions.h"
#include <iostream>

/// <summary>
/// Function in charge of the weapon shooting
/// </summary>
void Melee::fire(Entity& entity, GamePlay& game)
{
	float rotationRadians = entity.getSprite().getRotation().asRadians() - 1.5708f;
	sf::Vector2f facingDirection;
	facingDirection.x = std::cos(rotationRadians);
	facingDirection.y = std::sin(rotationRadians);
	sf::Vector2f attackCenter = entity.getPosition() + facingDirection * (m_stats->getRange() / 2.f);
	sf::FloatRect attackBox({ attackCenter.x - m_stats->getRange() / 2.0f , attackCenter.y - m_stats->getRange() / 2.0f }, { m_stats->getRange(), m_stats->getRange() });
	HitInfo hit;
	hit.entity = &entity;
	hit.area = attackBox;
	hit.damage = m_stats->getDamage();
	Collisions::getInstance().addHit(hit);
}

