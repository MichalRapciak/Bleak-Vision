#pragma once
#include "Weapon.h"

class Melee : public Weapon
{
public:
	Melee() : Weapon(0.5f) { // the 0.5 is the default cooldown. I can't initialize it here since it would not be able to read it in time, it will be initialized in a separate class later
		if (m_weaponTxt.loadFromFile("ASSETS/WEAPON/meleePlaceholder.png"))
		{
		}
	}
	virtual float getRange() const override; // the overrides make sure the player uses the version of the function inside the weapon type
	virtual float getDamage() const override;
	virtual float getAmmo() const override;
	//sf::RectangleShape getDebugBox() const override { return m_debugBox; } //debug box to show weapon hit area

private:
	//sf::RectangleShape m_debugBox;
	float m_weaponRange = 100;
	float m_weaponDamage = 10;
	float m_weaponAmmo = 0;

	virtual void fire(Player& player, Game& game) override; // only the weapon class decides if the current weapon type is allowed to fire

};