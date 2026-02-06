#include "PlayerController.h"
#include "Player.h"

PlayerController::PlayerController(Player& player) : m_player(player)
{
}
PlayerController::~PlayerController()
{
}


void PlayerController::playerMovement(const sf::Event t_event, bool isPressed)
{
	if (isPressed == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) // These check if a key is pressed, then accelerate the player
		{
			m_speedVector.y -= m_player.getSpeed();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			m_speedVector.y += m_player.getSpeed();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			m_speedVector.x -= m_player.getSpeed();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			m_speedVector.x += m_player.getSpeed();
		}
	}
	if (m_speedVector.x > m_player.getTopSpeed()) // These statements cap velocity at player's max speed
	{
		m_speedVector.x = m_player.getTopSpeed();
	}
	else if (m_speedVector.x < -(m_player.getTopSpeed()))
	{
		m_speedVector.x = -m_player.getTopSpeed();
	}
	if (m_speedVector.y > m_player.getTopSpeed())
	{
		m_speedVector.y = m_player.getTopSpeed();
	}
	else if (m_speedVector.y < -(m_player.getTopSpeed()))
	{
		m_speedVector.y = -m_player.getTopSpeed();
	}
}

void PlayerController::playerIdle(bool isPressed)
{
	if (isPressed == false)
	{
		if (m_speedVector.x > -0.5 && m_speedVector.x < 0.5) //these two if statements make sure player is stationary and not "bouncing"
		{
			m_speedVector.x = 0;
		}
		if (m_speedVector.y > -0.5 && m_speedVector.y < 0.5)
		{
			m_speedVector.y = 0;
		}
		if (m_speedVector.x < 0) //these if statements decelerate the player so he's not constantly accelerating
		{
			m_speedVector.x += 0.1;
		}
		else if (m_speedVector.x > 0)
		{
			m_speedVector.x -= 0.1;
		}
		if (m_speedVector.y < 0)
		{
			m_speedVector.y += 0.1;
		}
		else if (m_speedVector.y > 0)
		{
			m_speedVector.y -= 0.1;
		}
	}
	m_newPos = m_player.getPosition() + m_speedVector; // update new position to add the velocity
	m_player.setPosition(m_newPos); // update the old position to new position
	std::cout << m_speedVector.x << " , " << m_speedVector.y << std::endl; // debugging text output to see current velocity
}
