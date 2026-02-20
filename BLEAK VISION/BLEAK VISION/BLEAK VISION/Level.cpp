#include "Level.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include "GamePlay.h"
#include <random>

Level::Level() : m_levelBG(m_levelTXT)
{
	initialiseArrays();
	initialiseMap();
	srand(time(nullptr)); // sets up random seed
	m_waves.push_back({30, 0, 0, 20}); // enemies to spawn, enemies spawned, enemies killed
	currentWaveIndex = 0;
}

Level::~Level()
{
}

/// <summary>
/// This function initializes the sprite visible in the background
/// </summary>
void Level::initialiseMap()
{
		if (!m_levelTXT.loadFromFile("ASSETS/LEVEL/level1bg.png"))
	{
		std::cout << "Can't load background" << std::endl;
	}
	m_levelBG.setTexture(m_levelTXT);
	m_levelBG.setPosition({ 0, 0 });
	m_levelBG.setTextureRect(sf::IntRect({ 0,0 }, { 5000,5000 }));
}

void Level::update(GamePlay& game)
{
	Wave& wave = m_waves[currentWaveIndex];
	wave.enemiesKilled = game.getEnemiesKilled();
	if (wave.enemiesSpawned < wave.enemiesToSpawn)
	{
		spawnEnemies(game);

	}
	if (wave.enemiesKilled >= wave.enemiesToSpawn && currentWaveIndex < 10)
	{
		game.resetEnemiesKilled();
		currentWaveIndex++;
		m_waves.push_back({30 + 15 * (currentWaveIndex),0,0,20 + 10 * currentWaveIndex});
	}

}

/// <summary>
/// This function loads the tilemap (stored in a .txt file) into the system
/// </summary>
void Level::initialiseArrays()
{
	std::ifstream level1{ "ASSETS/LEVEL/level1.txt" }; // open level1.txt
	if (!level1.is_open()) std::cout << "Error loading level file" << std::endl;

	for (int i = 0; i != Y_BOXES; ++i) { // loop to go through every i (y coordinate) in file
		for (int j = 0; j != X_BOXES; ++j) { // loop to go through every j (x coordinate) in file
			level1 >> levelGrid1[i][j]; // writes the value from level1 to levelGrid
		}
	}
}

/// <summary>
/// This function is used to get the current tile entity is in
/// </summary>
/// <param name="t_pos"></param>
/// <returns></returns>
int Level::returnTile(sf::Vector2f t_pos)
{
	int xTile = static_cast<int>(t_pos.x / 100); // Current position is divided by 100 as 1 tile = 100 pixels
	int yTile = static_cast<int>(t_pos.y / 100);
	tile = levelGrid1[yTile][xTile];
	return tile;
}

bool Level::isSolid(sf::Vector2i t_pos)
{
	tile = levelGrid1[t_pos.y][t_pos.x];
	if (tile == 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Level::spawnEnemies(GamePlay& game)
{
	Wave& wave = m_waves[currentWaveIndex];
	if (game.getEnemyCount() < wave.enemiesAliveMax)
	{
		for (int y = 0; y != Y_BOXES; y++)
		{
			for (int x = 0; x != X_BOXES; x++)
			{
				tile = levelGrid1[y][x];
				if (tile == 2)
				{
					randomNo = (rand() % 500) + 1;
					if (randomNo == 1)
					{
						game.spawnEnemy({ x * 100.0f, y * 100.0f });
						wave.enemiesSpawned++;
					}
				}
			}
		}
	}
}
