
#include "SFML/Window.hpp"
#include "include/Player.h"
#include "include/PlayerGUI.h"
#include "include/Enemy.h"
#include "include/GroupOfEnemies.h"
#include "include/ScoreText.h"
#include "include/PowerUp.h"
#include "include/MainMenu.h"

enum DIFFICULTY {
    EASY,
    MEDIUM,
    HARD
};

void PlayGame(sf::RenderWindow& window, DIFFICULTY difficulty ) {
    Player player(700, 400);
    StaminaBar staminaBar(300, 100);
    GroupOfEnemies enemies;
    switch (difficulty) {
        case DIFFICULTY::EASY:
            enemies.setSpawnDelay(125);
            break;
        case DIFFICULTY::MEDIUM:
            enemies.setSpawnDelay(100);
            break;
        case DIFFICULTY::HARD:
            enemies.setSpawnDelay(75);
            break;
    }
    ScoreText score(687, 70, 50);
    PowerUp powerUp(1600, 1000);
    PowerUpBar powerUpBar(1100, 100);
    while (true) {
        window.clear(sf::Color::Black);
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
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1400, 800), "Sprint & Shoot");
    MainMenu mainMenu(window.getSize().x, window.getSize().y, 50);
    window.setFramerateLimit(60);
    sf::Event event;

    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        window.draw(mainMenu);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::S && !mainMenu.getIsPlaySelected())
                {
                    mainMenu.moveDownMain();
                    break;
                }
                else if (event.key.code == sf::Keyboard::W && !mainMenu.getIsPlaySelected())
                {
                    mainMenu.moveUpMain();
                    break;
                }
                if (event.key.code == sf::Keyboard::S && mainMenu.getIsPlaySelected())
                {
                    mainMenu.moveDownPlay();
                    break;
                }
                else if (event.key.code == sf::Keyboard::W && mainMenu.getIsPlaySelected())
                {
                    mainMenu.moveUpPlay();
                    break;
                }
                if (!mainMenu.getIsPlaySelected()) {
                    switch (mainMenu.getSelectedIndexMain()) {
                    case 0:
                        if (event.key.code == sf::Keyboard::Enter) {
                            mainMenu.selectPlay();
                        }
                        break;
                    case 1:
                        if (event.key.code == sf::Keyboard::Enter) {
                            window.close();
                        }
                        break;
                    }
                }
                else {
                    switch (mainMenu.getSelectedIndexPlay()) {
                    case 0:
                        if (event.key.code == sf::Keyboard::Enter) {
                            PlayGame(window, DIFFICULTY::EASY);
                            mainMenu.unselectPlay();
                        }
                        break;
                    case 1:
                        if (event.key.code == sf::Keyboard::Enter) {
                            PlayGame(window, DIFFICULTY::MEDIUM);
                            mainMenu.unselectPlay();
                        }
                        break;
                    case 2:
                        if (event.key.code == sf::Keyboard::Enter) {
                            PlayGame(window, DIFFICULTY::HARD);
                            mainMenu.unselectPlay();
                        }
                        break;
                    case 3:
                        if (event.key.code == sf::Keyboard::Enter) {
                            mainMenu.unselectPlay();
                        }
                        break;
                    }
                }
            }
        }
        window.display();
    }

    return 0;
}
