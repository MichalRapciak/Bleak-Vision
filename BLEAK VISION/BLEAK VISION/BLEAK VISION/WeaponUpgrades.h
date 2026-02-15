#pragma once

#include "WeaponStats.h"
#include "StatModifiers.h"
#include "UpgradeLevels.h"
#include "WeaponType.h"

class WeaponUpgrades
{
public:

	void levelUpDamage(weaponType& t_weapon)
	{
		if (t_weapon == weaponType::melee)
		{
			melee.damageLevel++;
		}
		if (t_weapon == weaponType::short_range)
		{
			shortRange.damageLevel++;
		}
		if (t_weapon == weaponType::medium_range)
		{
			mediumRange.damageLevel++;
		}
		if (t_weapon == weaponType::long_range)
		{
			longRange.damageLevel++;
		}
	}

	void levelUpCooldown(weaponType& t_weapon)
	{
		if (t_weapon == weaponType::melee)
		{
			melee.cooldownLevel++;
		}
		if (t_weapon == weaponType::short_range)
		{
			shortRange.cooldownLevel++;
		}
		if (t_weapon == weaponType::medium_range)
		{
			mediumRange.cooldownLevel++;
		}
		if (t_weapon == weaponType::long_range)
		{
			longRange.cooldownLevel++;
		}
	}

	void levelUpProj(weaponType& t_weapon)
	{
		if (t_weapon == weaponType::melee)
		{
			melee.projSpeedLevel++;
		}
		if (t_weapon == weaponType::short_range)
		{
			shortRange.projSpeedLevel++;
		}
		if (t_weapon == weaponType::medium_range)
		{
			mediumRange.projSpeedLevel++;
		}
		if (t_weapon == weaponType::long_range)
		{
			longRange.projSpeedLevel++;
		}
	}

	void levelUpRange(weaponType& t_weapon)
	{
		if (t_weapon == weaponType::melee)
		{
			melee.rangeLevel++;
		}
		if (t_weapon == weaponType::short_range)
		{
			shortRange.rangeLevel++;
		}
		if (t_weapon == weaponType::medium_range)
		{
			mediumRange.rangeLevel++;
		}
		if (t_weapon == weaponType::long_range)
		{
			longRange.rangeLevel++;
		}
	}

	void ApplyUpgrades(WeaponStats& stats, const UpgradeLevels& levels)
	{
		stats.damageMod.flat += 4.0f * levels.damageLevel;
		stats.cooldownMod.percent -= 0.05f * levels.cooldownLevel;
		stats.projMod.percent += 0.1f * levels.projSpeedLevel;
		stats.rangeMod.percent += 0.1 * levels.rangeLevel;
	}





private:
	StatModifier m_damage;
	StatModifier m_cooldown;
	StatModifier m_bulletSpeed;
	StatModifier m_range;
	UpgradeLevels melee;
	UpgradeLevels shortRange;
	UpgradeLevels mediumRange;
	UpgradeLevels longRange;





};