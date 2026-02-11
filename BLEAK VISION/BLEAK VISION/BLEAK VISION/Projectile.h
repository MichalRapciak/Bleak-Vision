#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "HitInfo.h"

class Projectile : public Entity
{
public:
	Projectile(Entity* owner,
		const sf::Texture& texture,
		const sf::Vector2f& position,
		const sf::Vector2f& direction,
		float speed,
		float damage,
		float range);
	~Projectile();

	void update(float dt);
	void setPosition(sf::Vector2f t_position) { m_position = t_position; }
	void move(sf::Vector2f t_pos);

	bool getDead() const { return m_isDead; }
	int getDamage() const { return m_damage; }
	sf::Vector2f getPosition() { return m_position; }
	void setDead() { m_isDead = true; }

	float getHealth() const override { return 0; }
	sf::FloatRect getBoundingBox() const override { return m_projSprite.getGlobalBounds(); }
	void takeDamage(float amount) override { }
	sf::Sprite getSprite() { return m_projSprite; }

private:
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	Entity* m_owner;

	sf::Vector2f m_startPosition;
	sf::Vector2f m_delta;
	float m_distanceTravelled;
	float m_distanceOverRange;
	float m_range;
	float m_baseDamage;
	float m_damageMultiplier;
	float m_speed;
	float m_damage;
	bool m_isDead = false;
	sf::Sprite m_projSprite;

};