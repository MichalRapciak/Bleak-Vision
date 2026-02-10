#include "Weapon.h"
#include <iostream>

/// <summary>
/// This function checks if the weapon is currently able to shoot
/// </summary>
/// <param name="dt"></param>
void Weapon::tryFire(float dt)
{
	if (!m_readyToShoot) // if it's not ready to shoot, keep adding time passed to the cooldown timer
	{
		m_timer += dt;
		if (m_timer >= m_cooldown) // if the timer has collected more seconds than the cooldown of the weapon
		{
			m_readyToShoot = true; // tell yourself it's ready to shoot
			m_timer = 0.0f; // reset the cooldown
		}
	}
	if (m_readyToShoot) // if it's ready to shoot
	{
		fire(); // go to the weapon type and use the fire function there
		m_readyToShoot = false; // after the weapon fires, start cooldown again
	}
}


