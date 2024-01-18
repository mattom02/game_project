#pragma once

#include "SFML/Graphics.hpp"
#include "Player.h"

class Player;

class StaminaBar : public sf::Drawable
{
public:
	StaminaBar(float X, float Y);

	void updateStaminaBar(const Player& player);

private:
	sf::RectangleShape staminaBar;
	sf::RectangleShape staminaBarBackground;

	const float staminaBarHeight = 50.0f;
	const float staminaBarWidth = 500.0f;

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override { target.draw(staminaBarBackground, state); target.draw(staminaBar, state);}
};

class PowerUpBar : public sf::Drawable
{
public:
	PowerUpBar(float X, float Y);

	void updatePowerUpBar(const Player& player);

private:
	sf::RectangleShape powerUpBar;
	sf::RectangleShape powerUpBarBackground;

	const float powerUpBarHeight = 50.0f;
	const float powerUpBarWidth = 500.0f;

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override { target.draw(powerUpBarBackground, state); target.draw(powerUpBar, state); }
};


