#pragma once
#include <SFML/Graphics.hpp>
class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void initialise(sf::Font& t_font);
	void update(sf::Time& t_deltaTime, sf::Window& t_window);
	void render(sf::RenderWindow& t_window);

protected:
	
	static const int m_buttonCount = 3;
	sf::Texture m_buttonTxt;
	std::vector<sf::Sprite> m_buttonSprite;
	std::vector<sf::Text> m_text;
	sf::Font m_font;

	float m_yOffset{ 0.0f };
	float m_xOffset{ 0.0f };
	float m_buttonSpacing{ 0.0f };
	float m_buttonWidth{ 0.0f };
	float m_buttonHeight{ 0.0f };
};
