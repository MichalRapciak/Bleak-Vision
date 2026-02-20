#pragma once
#include "Weapon.h"
#include "WeaponStats.h"

class LongRange : public Weapon
{
public:
	LongRange(WeaponStats* stats) : Weapon(stats)
	{
		if (m_weaponTxt.loadFromFile("ASSETS/WEAPON/LSpell.png"))
		{
		}
	}

private:
	float m_weaponAmmo = 4;

	virtual void fire(Entity& entity, GamePlay& game) override; // only the weapon class decides if the current weapon type is allowed to fire

};