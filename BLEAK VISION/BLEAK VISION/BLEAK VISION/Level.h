#pragma once
#include "SFML/Graphics.hpp"

class Level
{
public:
	Level();
	~Level();
	sf::Sprite getLevelBG() { return m_levelBG; }

private:
	sf::Sprite m_levelBG;
	sf::Texture m_levelTXT;
};