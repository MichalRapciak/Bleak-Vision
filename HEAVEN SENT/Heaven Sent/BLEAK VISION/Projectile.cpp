#include "Projectile.h"
#include "Collisions.h"
#include <iostream>
#include "Level.h"
#include "Enemy.h"

Projectile::Projectile(Entity* owner, const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& direction, float speed, float damage, float range) : m_projSprite(texture)
{
	setPosition(position);
	m_startPosition = position;
	m_projSprite.setPosition(m_position);
	m_projSprite.setTextureRect(sf::IntRect({ 0,0 }, { (int)texture.getSize().x,(int)texture.getSize().y }));
	m_projSprite.setOrigin({ texture.getSize().x / 2.0f,texture.getSize().y / 2.0f });
	m_speed = speed;
	m_baseDamage = damage;
	m_owner = owner;
	m_velocity = direction * m_speed;
	m_range = range;
	if (dynamic_cast<Enemy*>(owner))
	{
		m_projSprite.setColor(sf::Color::Green);
	}
}

Projectile::~Projectile()
{
}

void Projectile::update(float dt, Level& level)
{
	if (!m_isDead)
	{
		m_delta = m_position - m_startPosition;
		m_distanceTravelled = std::sqrt(m_delta.x * m_delta.x + m_delta.y * m_delta.y);
		m_damage = m_baseDamage;
		if (m_distanceTravelled >= m_range)
		{
			m_distanceOverRange = m_distanceTravelled - m_range;
			m_damageMultiplier = 1.0f - (0.001f * (m_distanceOverRange));
			m_damage = m_baseDamage * std::max(0.25f, m_damageMultiplier);
		}
		move(m_velocity * dt);
		if (level.isSolid({ (int)m_position.x / 100,(int)m_position.y / 100 }) == true)
		{
			m_isDead = true;
		}
		if (m_distanceTravelled > 3000)
		{
			m_isDead = true;
		}
		if (!m_isDead)
		{
			HitInfo hit;
			hit.area = getBoundingBox();
			hit.damage = m_damage;
			hit.entity = this;
			hit.ignore = m_owner;
			Collisions::getInstance().addHit(hit);
		}

	}
}

void Projectile::move(sf::Vector2f t_pos)
{
	setPosition(m_position += t_pos);
	m_projSprite.setPosition(m_position);
}
