#include "Projectile.h"
#include "Collisions.h"
#include <iostream>

Projectile::Projectile(Entity* owner, const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& direction, float speed, float damage, float range) : m_projSprite(texture)
{
	setPosition(position);
	m_startPosition = position;
	m_projSprite.setPosition(m_position);
	m_projSprite.setTextureRect(sf::IntRect({ 0,0 }, { 40,40 }));
	m_projSprite.setOrigin({ 20,20 });
	m_speed = speed;
	m_baseDamage = damage;
	m_owner = owner;
	m_velocity = direction * m_speed;
	m_range = range;
}

Projectile::~Projectile()
{
}

void Projectile::update(float dt)
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
		if (m_distanceTravelled > 3000)
		{
			m_isDead = true;
		}
		if (!m_isDead)
		{
			HitInfo hit;
			hit.area = getBoundingBox();
			hit.damage = m_damage;
			std::cout << m_damage << std::endl;
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
