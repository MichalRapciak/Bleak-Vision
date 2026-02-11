#pragma once
#include "Weapon.h"

class ShortRange : public Weapon
{
public:
	ShortRange() : Weapon(0.15f) { // the 1 is the default cooldown. I can't initialize it here since it would not be able to read it in time, it will be initialized in a separate class later
		if (m_weaponTxt.loadFromFile("ASSETS/WEAPON/sProjPlaceholder.png"))
		{
		}
	}
	virtual float getRange() const override; // the overrides make sure the player uses the version of the function inside the weapon type
	virtual float getDamage() const override;
	virtual float getAmmo() const override;

private:
	float m_weaponRange = 400;
	float m_weaponDamage = 8;
	float m_weaponBulletSpeed = 600;
	float m_weaponAmmo = 12;

	virtual void fire(Player& player, Game& game) override; // only the weapon class decides if the current weapon type is allowed to fire

};