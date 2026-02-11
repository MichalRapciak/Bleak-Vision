#pragma once
#include <SFML/Graphics.hpp>

class Entity;

/// <summary>
/// Struct with info about area being hit, and who is the one doing the hitting
/// </summary>
struct HitInfo
{
	sf::FloatRect area; // area of the hit
	float damage; // damage of the hit
	Entity* entity; // the entity doing the hit
	Entity* ignore; // ignore these entities - this is specifically if entity doing the hit is a projectile, ignore the entity that shot it
};