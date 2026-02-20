#include "SkillTree.h"
#include "Game.h"
#include "WeaponUpgrades.h"
#include <iostream>

SkillTree::SkillTree(Player& player) : 
	m_skillBackground(m_skillBackgroundTexture),
	m_backToSkillsSprite(m_buttonTxt),
	m_backToSkillsText(m_font),
	m_player(player),
	m_levelAndCost(m_font),
	m_souls(m_font),
	m_skillTreeView(sf::FloatRect({ 0,0 }, { 1920,1080 }))
{
}

SkillTree::~SkillTree()
{
}

/// <summary>
/// Initializes font, textures and placement of buttons/text
/// </summary>
/// <param name="t_font"></param>
void SkillTree::initialise(sf::Font& t_font)
{
	m_font = t_font;
	if (!m_skillBackgroundTexture.loadFromFile("ASSETS/IMAGES/skillbg.png"))
	{
		std::cout << "Error loading skill screen background\n";
	}
	m_skillBackgroundTexture.setRepeated(true); // might not be needed if the final background is a full screen image
	m_skillBackground.setTexture(m_skillBackgroundTexture);
	m_skillBackground.setTextureRect(sf::IntRect({ 0, 0 }, { static_cast<int>(1920), static_cast<int>(1080) })); // sets it to the size of the w
	m_skillBackground.setPosition({ 0, 0 });
	if (!m_buttonTxt.loadFromFile("ASSETS/IMAGES/button.png"))
	{
		std::cout << "Error loading button texture" << std::endl;
	}

	sf::IntRect txtRect;
	txtRect.position = { 0,0 };
	txtRect.size = { static_cast<int>(m_buttonTxt.getSize().x) , static_cast<int>(m_buttonTxt.getSize().y) };

	m_buttonWidth = 300;
	m_buttonHeight = 100;
	m_yOffset = 200;
	m_xOffset = (m_skillTreeView.getSize().x / 2) - m_buttonWidth / 2;
	m_yWeaponOffset = 200;
	m_xWeaponOffset = (m_skillTreeView.getSize().x / 5)  - m_buttonWidth/2;
	m_buttonSpacing = 120;
	int textDropOffset = 15;

	// setting up text outputs
	sf::String m_Texts[] = { "Spell Upgrades", "Player Upgrades" , "Back To Game"};
	sf::String m_meleeTexts[] = { "Melee Swing Speed" , "" , "Melee Damage", "Melee Range"};
	sf::String m_shortTexts[] = { "Short Spell Fire Rate" , "Short Spell Speed" , "Short Spell Damage", "Short Spell Range" };
	sf::String m_mediumTexts[] = { "Mid Spell Fire Rate" , "Mid Spell Speed" , "Mid Spell Damage", "Mid Spell Range" };
	sf::String m_longTexts[] = { "Long Spell Fire Rate" , "Long Spell Speed" , "Long Spell Damage", "Long Spell Range" };
	sf::String m_playTexts[] = { "Max Health" , "Walk Speed" , "Sprint Speed" , "Acceleration" , "Health Regen" };
	sf::String m_exitText = "Back to Previous Menu";

	/// setting up button to go back to the main skills menu
	{
		m_backToSkillsSprite.setTexture(m_buttonTxt);
		m_backToSkillsSprite.setTextureRect(txtRect);
		m_backToSkillsSprite.setPosition({ m_xOffset, 800.f });
		sf::Vector2u txtSize = m_buttonTxt.getSize();
		m_backToSkillsSprite.setScale({ m_buttonWidth / txtSize.x, m_buttonHeight / txtSize.y });
		m_backToSkillsText.setFont(m_font);
		m_backToSkillsText.setString(m_exitText);
		m_backToSkillsText.setFillColor(sf::Color::White);
		m_backToSkillsText.setCharacterSize(20);
		sf::FloatRect textSize = m_backToSkillsText.getGlobalBounds();
		float exitOffset = (m_buttonWidth - textSize.size.x) / (2);
		m_backToSkillsText.setPosition({ m_xOffset + exitOffset, 800.f + textDropOffset });
	}

	// main skills menu buttons
	for (int i = 0; i < m_skillTreeButtonCount; i++)
	{
		auto& sprite = m_buttonSprite.emplace_back(m_buttonTxt);
		sprite.setTextureRect(txtRect);
		sprite.setPosition({ m_xOffset, m_buttonSpacing * i + m_yOffset });
		sf::Vector2u txtSize = m_buttonTxt.getSize();
		sprite.setScale({ m_buttonWidth / txtSize.x, m_buttonHeight / txtSize.y });

		auto& text = m_skillTreeText.emplace_back(m_font);
		text.setFont(m_font);
		text.setString(m_Texts[i]);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(30);
		sf::FloatRect textSize = text.getGlobalBounds();
		float textOffset = (m_buttonWidth - textSize.size.x) / (2);
		text.setPosition({ m_xOffset + textOffset, m_buttonSpacing * i + m_yOffset + textDropOffset });
	}
	// melee upgrade buttons
	for (int i = 0; i < m_weaponUpgradeButtonCount; i++)
	{
		auto& sprite = m_meleeSprite.emplace_back(m_buttonTxt);
		sprite.setTextureRect(txtRect);
		sprite.setPosition({ m_xWeaponOffset, m_buttonSpacing * i + m_yWeaponOffset });
		sf::Vector2u txtSize = m_buttonTxt.getSize();
		sprite.setScale({ m_buttonWidth / txtSize.x, m_buttonHeight / txtSize.y });

		auto& text = m_meleeText.emplace_back(m_font);
		text.setFont(m_font);
		text.setString(m_meleeTexts[i]);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(20);
		sf::FloatRect textSize = text.getGlobalBounds();
		float textOffset = (m_buttonWidth - textSize.size.x) / (2);
		text.setPosition({ m_xWeaponOffset + textOffset, m_buttonSpacing * i + m_yWeaponOffset + textDropOffset });
	}
	// short spell buttons
	for (int i = 0; i < m_weaponUpgradeButtonCount; i++)
	{
		auto& sprite = m_shortSprite.emplace_back(m_buttonTxt);
		sprite.setTextureRect(txtRect);
		sprite.setPosition({ 2 * m_xWeaponOffset + m_buttonWidth / 2, m_buttonSpacing * i + m_yWeaponOffset });
		sf::Vector2u txtSize = m_buttonTxt.getSize();
		sprite.setScale({ m_buttonWidth / txtSize.x, m_buttonHeight / txtSize.y });

		auto& text = m_shortText.emplace_back(m_font);
		text.setFont(m_font);
		text.setString(m_shortTexts[i]);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(20);
		sf::FloatRect textSize = text.getGlobalBounds();
		float textOffset = (m_buttonWidth - textSize.size.x) / (2);
		text.setPosition({ 2 * m_xWeaponOffset + textOffset + m_buttonWidth / 2, m_buttonSpacing * i + m_yWeaponOffset + textDropOffset });
	}
	// medium spell buttons
	for (int i = 0; i < m_weaponUpgradeButtonCount; i++)
	{
		auto& sprite = m_mediumSprite.emplace_back(m_buttonTxt);
		sprite.setTextureRect(txtRect);
		sprite.setPosition({ 3 * m_xWeaponOffset + m_buttonWidth, m_buttonSpacing * i + m_yWeaponOffset });
		sf::Vector2u txtSize = m_buttonTxt.getSize();
		sprite.setScale({ m_buttonWidth / txtSize.x, m_buttonHeight / txtSize.y });

		auto& text = m_mediumText.emplace_back(m_font);
		text.setFont(m_font);
		text.setString(m_mediumTexts[i]);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(20);
		sf::FloatRect textSize = text.getGlobalBounds();
		float textOffset = (m_buttonWidth - textSize.size.x) / (2);
		text.setPosition({ 3 * m_xWeaponOffset + textOffset + m_buttonWidth, m_buttonSpacing * i + m_yWeaponOffset + textDropOffset });
	}
	// long spell buttons
	for (int i = 0; i < m_weaponUpgradeButtonCount; i++)
	{
		auto& sprite = m_longSprite.emplace_back(m_buttonTxt);
		sprite.setTextureRect(txtRect);
		sprite.setPosition({ 4 * m_xWeaponOffset + m_buttonWidth * 1.5f, m_buttonSpacing * i + m_yWeaponOffset });
		sf::Vector2u txtSize = m_buttonTxt.getSize();
		sprite.setScale({ m_buttonWidth / txtSize.x, m_buttonHeight / txtSize.y });

		auto& text = m_longText.emplace_back(m_font);
		text.setFont(m_font);
		text.setString(m_longTexts[i]);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(20);
		sf::FloatRect textSize = text.getGlobalBounds();
		float textOffset = (m_buttonWidth - textSize.size.x) / (2);
		text.setPosition({ 4 * m_xWeaponOffset + textOffset + m_buttonWidth * 1.5f, m_buttonSpacing * i + m_yWeaponOffset + textDropOffset });
	}
	// player upgrade buttons
	for (int i = 0; i < m_playerUpgradeButtonCount; i++)
	{
		auto& sprite = m_playerUpgButton.emplace_back(m_buttonTxt);
		sprite.setTextureRect(txtRect);
		sprite.setPosition({ m_xOffset, m_buttonSpacing * i + m_yOffset });
		sf::Vector2u txtSize = m_buttonTxt.getSize();
		sprite.setScale({ m_buttonWidth / txtSize.x, m_buttonHeight / txtSize.y });

		auto& text = m_playerUpgTxt.emplace_back(m_font);
		text.setFont(m_font);
		text.setString(m_playTexts[i]);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(20);
		sf::FloatRect textSize = text.getGlobalBounds();
		float textOffset = (m_buttonWidth - textSize.size.x) / (2);
		text.setPosition({ m_xOffset + textOffset, m_buttonSpacing * i + m_yOffset + textDropOffset });
	}
	// souls display
	m_souls.setFont(m_font);
	m_souls.setFillColor(sf::Color::White);
	m_souls.setCharacterSize(60);
	m_souls.setPosition({ 120,120 });

}

