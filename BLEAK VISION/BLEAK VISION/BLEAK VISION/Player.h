#pragma once
#include <SFML/Graphics.hpp>
#include "WeaponType.h"
#include <iostream>
#include "Entity.h"
#include <memory>

class Weapon;
class Game;

class Player : public Entity
{
public:
	Player();
	~Player();



	sf::Vector2f getPosition() { return m_playerPosition; }
	sf::Sprite getSprite() { return m_playerSprite; }
	void setPosition(sf::Vector2f t_location) { m_playerPosition = t_location; m_playerSprite.setPosition(m_playerPosition); }
	void setPlayerTexture(sf::Texture t_texture) { m_playerTexture = t_texture; }
	float getSpeed() { return m_playerSpeed; }
	sf::Vector2f getVelocity() { return m_playerVelocity; }
	void setVelocity(sf::Vector2f t_velocity) { m_playerVelocity = t_velocity; }
	float getTopSpeed() { return m_playerTopSpeed; }
	float getSprintSpeed() { return m_playerSprintSpeed; }
	float getHealth() const override { return m_playerHealth; }
	sf::FloatRect getBoundingBox() const override { return m_playerSprite.getGlobalBounds(); }
	void takeDamage(float amount) override { m_playerHealth -= amount; }
	sf::Vector2f getPlayerAim() { return m_playerAim; }
	void setPlayerAim(sf::Vector2f t_mousePos) { m_playerAim = t_mousePos; }
	void updateAim(sf::Vector2f t_mousePos, float facingDir);
	void update(float dt);
	void shooting(float dt, Game& game);
	void equipWeapon(weaponType t_weaponType);
	sf::Sprite getWeaponSprite() { return m_weaponSprite; }
	//Weapon* getWeapon() const { if (m_weapon) { return m_weapon.get(); } else {} }
	

private:
	sf::Sprite m_playerSprite;
	sf::Texture m_playerTexture;
	sf::Vector2f m_playerPosition;
	float m_playerSpeed = 15;
	float m_playerTopSpeed = 80;
	float m_playerSprintSpeed = 160;
	sf::Vector2f m_playerVelocity{ 0.0,0.0 };
	sf::Vector2f m_playerAim{ 0, 0 }; // coordinates where player is aiming
	float m_playerHealth = 0;
	bool isDamaged = false;
	std::unique_ptr<Weapon> m_weapon; // Creates a pointer to a weapon
	sf::Sprite m_weaponSprite;
	sf::Texture m_weaponTxt;
	bool isDead = false;
};