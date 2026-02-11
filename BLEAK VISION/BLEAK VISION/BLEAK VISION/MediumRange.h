#pragma once
#include "Weapon.h"

class MediumRange : public Weapon
{
public:
	MediumRange() : Weapon(0.4f) { // the 1 is the default cooldown. I can't initialize it here since it would not be able to read it in time, it will be initialized in a separate class later
		if (m_weaponTxt.loadFromFile("ASSETS/WEAPON/mProjPlaceholder.png"))
		{
		}
	}
	virtual float getRange() const override; // the overrides make sure the player uses the version of the function inside the weapon type
	virtual float getDamage() const override;
	virtual float getAmmo() const override;

private:
	float m_weaponRange = 800;
	float m_weaponDamage = 16;
	float m_weaponBulletSpeed = 900;
	float m_weaponAmmo = 8;

	virtual void fire(Player& player, Game& game) override; // only the weapon class decides if the current weapon type is allowed to fire

};