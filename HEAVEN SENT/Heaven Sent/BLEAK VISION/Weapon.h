#pragma once
#include "SFML/Graphics.hpp"
#include "HitInfo.h"
#include "WeaponStats.h"

class Player;
class Entity;
class GamePlay;

class Weapon
{
public:
	Weapon(WeaponStats* stats) : m_stats(stats), m_timer(0.0f) {}
	virtual ~Weapon() = default;

	void tryFire(float dt, Entity& entity, GamePlay& game);
	void updateCooldown(float dt);
	const sf::Texture& getTxt() const { return m_weaponTxt; } // I declare this here so I can set it when creating a weapon
	sf::Texture m_weaponTxt;

protected:
	WeaponStats* m_stats;
	float m_cooldown = 1.0f; // cooldown between hits
	float m_timer = 0.0f; // timer for the cooldown
	bool m_readyToShoot = true;
private:
	virtual void fire(Entity& entity, GamePlay& game) = 0; // Used by weapon type to fire
};

