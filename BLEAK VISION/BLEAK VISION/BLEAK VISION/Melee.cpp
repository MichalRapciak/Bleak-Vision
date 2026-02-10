#include "Melee.h"
#include <iostream>

/// <summary>
/// Function in charge of the weapon shooting
/// </summary>
void Melee::fire()
{
	std::cout << "shooting\n";
}

float Melee::getRange() const
{
	return m_weaponRange;
}

float Melee::getDamage() const
{
	return m_weaponDamage;
}

float Melee::getAmmo() const
{
	return m_weaponAmmo;
}

