#pragma once
#include "WeaponUpgradeType.h"

struct WeaponUpgradeLevels
{
	std::array<int, static_cast<size_t>(WeaponUpgradeType::COUNT)> levels{}; //array of int level for every weapon upgrade type
};