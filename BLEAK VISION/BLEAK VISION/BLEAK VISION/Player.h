#pragma once
#include <SFML/Graphics.hpp>
#include "WeaponType.h"
#include <iostream>
#include "Entity.h"
#include "WeaponStats.h"
#include "WeaponUpgrades.h"
#include "WeaponUpgradeType.h"
#include "PlayerUpgrades.h"
#include "PlayerStats.h"
#include <memory>

class Weapon;
class GamePlay;
class Level;

class Player : public Entity
{
public:
	Player();
	~Player();



	sf::Vector2f getPosition() { return m_playerPosition; }
	sf::Sprite getSprite() { return m_playerSprite; }
	void setPlayerTexture(sf::Texture t_texture) { m_playerTexture = t_texture; }
	void setPosition(sf::Vector2f t_location) { m_playerPosition = t_location; m_playerSprite.setPosition(m_playerPosition); }
	sf::Vector2f getVelocity() { return m_playerVelocity; }
	void setVelocity(sf::Vector2f t_velocity) { m_playerVelocity = t_velocity; }

	float getAcceleration() { return m_playerStats.getAccel(); }
	float getWalkSpeed() { return m_playerStats.getWalkSpeed(); }
	float getSprintSpeed() { return m_playerStats.getSprintSpeed(); }
	float getHealth() const override { return m_playerStats.getHealth(); }
	float getRegen() { return m_playerStats.getRegen(); }
	void addSoul() { m_playerSouls++; }
	int getSouls() { return m_playerSouls; }

	sf::FloatRect getBoundingBox() const override { return sf::FloatRect({ m_playerPosition.x - 25,m_playerPosition.y - 25 }, { 50,50 }); }
	void takeDamage(float amount) override { m_playerHealth -= amount; }
	sf::Vector2f getPlayerAim() { return m_playerAim; }


	void setPlayerAim(sf::Vector2f t_mousePos) { m_playerAim = t_mousePos; }
	void updateAim(sf::Vector2f t_mousePos, float facingDir);
	void update(float dt, Level& level);
	void shooting(float dt, GamePlay& game);
	void equipWeapon(weaponType t_weaponType);
	sf::Sprite getWeaponSprite() { return m_weaponSprite; }
	//Weapon* getWeapon() const { if (m_weapon) { return m_weapon.get(); } else {} } // This is to get the debug box for melee attack area
	void moveWithCollisions(sf::Vector2f movement, Level& level);
	void moveAxis(float dx, float dy, Level& level);

	void tryBuyWeaponUpgrade(WeaponUpgradeType t_type, weaponType t_weapon);
	void tryBuyPlayerUpgrade(PlayerUpgradeType t_type);
	int getWeaponUpgradeLevel(WeaponUpgradeType t_type, weaponType t_weapon) { return m_weaponUpgrades.getLevel(t_type, t_weapon); }
	int getWeaponUpgradeCost(WeaponUpgradeType t_type, weaponType t_weapon) { return m_weaponUpgrades.getCost(t_type, t_weapon); }
	int getPlayerUpgLvl(PlayerUpgradeType t_type) { return m_playerUpgrades.getLevel(t_type); }
	int getPlayerUpgCost(PlayerUpgradeType t_type) { return m_playerUpgrades.getCost(t_type); }
	void recalculateStats();
	
	WeaponStats m_meleeStats;
	WeaponStats m_shortStats;
	WeaponStats m_mediumStats;
	WeaponStats m_longStats;
	WeaponUpgrades m_weaponUpgrades;

private:
	sf::Sprite m_playerSprite;
	sf::Texture m_playerTexture;
	sf::Vector2f m_playerPosition;
	sf::Vector2f m_playerMovement;
	sf::Vector2f m_playerVelocity{ 0.0,0.0 };
	sf::Vector2f m_playerAim{ 0, 0 }; // coordinates where player is aiming

	float m_playerHealth = 0;
	int m_playerSouls = 0;
	PlayerStats m_playerStats;
	PlayerUpgrades m_playerUpgrades;

	bool isDamaged = false;
	std::unique_ptr<Weapon> m_weapon; // Creates a pointer to a weapon
	sf::Sprite m_weaponSprite;
	sf::Texture m_weaponTxt;
	bool isDead = false;


};