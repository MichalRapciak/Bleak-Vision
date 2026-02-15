#pragma once
#include "Weapon.h"
#include "WeaponStats.h"

class ShortRange : public Weapon
{
public:
	ShortRange(WeaponStats* stats) : Weapon(stats) { // the 1 is the default cooldown. I can't initialize it here since it would not be able to read it in time, it will be initialized in a separate class later
		if (m_weaponTxt.loadFromFile("ASSETS/WEAPON/sProjPlaceholder.png"))
		{
		}
	}

private:
	float m_weaponAmmo = 12;

	virtual void fire(Player& player, GamePlay& game) override; // only the weapon class decides if the current weapon type is allowed to fire

};