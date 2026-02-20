#pragma once
#include "Weapon.h"
#include "WeaponStats.h"

class Melee : public Weapon
{
public:
	Melee(WeaponStats* stats) : Weapon(stats)
	{
		if (m_weaponTxt.loadFromFile("ASSETS/WEAPON/meleePlaceholder.png"))
		{
		}
	}
private:
	float m_weaponAmmo = 0;

	virtual void fire(Entity& entity, GamePlay& game) override; // only the weapon class decides if the current weapon type is allowed to fire

};