/// <summary>
/// updates whichever menu you're in
/// </summary>
/// <param name="t_deltaTime"></param>
/// <param name="t_window"></param>
void SkillTree::update(sf::Time& t_deltaTime, sf::RenderWindow& t_window)
{
	sf::String soulsString = "Souls: " + std::to_string(m_player.getSouls());
	m_souls.setString(soulsString);

	switch (m_currentCategory)
	{
	case SkillCategory::SkillMenu:
		skillTreeUpdate(t_deltaTime, t_window);
		break;
	case SkillCategory::Weapon:
		weaponTreeUpdate(t_deltaTime, t_window);
		break;
	case SkillCategory::Health:
		healthTreeUpdate(t_deltaTime, t_window);
		break;
	}
}

void SkillTree::processInput(sf::Event& t_event, sf::RenderWindow& t_window)
{
	if (const auto resized = t_event.getIf<sf::Event::Resized>()) //debugging to see if window resizing works
	{
		sf::Vector2f visibleArea(sf::Vector2f(resized->size));
		m_skillTreeView.setSize(visibleArea);
		m_xOffset = (m_skillTreeView.getSize().x / 2) - m_buttonWidth / 2 ;
		m_xWeaponOffset = (m_skillTreeView.getSize().x / 5) - m_buttonWidth / 2;
		t_window.setView(m_skillTreeView);
	}
}

