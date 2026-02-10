#pragma once
#include "SFML/Graphics.hpp"

class Weapon
{
public:
	Weapon(float cooldown) : m_cooldown(cooldown), m_timer(0.0f) {}
	virtual ~Weapon() = default;

	void tryFire(float dt);
	virtual float getRange() const = 0; // These functions are virtual so I can reference them in the different weapon types
	virtual float getDamage() const = 0;
	virtual float getAmmo() const = 0;
	const sf::Texture& getTxt() const { return m_weaponTxt; } // I declare this here so I can set it when creating a weapon
	sf::Texture m_weaponTxt;
protected:
	float m_cooldown = 1.0f;
	float m_timer = 0.0f;
	bool m_readyToShoot = true;
private:
	virtual void fire() = 0;



};

