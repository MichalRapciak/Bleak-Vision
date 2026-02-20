#pragma once

#include "WeaponStats.h"
#include "StatModifiers.h"
#include "WeaponUpgradeLevels.h"
#include "WeaponType.h"
#include "WeaponUpgradeType.h"

class WeaponUpgrades
{
public:

	void levelUp(WeaponUpgradeType t_type, weaponType t_weapon)
	{
		auto& w = m_weapons[static_cast<size_t>(t_weapon)]; // pointer to m_weapons vector for (t_weapon) weaponType

		w.levels[static_cast<size_t>(t_type)]++; // add a level to upgrade type t_type

	}

	void ApplyUpgrades(WeaponStats& stats, weaponType t_weapon)
	{
		stats.damageMod.flat = 2.0f * m_weapons[(size_t)t_weapon].levels[static_cast<size_t>(WeaponUpgradeType::weaponDamage)];
		stats.cooldownMod.percent = 0.025f * m_weapons[(size_t)t_weapon].levels[static_cast<size_t>(WeaponUpgradeType::weaponCooldown)];
		stats.projMod.percent = 0.025f * m_weapons[(size_t)t_weapon].levels[static_cast<size_t>(WeaponUpgradeType::weaponProjSpeed)];
		stats.rangeMod.percent = 0.05f * m_weapons[(size_t)t_weapon].levels[static_cast<size_t>(WeaponUpgradeType::weaponRange)];
	}

	int getCost(WeaponUpgradeType t_type, weaponType t_weapon)
	{
		const auto& w = m_weapons[static_cast<size_t>(t_weapon)]; // pointer to m_weapons vector for (t_weapon) weaponType

		int level = w.levels[static_cast<size_t>(t_type)]; // gets the level for current upgrade type 

		return baseCost + (2 * level);
	}

	int getLevel(WeaponUpgradeType type, weaponType weapon)
	{
		return m_weapons[(size_t)weapon].levels[(size_t)type]; // this is basically eg.: m_weapons[melee].levels[cooldown]()
	}

private:
	std::array<WeaponUpgradeLevels, static_cast<size_t>(weaponType::COUNT)> m_weapons;

	int baseCost = 3;



};