/// <summary>
/// rendering current menu
/// </summary>
/// <param name="t_window"></param>
void SkillTree::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_souls);
	switch (m_currentCategory)
	{
	case SkillCategory::SkillMenu:
		skillTreeRender(t_window);
		break;
	case SkillCategory::Weapon:
		weaponTreeRender(t_window);
		break;
	case SkillCategory::Health:
		healthTreeRender(t_window);
		break;
	}
	t_window.setView(m_skillTreeView);
}

void SkillTree::skillTreeUpdate(sf::Time& t_deltaTime, sf::RenderWindow& t_window)
{
	sf::Vector2f mouseLocation;
	mouseLocation = t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window));

	bool currentState = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

	for (int i = 0; i < m_skillTreeButtonCount; i++)
	{
		m_skillTreeText[i].setFillColor(sf::Color::White);
		m_buttonSprite[i].setColor(sf::Color::White);
		if (isMouseOverButton(i, mouseLocation, weaponType::melee) == true)
		{
			m_buttonSprite[i].setColor(sf::Color{ 100,100,100,255 });
			m_skillTreeText[i].setFillColor(sf::Color{ 75,75,75,255 });
			if (currentState && !m_previousMouseState)
			{
				if (i == 0) m_currentCategory = SkillCategory::Weapon;
				if (i == 1) m_currentCategory = SkillCategory::Health;
				if (i == 2) Game::currentState = GameState::GamePlay;
			}
		}
	}
	m_previousMouseState = currentState;
}

