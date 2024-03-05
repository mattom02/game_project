#pragma once
#include "SFML/Graphics.hpp"

class Enemy
{
public:
	Enemy();

	Enemy(float X, float Y);

	sf::Vector2f getPosition() { return enemyTexture.getPosition(); }

	void move(float X, float Y) { enemyTexture.move(X, Y); }

	float getVelocity() const { return enemyVelocity; }

	const sf::RectangleShape& getTexture() const { return enemyTexture; }

	void updateHitbox();

	sf::Vector2f getHitboxTopLeftCorner() const { return hitboxTopLeftCorner; }

	sf::Vector2f getHitboxBottomRightCorner() const { return hitboxBottomRightCorner; }
private:
	sf::RectangleShape enemyTexture;
	const float textureHeight = 75.0f;
	const float textureWidth = 38.0f;
	const float enemyVelocity = 3.0f;

	sf::Vector2f hitboxTopLeftCorner;
	sf::Vector2f hitboxBottomRightCorner;

	std::vector<sf::Vector2f> spawnPoints {sf::Vector2f(-50, 400), sf::Vector2f(1450, 400),  sf::Vector2f(460, -50), sf::Vector2f(460, 850), sf::Vector2f(920, 850), sf::Vector2f(920, -50)};
};

