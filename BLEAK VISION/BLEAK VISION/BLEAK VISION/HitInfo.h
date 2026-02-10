#pragma once
#include <SFML/Graphics.hpp>

class Entity;

/// <summary>
/// Struct with info about area being hit, and who is the one doing the hitting
/// </summary>
struct HitInfo
{
	sf::FloatRect area;
	float damage;
	Entity* entity;
};