void SkillTree::weaponTreeUpdate(sf::Time& t_deltaTime, sf::RenderWindow& t_window)
{
	m_weaponUpRequested = false;
	sf::Vector2f mouseLocation;
	mouseLocation = t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window));
	m_levelAndCost.setFillColor(sf::Color::Transparent);

	bool currentState = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

	for (int i = 0; i < m_weaponUpgradeButtonCount; i++)
	{
		m_meleeText[i].setFillColor(sf::Color::White);
		m_meleeSprite[i].setColor(sf::Color::White);
		m_shortText[i].setFillColor(sf::Color::White);
		m_shortSprite[i].setColor(sf::Color::White);
		m_mediumText[i].setFillColor(sf::Color::White);
		m_mediumSprite[i].setColor(sf::Color::White);
		m_longText[i].setFillColor(sf::Color::White);
		m_longSprite[i].setColor(sf::Color::White);

		for (int j = 0; j < m_weaponUpgradeButtonCount; j++)
		{
			if (isMouseOverButton(i, mouseLocation, static_cast<weaponType>(j)) == true)
			{
				if (static_cast<weaponType>(j) == weaponType::melee)
				{
					m_meleeSprite[i].setColor(sf::Color{ 100,100,100,255 });
					m_meleeText[i].setFillColor(sf::Color{ 75,75,75,255 });
				
					sf::String levelandcost = "Level: " + std::to_string(m_player.getWeaponUpgradeLevel(static_cast<WeaponUpgradeType>(i), static_cast<weaponType>(j))) + " Cost: " + std::to_string(m_player.getWeaponUpgradeCost(static_cast<WeaponUpgradeType>(i), static_cast<weaponType>(j)));
					m_levelAndCost.setString(levelandcost);
					m_levelAndCost.setFillColor(sf::Color::White);
					m_levelAndCost.setCharacterSize(20);
					m_levelAndCost.setPosition({m_meleeText[i].getPosition().x, m_meleeText[i].getPosition().y + 40});
				}
				if (static_cast<weaponType>(j) == weaponType::short_range)
				{
					m_shortSprite[i].setColor(sf::Color{ 100,100,100,255 });
					m_shortText[i].setFillColor(sf::Color{ 75,75,75,255 });

					sf::String levelandcost = "Level: " + std::to_string(m_player.getWeaponUpgradeLevel(static_cast<WeaponUpgradeType>(i), static_cast<weaponType>(j))) + " Cost: " + std::to_string(m_player.getWeaponUpgradeCost(static_cast<WeaponUpgradeType>(i), static_cast<weaponType>(j)));
					m_levelAndCost.setString(levelandcost);
					m_levelAndCost.setFillColor(sf::Color::White);
					m_levelAndCost.setCharacterSize(20);
					m_levelAndCost.setPosition({ m_shortText[i].getPosition().x, m_shortText[i].getPosition().y + 40 });
				}
				if (static_cast<weaponType>(j) == weaponType::medium_range)
				{
					m_mediumSprite[i].setColor(sf::Color{ 100,100,100,255 });
					m_mediumText[i].setFillColor(sf::Color{ 75,75,75,255 });

					sf::String levelandcost = "Level: " + std::to_string(m_player.getWeaponUpgradeLevel(static_cast<WeaponUpgradeType>(i), static_cast<weaponType>(j))) + " Cost: " + std::to_string(m_player.getWeaponUpgradeCost(static_cast<WeaponUpgradeType>(i), static_cast<weaponType>(j)));
					m_levelAndCost.setString(levelandcost);
					m_levelAndCost.setFillColor(sf::Color::White);
					m_levelAndCost.setCharacterSize(20);
					m_levelAndCost.setPosition({ m_mediumText[i].getPosition().x, m_mediumText[i].getPosition().y + 40 });
				}
				if (static_cast<weaponType>(j) == weaponType::long_range)
				{
					m_longSprite[i].setColor(sf::Color{ 100,100,100,255 });
					m_longText[i].setFillColor(sf::Color{ 75,75,75,255 });

					sf::String levelandcost = "Level: " + std::to_string(m_player.getWeaponUpgradeLevel(static_cast<WeaponUpgradeType>(i), static_cast<weaponType>(j))) + " Cost: " + std::to_string(m_player.getWeaponUpgradeCost(static_cast<WeaponUpgradeType>(i), static_cast<weaponType>(j)));
					m_levelAndCost.setString(levelandcost);
					m_levelAndCost.setFillColor(sf::Color::White);
					m_levelAndCost.setCharacterSize(20);
					m_levelAndCost.setPosition({ m_longText[i].getPosition().x, m_longText[i].getPosition().y + 40 });
				}
				if (currentState && !m_previousMouseState)
				{
					m_requestedWeaponUpType = static_cast<WeaponUpgradeType>(i);
					m_requestedWeapon = static_cast<weaponType>(j);
					m_weaponUpRequested = true;
				}
			}
		}
	}

	m_backToSkillsText.setFillColor(sf::Color::White);
	m_backToSkillsSprite.setColor(sf::Color::White);

	if (mouseLocation.x > m_xOffset && mouseLocation.x < m_xOffset + m_buttonWidth)
	{
		if (mouseLocation.y > 800.f && mouseLocation.y < 800.f + m_buttonHeight)
		{
			m_backToSkillsSprite.setColor(sf::Color{ 100,100,100,255 });
			m_backToSkillsText.setFillColor(sf::Color{ 75,75,75,255 });
			if (currentState && !m_previousMouseState)
			{
				m_currentCategory = SkillCategory::SkillMenu;
			}
		}
	}
	

	m_previousMouseState = currentState;

}

