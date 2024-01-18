
#include "SFML/Window.hpp"
#include "Player.h"
#include "PlayerGUI.h"
#include "Enemy.h"
#include "GroupOfEnemies.h"
#include "ScoreText.h"
#include "PowerUp.h"

int main() {
    Player player(700, 400);
    StaminaBar staminaBar(300, 100);
    GroupOfEnemies enemies;
    ScoreText score(687, 70, 50);
    PowerUp powerUp(1600, 1000);
    PowerUpBar powerUpBar(1100, 100);
    sf::RenderWindow window(sf::VideoMode(1400, 800), "Game");
    window.setFramerateLimit(60);
    sf::Event event;


    while (true) {
        window.clear(sf::Color::Black);
        window.pollEvent(event);
        if (event.type == sf::Event::Closed) {
            window.close();
            break;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            player.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            player.moveRight();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            player.moveUp();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            player.moveDown();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            player.sprint();
        }
        else
        {
            player.disableSprint();
            player.regenerateStamina();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            player.shootProjectile();
        }
        player.checkIfPoweredUp(window, powerUpBar);
        powerUpBar.updatePowerUpBar(player);
        powerUp.checkForPowerUp(player);
        enemies.spawnEnemy();
        enemies.moveEnemies(player);
        staminaBar.updateStaminaBar(player);
        player.moveProjectiles(enemies, powerUp, score);
        enemies.eraseEnemies(score);
        player.eraseProjectiles();
        if (player.checkIfDied(enemies)) {
            break;
        }
        window.draw(enemies);
        window.draw(player);
        window.draw(staminaBar);
        window.draw(score);
        window.draw(powerUp);
        window.display();
    }

    return 0;
}
