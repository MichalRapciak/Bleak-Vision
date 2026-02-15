#pragma once
#include "StatModifiers.h"

struct WeaponStats
{
	float cooldown; // cooldown between weapon shots/hits (fireRate), in seconds
	float projectileSpeed; // speed of projectile sent by the weapon
	float damage; // damage of the projectile/hit by the weapon
	float range; // range of the projectile/hit by the weapon

	StatModifier cooldownMod;
	StatModifier projMod;
	StatModifier damageMod;
	StatModifier rangeMod;

	float getCooldown() const
	{
		return (cooldown + cooldownMod.flat) * (1.0f + cooldownMod.percent); // returns cooldown after stat modifications
	}
	float getDamage() const
	{
		return (damage + damageMod.flat) * (1.0f + damageMod.percent);
	}
	float getProjSpeed() const
	{
		return (projectileSpeed + projMod.flat) * (1.0f + projMod.percent);
	}
	float getRange() const
	{
		return (range + rangeMod.flat) * (1.0f + rangeMod.percent);
	}
};
