#include "PlayerController.h"
#include "WeaponType.h"
#include "Player.h"

PlayerController::PlayerController(Player& player) : m_player(player)
{
}
PlayerController::~PlayerController()
{
}

/// <summary>
/// Handling Input through Player Controller class, since within menus etc. you won't need to move the player it's good to keep these separate
/// </summary>
/// <param name="t_event"></param>
/// <param name="isPressed"></param>
void PlayerController::inputHandler(const sf::Event t_event)
{
	if (const auto keyPressed = t_event.getIf<sf::Event::KeyPressed>()) // This checks what key is pressed and tells the updater which action to do
	{
		if (keyPressed->scancode == sf::Keyboard::Scancode::W)
		{
			m_up = true;
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::S)
		{
			m_down = true;
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::A)
		{
			m_left = true;
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::D)
		{
			m_right = true;
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::LShift)
		{
			isSprinting = true;
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::Num1)
		{
			m_player.equipWeapon(weaponType::melee);
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::Num2)
		{
			m_player.equipWeapon(weaponType::short_range);
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::Num3)
		{
			m_player.equipWeapon(weaponType::medium_range);
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::Num4)
		{
			m_player.equipWeapon(weaponType::long_range);
		}
		if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
		{
			m_player.startRoll(m_speedVector);
		}
	}
	if (const auto keyReleased = t_event.getIf<sf::Event::KeyReleased>())
	{
		if (keyReleased->scancode == sf::Keyboard::Scancode::W) // These check what key is released, telling the updated to decelerate
		{
			m_up = false;
		}
		if (keyReleased->scancode == sf::Keyboard::Scancode::S)
		{
			m_down = false;
		}
		if (keyReleased->scancode == sf::Keyboard::Scancode::A)
		{
			m_left = false;
		}
		if (keyReleased->scancode == sf::Keyboard::Scancode::D)
		{
			m_right = false;
		}
		if (keyReleased->scancode == sf::Keyboard::Scancode::LShift)
		{
			isSprinting = false;
		}
	}
	if (const auto buttonPressed = t_event.getIf<sf::Event::MouseButtonPressed>())
	{
		isShooting = true;
	}
	if (const auto buttonReleased = t_event.getIf<sf::Event::MouseButtonReleased>())
	{
		isShooting = false;
	}
}


/// <summary>
/// updating player movement - can be turned off if within menus.
/// </summary>
/// <param name="isPressed"></param>
void PlayerController::update(float dt, GamePlay& game)
{
	if (m_up) // these 4 statements set player velocity in given direction
	{
		m_speedVector.y -= m_player.getAcceleration();
	}
	if (m_down)
	{
		m_speedVector.y += m_player.getAcceleration();
	}
	if (m_left)
	{
		m_speedVector.x -= m_player.getAcceleration();
	}
	if (m_right)
	{
		m_speedVector.x += m_player.getAcceleration();
	}
	//
	if (!isSprinting)  // These statements cap velocity at player's walk speed
	{
		if (m_speedVector.x > m_player.getWalkSpeed())
		{
			m_speedVector.x = m_player.getWalkSpeed();
		}
		else if (m_speedVector.x < -(m_player.getWalkSpeed()))
		{
			m_speedVector.x = -m_player.getWalkSpeed();
		}
		if (m_speedVector.y > m_player.getWalkSpeed())
		{
			m_speedVector.y = m_player.getWalkSpeed();
		}
		else if (m_speedVector.y < -(m_player.getWalkSpeed()))
		{
			m_speedVector.y = -m_player.getWalkSpeed();
		}
	}
	else // if sprinting, cap speed at sprint speed
	{
		if (m_speedVector.x > m_player.getSprintSpeed())
		{
			m_speedVector.x = m_player.getSprintSpeed();
		}
		else if (m_speedVector.x < -(m_player.getSprintSpeed()))
		{
			m_speedVector.x = -m_player.getSprintSpeed();
		}
		if (m_speedVector.y > m_player.getSprintSpeed())
		{
			m_speedVector.y = m_player.getSprintSpeed();
		}
		else if (m_speedVector.y < -(m_player.getSprintSpeed()))
		{
			m_speedVector.y = -m_player.getSprintSpeed();
		}
	}
	//
	if (isShooting)
	{
		m_player.shooting(dt, game);
	}
	//
	if (m_up == false && m_down == false && m_left == false && m_right == false) //these two if statements make sure player is not "vibrating" when the velocity is very small.
	{
		if (m_speedVector.x > -(m_speedNearlyZero) && m_speedVector.x < m_speedNearlyZero)
		{
			m_speedVector.x = 0;
		}
		if (m_speedVector.y > -(m_speedNearlyZero) && m_speedVector.y < m_speedNearlyZero)
		{
			m_speedVector.y = 0;
		}
	}
	//
	if (!m_left) //these if statements decelerate the player in a given direction when key is released
	{
		if (m_speedVector.x < 0) 
		{
			m_speedVector.x += m_playerDeceleration;
		}
	}
	if (!m_right)
	{
		if (m_speedVector.x > 0)
		{
			m_speedVector.x -= m_playerDeceleration;
		}
	}
	if (!m_up)
		if (m_speedVector.y < 0)
		{
			m_speedVector.y += m_playerDeceleration;
		}
	if (!m_down)
	{
		if (m_speedVector.y > 0)
		{
			m_speedVector.y -= m_playerDeceleration;
		}
	}
	m_player.setVelocity(m_speedVector); // sends the new velocity to the player where it's updated
}

/// <summary>
/// Calculating Player Aim and facing Direction sending it to the Player
/// </summary>
/// <param name="t_mouseWorld"></param>
void PlayerController::mouseAiming(sf::Vector2f t_mouseWorld)
{
	m_facingDirection = t_mouseWorld - m_player.getPosition(); // Get the direction vector by taking away player's position from the mouse cursor
	m_angleRadians = std::atan2(m_facingDirection.y, m_facingDirection.x); // Calculate the angle into radians
	m_angleDegrees = m_angleRadians * 180.0f / 3.14159265f; // calculate the radians into degrees
	m_angleDegrees += 90.f; // add an offset as the sprite is facing up by default
	m_player.updateAim(t_mouseWorld, m_angleDegrees); // send information to update player aim in the player class
}