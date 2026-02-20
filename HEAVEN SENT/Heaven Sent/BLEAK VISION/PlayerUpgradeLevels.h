#pragma once
#include "PlayerUpgradeType.h"

struct PlayerUpgradeLevels
{
	std::array<int, static_cast<size_t>(PlayerUpgradeType::COUNT)> levels{};
};