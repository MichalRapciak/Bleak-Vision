#include "Level.h"

Level::Level() : m_levelBG(m_levelTXT)
{
	if (!m_levelTXT.loadFromFile("ASSETS/LEVEL/floor bg.png"))
	{
	}
	m_levelBG.setTexture(m_levelTXT);
	m_levelBG.setTextureRect(sf::IntRect({ 0,0 }, { 1920,1080 }));
	m_levelBG.setPosition({0,0});
}

Level::~Level()
{
}
