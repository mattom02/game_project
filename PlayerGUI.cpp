#include "PlayerGUI.h"

StaminaBar::StaminaBar(float X, float Y) {
	staminaBar.setPosition(X, Y);
	staminaBar.setSize(sf::Vector2f(staminaBarWidth, staminaBarHeight));
	staminaBar.setFillColor(sf::Color::Blue);
	staminaBar.setOrigin(sf::Vector2f(staminaBarWidth / 2, staminaBarHeight / 2));

	staminaBarBackground.setPosition(X, Y);
	staminaBarBackground.setSize(sf::Vector2f(staminaBarWidth, staminaBarHeight));
	staminaBarBackground.setFillColor(sf::Color(19, 18, 82));
	staminaBarBackground.setOrigin(sf::Vector2f(staminaBarWidth / 2, staminaBarHeight / 2));
}

void StaminaBar::updateStaminaBar(const Player& player) {
	float currentStamina = player.getStamina();
	float currentStaminaBar = (currentStamina / 10.0f) * staminaBarWidth;
	
	staminaBar.setSize(sf::Vector2f(currentStaminaBar, staminaBarHeight));
}

PowerUpBar::PowerUpBar(float X, float Y) {
	powerUpBar.setPosition(X, Y);
	powerUpBar.setSize(sf::Vector2f(powerUpBarWidth, powerUpBarHeight));
	powerUpBar.setFillColor(sf::Color(222,212,20));
	powerUpBar.setOrigin(sf::Vector2f(powerUpBarWidth / 2, powerUpBarHeight / 2));

	powerUpBarBackground.setPosition(X, Y);
	powerUpBarBackground.setSize(sf::Vector2f(powerUpBarWidth, powerUpBarHeight));
	powerUpBarBackground.setFillColor(sf::Color(115,110,29));
	powerUpBarBackground.setOrigin(sf::Vector2f(powerUpBarWidth / 2, powerUpBarHeight / 2));
}

void PowerUpBar::updatePowerUpBar(const Player& player) {
	float currentPowerUp = player.getPowerUp();
	float currentPowerUpBar = (currentPowerUp / 30.0f) * powerUpBarWidth;

	powerUpBar.setSize(sf::Vector2f(currentPowerUpBar, powerUpBarHeight));
}