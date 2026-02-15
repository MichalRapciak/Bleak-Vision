#include "Melee.h"
#include "Player.h"
#include "Collisions.h"
#include <iostream>

/// <summary>
/// Function in charge of the weapon shooting
/// </summary>
void Melee::fire(Player& player, GamePlay& game)
{
	float rotationRadians = player.getSprite().getRotation().asRadians() - 1.5708f;
	sf::Vector2f facingDirection;
	facingDirection.x = std::cos(rotationRadians);
	facingDirection.y = std::sin(rotationRadians);
	sf::Vector2f attackCenter = player.getPosition() + facingDirection * (m_stats->getRange() / 2.f);
	sf::FloatRect attackBox({ attackCenter.x - m_stats->getRange() / 2.0f , attackCenter.y - m_stats->getRange() / 2.0f }, { m_stats->getRange(), m_stats->getRange() });
	HitInfo hit;
	hit.entity = &player;
	hit.area = attackBox;
	hit.damage = m_stats->getDamage();
	// DEBUG BOX FOR WEAPON ATTACK AREA
	/*
	m_debugBox.setSize({m_weaponRange, m_weaponRange});
	m_debugBox.setOrigin({ m_weaponRange / 2.f, m_weaponRange / 2.0f });
	m_debugBox.setPosition({ player.getPosition() + facingDirection * (m_weaponRange / 2.0f)});
	m_debugBox.setFillColor(sf::Color::Transparent);
	m_debugBox.setOutlineColor(sf::Color::Blue);
	m_debugBox.setOutlineThickness(4.0f);
	std::cout << "shooting\n";
		*/
	Collisions::getInstance().addHit(hit);
}

