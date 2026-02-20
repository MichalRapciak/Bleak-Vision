#pragma once
#include <SFML/Graphics.hpp>
#include "WeaponType.h"
#include "WeaponUpgradeType.h"
#include "PlayerUpgradeType.h"

enum class SkillCategory
{
	SkillMenu,
	Weapon,
	Health
};

class Player;
class WeaponUpgrades;

class SkillTree
{
public:
	SkillTree(Player& player);
	~SkillTree();

	void initialise(sf::Font& t_font);
	void update(sf::Time& t_deltaTime, sf::RenderWindow& t_window);
	void processInput(sf::Event& t_event, sf::RenderWindow& t_window);
	void render(sf::RenderWindow& t_window);
	void skillTreeUpdate(sf::Time& t_deltaTime, sf::RenderWindow& t_window);
	void weaponTreeUpdate(sf::Time& t_deltaTime, sf::RenderWindow& t_window);
	void healthTreeUpdate(sf::Time& t_deltaTime, sf::RenderWindow& t_window);
	void skillTreeRender(sf::RenderWindow& t_window);
	void weaponTreeRender(sf::RenderWindow& t_window);
	void healthTreeRender(sf::RenderWindow& t_window);
	void setWeaponUpgrades(WeaponUpgrades& upgrades) { m_weaponUpgrades = &upgrades; }
	WeaponUpgradeType getWeaponUpRequest() { return m_requestedWeaponUpType; }
	weaponType requestedWeapon() { return m_requestedWeapon; }
	bool hasWeaponUpRequest() { return m_weaponUpRequested; }
	PlayerUpgradeType getPlayerUpRequest() { return m_requestedPlayerUpType; }
	bool hasPlayerUpRequest() { return m_playerUpRequested; }


protected:
	static const int m_skillTreeButtonCount = 3;
	static const int m_weaponUpgradeButtonCount = 4;
	static const int m_playerUpgradeButtonCount = 5;
	sf::Texture m_buttonTxt;
	std::vector<sf::Sprite> m_buttonSprite;
	std::vector<sf::Text> m_skillTreeText;
	// Sprites and text for the weapon ugprades
	std::vector<sf::Sprite> m_meleeSprite;
	std::vector<sf::Text> m_meleeText;
	std::vector<sf::Sprite> m_shortSprite;
	std::vector<sf::Text> m_shortText;
	std::vector<sf::Sprite> m_mediumSprite;
	std::vector<sf::Text> m_mediumText;
	std::vector<sf::Sprite> m_longSprite;
	std::vector<sf::Text> m_longText;
	// sprites and text for player upgrades
	std::vector<sf::Sprite> m_playerUpgradeSprite;
	std::vector<sf::Text> m_playerUpgradeText;
	std::vector<sf::Sprite> m_playerUpgButton;
	std::vector<sf::Text> m_playerUpgTxt;

	sf::Sprite m_backToSkillsSprite;
	sf::Text m_backToSkillsText;
	sf::Text m_levelAndCost;
	sf::Text m_souls;

	float m_yOffset{ 0.0f }; // where should the buttons start on y axis
	float m_xOffset{ 0.0f }; // where should buttons start on x axis
	float m_yWeaponOffset{ 0.0f }; // same but for the weapon menu
	float m_xWeaponOffset{ 0.0f };
	float m_buttonSpacing{ 0.0f }; // space between buttons
	float m_buttonWidth{ 0.0f }; // width of button
	float m_buttonHeight{ 0.0f }; // height of button

	sf::Font m_font;
	
	SkillCategory m_currentCategory = SkillCategory::SkillMenu;

	sf::Sprite m_skillBackground;
	sf::Texture m_skillBackgroundTexture;

private:
	sf::View m_skillTreeView;
	weaponType m_requestedWeapon = weaponType::melee;
	WeaponUpgrades* m_weaponUpgrades = nullptr;
	WeaponUpgradeType m_requestedWeaponUpType = WeaponUpgradeType::weaponCooldown;
	bool m_weaponUpRequested = false;
	PlayerUpgradeType m_requestedPlayerUpType = PlayerUpgradeType::MaxHealth;
	bool m_playerUpRequested = false;

	bool m_previousMouseState = false;

	bool isMouseOverButton(int index, sf::Vector2f mousePos, weaponType weapon);
	Player& m_player;

};


