#include "SFML/Window.hpp"
#include "Player.h"
#include "PlayerGUI.h"
#include "GroupOfEnemies.h"
#include "ScoreText.h"
#include "PowerUp.h"
#include "MainMenu.h"
#include "DeathScreen.h"

enum DIFFICULTY {
    EASY,
    MEDIUM,
    HARD
};

void PlayGame(sf::RenderWindow& window, sf::Event& event,DIFFICULTY difficulty ) {
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
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }
        window.clear(sf::Color::Black);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            player.shootProjectile();
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
        player.moveProjectiles(enemies, powerUp, score);
        enemies.eraseEnemies(score);
        player.eraseProjectiles();
        player.checkIfPoweredUp(window, powerUpBar);
        powerUpBar.updatePowerUpBar(player);
        powerUp.checkForPowerUp(player);
        enemies.spawnEnemy();
        enemies.moveEnemies(player);
        staminaBar.updateStaminaBar(player);
        if (player.checkIfDied(enemies)) {
            break;
        }
        window.draw(powerUp);
        window.draw(enemies);
        window.draw(player);
        window.draw(staminaBar);
        window.draw(score);
        window.display();
    }
}

void DisplayDeathScreen(sf::RenderWindow& window) {
    DeathScreen deathScreen(window.getSize().x, window.getSize().y, 50);
    sf::Event eventDeath;
    bool exit = true;
    while (exit) {
        while (window.pollEvent(eventDeath)) {
            if (eventDeath.type == sf::Event::Closed) {
                exit = false;
                window.close();
                break;
            }
            if (eventDeath.type == sf::Event::KeyReleased && eventDeath.key.code == sf::Keyboard::Enter) {
                exit = false;
                break;
            }
            else if (eventDeath.type == sf::Event::KeyReleased && eventDeath.key.code == sf::Keyboard::Escape) {
                exit = false;
                window.close();
                break;
            }
        }
        window.clear();
        window.draw(deathScreen);
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
                                PlayGame(window, event, DIFFICULTY::EASY);
                                mainMenu.unselectPlay();
                                if (!window.isOpen()) {
                                    break;
                                }
                                DisplayDeathScreen(window);
                            }
                            break;
                        case 1:
                            if (event.key.code == sf::Keyboard::Enter) {
                                PlayGame(window, event, DIFFICULTY::MEDIUM);
                                mainMenu.unselectPlay();
                                if (!window.isOpen()) {
                                    break;
                                }
                                DisplayDeathScreen(window);
                            }
                            break;
                        case 2:
                            if (event.key.code == sf::Keyboard::Enter) {
                                PlayGame(window, event, DIFFICULTY::HARD);
                                mainMenu.unselectPlay();
                                if (!window.isOpen()) {
                                    break;
                                }
                                DisplayDeathScreen(window);
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
