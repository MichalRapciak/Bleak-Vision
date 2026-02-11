#include "Melee.h"
#include "Player.h"
#include "Collisions.h"
#include <iostream>

/// <summary>
/// Function in charge of the weapon shooting
/// </summary>
void Melee::fire(Player& player, Game& game)
{
	float rotationRadians = player.getSprite().getRotation().asRadians() - 1.5708;
	sf::Vector2f facingDirection;
	facingDirection.x = std::cos(rotationRadians);
	facingDirection.y = std::sin(rotationRadians);
	sf::Vector2f attackCenter = player.getPosition() + facingDirection * (m_weaponRange / 2.f);
	sf::FloatRect attackBox({ attackCenter.x - m_weaponRange / 2.0f , attackCenter.y - m_weaponRange / 2.0f }, {m_weaponRange, m_weaponRange});
	HitInfo hit;
	hit.entity = &player;
	hit.area = attackBox;
	hit.damage = m_weaponDamage;
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

float Melee::getRange() const
{
	return m_weaponRange;
}

float Melee::getDamage() const
{
	return m_weaponDamage;
}

float Melee::getAmmo() const
{
	return m_weaponAmmo;
}

