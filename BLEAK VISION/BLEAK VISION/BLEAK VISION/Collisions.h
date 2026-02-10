#pragma once
#include <SFML/Graphics.hpp>
#include "HitInfo.h"
#include "Entity.h"
#include <iostream>

/// <summary>
/// This is the class in charge of all collisions
/// </summary>
class Collisions
{
public:
	static Collisions& getInstance() // Makes sure only one Collisions instance is always running
	{
		static Collisions instance;
		return instance;
	}

	void addHit(const HitInfo& hit)
	{
		m_hits.push_back(hit);
	}
	void update(const std::vector<Entity*>& entities) //create vector of entities
	{
		for (const auto& hit : m_hits) // go through the hits vector
		{
			for (auto* entity : entities) // go through the entities vector
			{
				if (entity == hit.entity) // if a hit is in range of the entity that shot it
				{
					continue; //Do nothing
				}
				if (hit.area.findIntersection(entity->getBoundingBox())) // if the hit intersects an entity
				{
					entity->takeDamage(hit.damage); // given entity takes damage
				}
				else
				{
					continue; // do nothing
				}
			}
		}
		m_hits.clear(); // clear all hits after they're processeed

	}

private:
	std::vector<HitInfo> m_hits;

	Collisions() = default; // privately constructed
	Collisions(const Collisions&) = delete;
	Collisions operator=(const Collisions&) = delete;
};