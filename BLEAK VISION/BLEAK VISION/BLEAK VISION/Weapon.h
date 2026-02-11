#pragma once
#include "SFML/Graphics.hpp"
#include "HitInfo.h"

class Player;
class Game;

class Weapon
{
public:
	Weapon(float cooldown) : m_cooldown(cooldown), m_timer(0.0f) {}
	virtual ~Weapon() = default;

	void tryFire(float dt, Player& player, Game& game);
	void updateCooldown(float dt);
	virtual float getRange() const = 0; // These functions are virtual so I can reference them in the different weapon types
	virtual float getDamage() const = 0;
	virtual float getAmmo() const = 0;
	const sf::Texture& getTxt() const { return m_weaponTxt; } // I declare this here so I can set it when creating a weapon
	sf::Texture m_weaponTxt;
	//virtual sf::RectangleShape getDebugBox() const { return sf::RectangleShape(); };

protected:
	float m_cooldown = 1.0f; // cooldown between hits
	float m_timer = 0.0f; // timer for the cooldown
	bool m_readyToShoot = true;
private:
	//virtual void fire(Player& player) = 0; // Used by weapon type to fire
	virtual void fire(Player& player, Game& game) = 0; // Used by weapon type to fire
};

