#pragma once

#include "SFML/Graphics.hpp"
#include "GroupOfEnemies.h"
#include "PowerUp.h"
#include "ScoreText.h"
#include "PlayerGUI.h"
#include <set>

class GroupOfEnemies;

class PowerUp;

class StaminaBar;

class PowerUpBar;

class Player : public sf::Drawable
{
public:
	Player(float X, float Y);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void sprint();
	void disableSprint() { playerVelocity = 3.0f; }
	void regenerateStamina() { if (stamina < 10.0f) stamina += 0.1f; }

	float getStamina() const { return stamina; }

	float getPowerUp() const { return powerUp; }

	sf::Vector2f getPosition() const { return playerTexture.getPosition(); }

	void shootProjectile();
	void moveProjectiles(GroupOfEnemies& enemies, PowerUp& powerUp, ScoreText& score);
	void eraseProjectiles();

	bool checkIfDied(GroupOfEnemies& enemies);

	void checkIfPoweredUp(sf::RenderWindow& window, PowerUpBar& powerUpBar);

	void setPowerUp() { isPoweredUp = true; }
private:
	sf::RectangleShape playerTexture;

	const float textureHeight = 75.0f;
	const float textureWidth = 38.0f;
	const float projectileVelocity = 8.0f;
	float playerVelocity = 3.0f;

	bool isPoweredUp = false;

	int shootDelay = 50;
	int shootDelayTimer = shootDelay;

	std::set<std::size_t> projectileIndexesToErase;
	std::vector<std::pair<sf::CircleShape, std::string>> projectiles;

	std::string facingDirection = "up";

	float powerUp = 30.0f;
	float stamina = 10.0f;
	bool isStaminaRegenerated = true;

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

