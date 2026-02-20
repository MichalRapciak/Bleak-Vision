#pragma once
#include "Weapon.h"
#include "WeaponStats.h"

class MediumRange : public Weapon
{
public:
	MediumRange(WeaponStats* stats) : Weapon(stats)
	{
		if (m_weaponTxt.loadFromFile("ASSETS/WEAPON/midSpell.png"))
		{
		}
	}
private:
	float m_weaponAmmo = 8;

	virtual void fire(Entity& entity, GamePlay& game) override; // only the weapon class decides if the current weapon type is allowed to fire

};