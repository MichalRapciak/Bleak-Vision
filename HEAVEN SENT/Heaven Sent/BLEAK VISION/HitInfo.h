#pragma once
#include <SFML/Graphics.hpp>

class Entity;

/// <summary>
/// Struct with info about area being hit, and who is the one doing the hitting
/// </summary>
struct HitInfo
{
	sf::FloatRect area; // area of the hit
	float damage = 0; // damage of the hit
	Entity* entity = 0; // the entity doing the hit
	Entity* ignore = 0; // ignore these entities - this is specifically if entity doing the hit is a projectile, ignore the entity that shot it
};