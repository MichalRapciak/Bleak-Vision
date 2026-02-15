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
	//sf::RectangleShape getDebugBox() const override { return m_debugBox; } //debug box to show weapon hit area

private:
	//sf::RectangleShape m_debugBox;
	float m_weaponAmmo = 0;

	virtual void fire(Player& player, GamePlay& game) override; // only the weapon class decides if the current weapon type is allowed to fire

};