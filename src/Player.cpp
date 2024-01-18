#include "../include/Player.h"

Player::Player(float X, float Y) {
	playerTexture.setPosition(X, Y);
	playerTexture.setSize(sf::Vector2f(textureWidth, textureHeight));
	playerTexture.setFillColor(sf::Color::White);
	playerTexture.setOrigin(sf::Vector2f(textureWidth/2, textureHeight /2));
}

void Player::sprint() {
	if (stamina > 0 && isStaminaRegenerated){
		stamina -= 0.1f;
		playerVelocity = 6.0f;
	}
	else if (stamina == 10.0f && !isStaminaRegenerated) {
		isStaminaRegenerated = true;
	}
	else {
		disableSprint();
		isStaminaRegenerated = false;
	}
}

void Player::moveLeft() { 
	if (playerTexture.getPosition().x > 0) {
		if (isPoweredUp) {
			playerTexture.move(-2 * playerVelocity, 0);
		}
		else {
			playerTexture.move(-1 * playerVelocity, 0);
		}
	}
	facingDirection = "left";
}

void Player::moveRight() {
	if (playerTexture.getPosition().x < 1400) {
		if (isPoweredUp) {
			playerTexture.move(2 * playerVelocity, 0);
		}
		else {
			playerTexture.move(playerVelocity, 0);
		}
	}
	facingDirection = "right";
}

void Player::moveUp() { 
	if (playerTexture.getPosition().y > 0) {
		if (isPoweredUp) {
			playerTexture.move(0, -2 * playerVelocity);
		}
		else {
			playerTexture.move(0, -1 * playerVelocity);
		}
	}
	facingDirection = "up";
}

void Player::moveDown() { 
	if (playerTexture.getPosition().y < 800) {
		if (isPoweredUp) {
			playerTexture.move(0, 2 * playerVelocity);
		}
		else {
			playerTexture.move(0, playerVelocity);
		}
	}
	facingDirection = "down";
}

void Player::checkIfPoweredUp(sf::RenderWindow& window, PowerUpBar& powerUpBar) {
	if (isPoweredUp) {
		if (powerUp < 0) {
			isPoweredUp = false;
			powerUp = 30.0f;
		}
		powerUp -= 0.05f;
		window.draw(powerUpBar);
	}
}

void Player::shootProjectile() {
	if (shootDelayTimer == shootDelay) {
		sf::CircleShape projectile;
		projectile.setFillColor(sf::Color::Red);
		projectile.setRadius(5.0f);
		projectile.setOrigin(sf::Vector2f(projectile.getRadius(), projectile.getRadius()));
		projectile.setPosition(playerTexture.getPosition().x, playerTexture.getPosition().y);

		projectiles.push_back(std::make_pair(projectile, facingDirection));

		shootDelayTimer = 0;
	}
}

void Player::moveProjectiles(GroupOfEnemies& enemies, PowerUp& powerUp, ScoreText& score) {
	if (shootDelayTimer < shootDelay && isPoweredUp) {
		shootDelayTimer += 2;
	}
	else if (shootDelayTimer < shootDelay) {
		shootDelayTimer++;
	}
	std::size_t index;
	for (std::size_t i = 0; i < projectiles.size(); i++) {
		if (projectiles[i].second == "up") {
			if (projectiles[i].first.getPosition().y < 0) {
				projectileIndexesToErase.emplace(i);
			}
			else {
				projectiles[i].first.move(0, -1 * projectileVelocity);
			}
		}
		if (projectiles[i].second == "down") {
			if (projectiles[i].first.getPosition().y > 800) {
				projectileIndexesToErase.emplace(i);
			}
			else {
				projectiles[i].first.move(0, projectileVelocity);
			}
		}
		if (projectiles[i].second == "right") {
			if (projectiles[i].first.getPosition().x > 1400) {
				projectileIndexesToErase.emplace(i);
			}
			else {
				projectiles[i].first.move(projectileVelocity, 0);
			}
		}
		if (projectiles[i].second == "left") {
			if (projectiles[i].first.getPosition().x < 0) {
				projectileIndexesToErase.emplace(i);
			}
			else {
				projectiles[i].first.move(-1 * projectileVelocity, 0);
			}
		}
		index = 0;
		for (auto& j : enemies.getEnemies()) {
			if (projectiles[i].first.getPosition().x > j.getHitboxTopLeftCorner().x
				&& projectiles[i].first.getPosition().y > j.getHitboxTopLeftCorner().y
				&& projectiles[i].first.getPosition().x < j.getHitboxBottomRightCorner().x
				&& projectiles[i].first.getPosition().y < j.getHitboxBottomRightCorner().y)
			{
				enemies.addEnemiesIndexesToErase(index);
				projectileIndexesToErase.emplace(i);
				if (score.getScore() % 20 == 0) {
					powerUp.spawn(j.getTexture().getPosition().x, j.getTexture().getPosition().y);
				}
			}
			index++;
		}
		
	}
}

void Player::eraseProjectiles() {
	for (auto& i : projectileIndexesToErase) {
		projectiles.erase(projectiles.begin() + i);
	}
	projectileIndexesToErase.clear();
}

bool Player::checkIfDied(GroupOfEnemies& enemies) {
	for (auto& j : enemies.getEnemies()) {
		if (playerTexture.getPosition().x > j.getHitboxTopLeftCorner().x
			&& playerTexture.getPosition().y > j.getHitboxTopLeftCorner().y
			&& playerTexture.getPosition().x < j.getHitboxBottomRightCorner().x
			&& playerTexture.getPosition().y < j.getHitboxBottomRightCorner().y)
		{
			return true;
		}
	}
	return false;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	target.draw(playerTexture, state);
	for (auto& i : projectiles) {
		target.draw(i.first, state);
	}
}