void SkillTree::healthTreeUpdate(sf::Time& t_deltaTime, sf::RenderWindow& t_window)
{
	m_playerUpRequested = false;
	sf::Vector2f mouseLocation;
	mouseLocation = t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window));
	m_levelAndCost.setFillColor(sf::Color::Transparent);
	m_backToSkillsText.setFillColor(sf::Color::White);
	m_backToSkillsSprite.setColor(sf::Color::White);

	bool currentState = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);


	for (int i = 0; i < m_playerUpgradeButtonCount; i++)
	{
		m_playerUpgTxt[i].setFillColor(sf::Color::White);
		m_playerUpgButton[i].setColor(sf::Color::White);
		if (isMouseOverButton(i, mouseLocation, static_cast<weaponType>(0)) == true)
		{
			m_playerUpgButton[i].setColor(sf::Color{ 100,100,100,255 });
			m_playerUpgTxt[i].setFillColor(sf::Color{ 75,75,75,255 });

			sf::String levelandcost = "Level: " + std::to_string(m_player.getPlayerUpgLvl(static_cast<PlayerUpgradeType>(i))) + " Cost: " + std::to_string(m_player.getPlayerUpgCost(static_cast<PlayerUpgradeType>(i)));
			m_levelAndCost.setString(levelandcost);
			m_levelAndCost.setFillColor(sf::Color::White);
			m_levelAndCost.setCharacterSize(20);
			m_levelAndCost.setPosition({ m_playerUpgTxt[i].getPosition().x, m_playerUpgTxt[i].getPosition().y + 40 });

			if (currentState && !m_previousMouseState)
			{
				m_requestedPlayerUpType = static_cast<PlayerUpgradeType>(i);
				m_playerUpRequested = true;
			}
		}
	}

	if (mouseLocation.x > m_xOffset && mouseLocation.x < m_xOffset + m_buttonWidth)
	{
		if (mouseLocation.y > 800.f && mouseLocation.y < 800.f + m_buttonHeight)
		{
			m_backToSkillsSprite.setColor(sf::Color{ 100,100,100,255 });
			m_backToSkillsText.setFillColor(sf::Color{ 75,75,75,255 });
			if (currentState && !m_previousMouseState)
			{
				m_currentCategory = SkillCategory::SkillMenu;
			}
		}
	}
	m_previousMouseState = currentState;
}

