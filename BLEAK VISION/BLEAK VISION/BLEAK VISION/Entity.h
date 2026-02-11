#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity() = default;
	virtual ~Entity() = default;

	virtual sf::FloatRect getBoundingBox() const = 0;
	virtual float getHealth() const = 0;
	virtual void takeDamage(float amount) = 0;

private:


};