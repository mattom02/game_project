#include "Enemy.h"

#include <random>

Enemy::Enemy(){
	typedef std::mt19937 rng_type;
	std::uniform_int_distribution<rng_type::result_type> udist(0, 5);
	rng_type rng;
	rng.seed(std::time(0));
	rng_type::result_type random_number = udist(rng);

	enemyTexture.setPosition(spawnPoints[random_number]);
	enemyTexture.setSize(sf::Vector2f(textureWidth, textureHeight));
	enemyTexture.setFillColor(sf::Color::Green);
	enemyTexture.setOrigin(sf::Vector2f(textureWidth / 2, textureHeight / 2));
}

Enemy::Enemy(float X, float Y) {
	enemyTexture.setPosition(sf::Vector2f(X, Y));
	enemyTexture.setSize(sf::Vector2f(textureWidth, textureHeight));
	enemyTexture.setFillColor(sf::Color::Green);
	enemyTexture.setOrigin(sf::Vector2f(textureWidth / 2, textureHeight / 2));
}

void Enemy::updateHitbox() {
	hitboxTopLeftCorner = sf::Vector2f(enemyTexture.getPosition().x - (textureWidth / 2), enemyTexture.getPosition().y - (textureHeight / 2));
	hitboxBottomRightCorner = sf::Vector2f(enemyTexture.getPosition().x + (textureWidth / 2), enemyTexture.getPosition().y + (textureHeight / 2));
}