void SkillTree::skillTreeRender(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_skillTreeButtonCount; i++)
	{
		t_window.draw(m_buttonSprite[i]);
		t_window.draw(m_skillTreeText[i]);
	}
}

void SkillTree::weaponTreeRender(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_weaponUpgradeButtonCount; i++)
	{
		t_window.draw(m_meleeSprite[i]);
		t_window.draw(m_meleeText[i]);
		t_window.draw(m_shortSprite[i]);
		t_window.draw(m_shortText[i]);
		t_window.draw(m_mediumSprite[i]);
		t_window.draw(m_mediumText[i]);
		t_window.draw(m_longSprite[i]);
		t_window.draw(m_longText[i]);
	}
	t_window.draw(m_backToSkillsSprite);
	t_window.draw(m_backToSkillsText);
	t_window.draw(m_levelAndCost);
}

void SkillTree::healthTreeRender(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_playerUpgradeButtonCount; i++)
	{
		t_window.draw(m_playerUpgButton[i]);
		t_window.draw(m_playerUpgTxt[i]);
	}
	t_window.draw(m_backToSkillsSprite);
	t_window.draw(m_backToSkillsText);
	t_window.draw(m_levelAndCost);
}

bool SkillTree::isMouseOverButton(int index, sf::Vector2f mousePos, weaponType weapon)
{
	if (m_currentCategory == SkillCategory::SkillMenu)
	{
		return m_buttonSprite[index].getGlobalBounds().contains(mousePos);
	}
	if (m_currentCategory == SkillCategory::Weapon)
	{	
		if (weapon == weaponType::melee) return m_meleeSprite[index].getGlobalBounds().contains(mousePos);
		if (weapon == weaponType::short_range) return m_shortSprite[index].getGlobalBounds().contains(mousePos);
		if (weapon == weaponType::medium_range) return m_mediumSprite[index].getGlobalBounds().contains(mousePos);
		if (weapon == weaponType::long_range) return m_longSprite[index].getGlobalBounds().contains(mousePos);
	}
	if (m_currentCategory == SkillCategory::Health)
	{
		return m_playerUpgButton[index].getGlobalBounds().contains(mousePos);
	}
	return false;
}
	
