#include "../include/PowerUp.h"

PowerUp::PowerUp(float X, float Y) {
	powerUpTexture.setPosition(X, Y);
	powerUpTexture.setRadius(textureRadius);
	powerUpTexture.setFillColor(sf::Color::Yellow);
	powerUpTexture.setOrigin(textureRadius, textureRadius);
}

void PowerUp::updateHitbox() {
	powerUphitboxTopLeftCorner = sf::Vector2f(powerUpTexture.getPosition().x - textureRadius, powerUpTexture.getPosition().y - textureRadius);
	powerUphitboxBottomRightCorner = sf::Vector2f(powerUpTexture.getPosition().x + textureRadius, powerUpTexture.getPosition().y + textureRadius);
}

void PowerUp::checkForPowerUp(Player& player) {
	if (isSpawned) {
		if (player.getPosition().x > getHitboxTopLeftCorner().x
			&& player.getPosition().y > getHitboxTopLeftCorner().y
			&& player.getPosition().x < getHitboxBottomRightCorner().x
			&& player.getPosition().y < getHitboxBottomRightCorner().y)
		{
			player.setPowerUp();
			despawn();
		}
	}
}