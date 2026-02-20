#pragma once
#include "PlayerStats.h"
#include "PlayerUpgradeLevels.h"
#include "PlayerUpgradeType.h"
#include "StatModifiers.h"

class PlayerUpgrades
{
public:
	void levelUp(PlayerUpgradeType type)
	{
		levels[(size_t)type]++;
	}

	void applyPlayerUpgrades(PlayerStats& stats)
	{
		stats.healthMod.flat = 10.f * getLevel(PlayerUpgradeType::MaxHealth);
		stats.walkMod.percent = 0.05f * getLevel(PlayerUpgradeType::WalkSpeed);
		stats.sprintMod.percent = 0.05f * getLevel(PlayerUpgradeType::SprintSpeed);
		stats.accelMod.percent = 0.05f * getLevel(PlayerUpgradeType::Acceleration);
		stats.regenMod.flat = 1.f * getLevel(PlayerUpgradeType::Regen);
	}

	int getLevel(PlayerUpgradeType type)
	{
		return levels[(size_t)type];
	}

	int getCost(PlayerUpgradeType type)
	{
		int level = getLevel(type);
		return baseCost + (3 * level);
	}

private:
	std::array<int, (size_t)PlayerUpgradeType::COUNT> levels{};
	int baseCost = 3;

};