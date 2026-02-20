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



	sf::Vector2f getPosition() const override { return m_playerPosition; }
	sf::Sprite getSprite() const override{ return m_playerSprite; }
	sf::Sprite getHalo() { return m_playerHalo; }
	sf::Sprite getHorns() { return m_playerHorns; }
	void setPlayerTexture(sf::Texture t_texture) { m_playerTexture = t_texture; }
	void setPosition(sf::Vector2f t_location) { m_playerPosition = t_location; m_playerSprite.setPosition(m_playerPosition); }
	sf::Vector2f getVelocity() { return m_playerVelocity; }
	void setVelocity(sf::Vector2f t_velocity) { m_playerVelocity = t_velocity; }

	float getAcceleration() { return m_playerStats.getAccel(); }
	float getWalkSpeed() { return m_playerStats.getWalkSpeed(); }
	float getSprintSpeed() { return m_playerStats.getSprintSpeed(); }
	float getHealth() const override { return m_playerHealth; }
	float getRegen() { return m_playerStats.getRegen(); }
	float getMaxHealth() { return m_playerStats.getHealth(); }
	void addSoul() { m_playerSouls++; enemiesKilled++; }
	void soulsCheat() { m_playerSouls++; }
	int getSouls() { return m_playerSouls; }
	bool getDead() { return isDead; }

	sf::FloatRect getBoundingBox() const override { return sf::FloatRect({ m_playerPosition.x - 20,m_playerPosition.y - 20 }, { 40,40 }); }
	void takeDamage(float amount) override { m_playerHealth -= amount; }
	sf::Vector2f getPlayerAim() { return m_playerAim; }

	int getEnemiesKilled() { return enemiesKilled; }
	void setEnemiesKilled(int num) { enemiesKilled = num; }
	void setPlayerAim(sf::Vector2f t_mousePos) { m_playerAim = t_mousePos; }
	void updateAim(sf::Vector2f t_mousePos, float facingDir);
	void update(float dt, Level& level);
	void shooting(float dt, GamePlay& game);
	void equipWeapon(weaponType t_weaponType);
	sf::Sprite getWeaponSprite() { return m_weaponSprite; }
	void moveWithCollisions(sf::Vector2f movement, Level& level);
	void moveAxis(float dx, float dy, Level& level);

	void startRoll(sf::Vector2f direction);
	int getReputation() { return m_reputation; }

	void tryBuyWeaponUpgrade(WeaponUpgradeType t_type, weaponType t_weapon);
	void tryBuyPlayerUpgrade(PlayerUpgradeType t_type);
	int getWeaponUpgradeLevel(WeaponUpgradeType t_type, weaponType t_weapon) { return m_weaponUpgrades.getLevel(t_type, t_weapon); }
	int getWeaponUpgradeCost(WeaponUpgradeType t_type, weaponType t_weapon) { return m_weaponUpgrades.getCost(t_type, t_weapon); }
	int getPlayerUpgLvl(PlayerUpgradeType t_type) { return m_playerUpgrades.getLevel(t_type); }
	int getPlayerUpgCost(PlayerUpgradeType t_type) { return m_playerUpgrades.getCost(t_type); }
	void recalculateStats();
	void updateReputation();
	
	WeaponStats m_meleeStats;
	WeaponStats m_shortStats;
	WeaponStats m_mediumStats;
	WeaponStats m_longStats;
	WeaponUpgrades m_weaponUpgrades;
	sf::String getCurrentWeapon() { return currentWeapon; }

private:
	sf::Sprite m_playerSprite;
	sf::Sprite m_playerHalo;
	sf::Texture m_playerHaloTxt;
	sf::Sprite m_playerHorns;
	sf::Texture m_playerHornsTxt;
	sf::Texture m_playerTexture;
	sf::Vector2f m_playerPosition;
	sf::Vector2f m_playerMovement;
	sf::Vector2f m_playerVelocity{ 0.0,0.0 };
	sf::Vector2f m_playerAim{ 0, 0 }; // coordinates where player is aiming

	bool m_isRolling = false;
	float m_rollTimer = 0.0f;
	float m_rollDuration = 0.5f;
	float m_rollSpeed = 150.f;
	sf::Vector2f m_rollDirection;
	float m_rollCooldown = 1.0f;
	float m_rollCooldownTimer = 0.f;

	std::string currentWeapon = "None";
	float m_playerHealth = 0;
	int m_playerSouls = 0;
	PlayerStats m_playerStats;
	PlayerUpgrades m_playerUpgrades;
	int enemiesKilled = 0;

	int m_reputation = 0;

	bool isDamaged = false;
	std::unique_ptr<Weapon> m_weapon; // Creates a pointer to a weapon
	sf::Sprite m_weaponSprite;
	sf::Texture m_weaponTxt;
	bool isDead = false;


};