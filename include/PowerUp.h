#pragma once
#include "Player.h"

class Player;

class PowerUp : public sf::Drawable
{
public:
	PowerUp(float X, float Y);

	void updateHitbox();

	void spawn(float X, float Y) { powerUpTexture.setPosition(X, Y); isSpawned = true; updateHitbox(); }

	void despawn() { powerUpTexture.setPosition(1600, 1000); isSpawned = false; updateHitbox(); }

	void checkForPowerUp(Player& player);

	sf::Vector2f getHitboxTopLeftCorner() const { return powerUphitboxTopLeftCorner; }

	sf::Vector2f getHitboxBottomRightCorner() const { return powerUphitboxBottomRightCorner; }
private:
	sf::CircleShape powerUpTexture;

	sf::Vector2f powerUphitboxTopLeftCorner;
	sf::Vector2f powerUphitboxBottomRightCorner;

	bool isSpawned = false;

	const float textureRadius = 20.0f;

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override { if (isSpawned) target.draw(powerUpTexture, state); }
};

