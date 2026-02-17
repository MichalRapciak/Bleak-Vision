#pragma once
#include "StatModifiers.h"

struct PlayerStats
{
	float m_maxHealth = 0.f;
	float m_walkSpeed = 0.f;
	float m_sprintSpeed = 0.f;
	float m_acceleration = 0.f;
	float m_regen = 0.f;

	StatModifier healthMod;
	StatModifier walkMod;
	StatModifier sprintMod;
	StatModifier accelMod;
	StatModifier regenMod;

	float getHealth() const
	{
		return (m_maxHealth + healthMod.flat) * (1.0f + healthMod.percent); // returns health after stat modifications
	}
	float getWalkSpeed() const
	{
		return (m_walkSpeed + walkMod.flat) * (1.0f + walkMod.percent);
	}
	float getSprintSpeed() const
	{
		return (m_sprintSpeed + sprintMod.flat) * (1.0f + sprintMod.percent);
	}
	float getAccel() const
	{
		return (m_acceleration + accelMod.flat) * (1.0f + accelMod.percent);
	}
	float getRegen() const
	{
		return (m_regen + regenMod.flat) * (1.0f + regenMod.percent);
	}
};
