#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "GamePlay.h"
#include "LicenseScreen.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "Help.h"
#include "SkillTree.h"
//#include "Player.h"
//#include "Enemy.h"
//#include "Level.h"

enum class
	GameState
{
	None,
	License,
	Splash,
	MainMenu,
	Help,
	GamePlay,
	SkillTree
};


class Game
{

public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
	static GameState currentState;

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void initialiseStates();

	sf::Font m_font;
	sf::RenderWindow m_window; // main SFML window

	LicenseScreen m_licenseScreen;
	SplashScreen m_splashScreen;
	MainMenu m_mainMenuScreen;
	Help m_helpScreen;
	std::unique_ptr<GamePlay> m_gamingScreen;
	std::unique_ptr<SkillTree> m_skillTree;

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP