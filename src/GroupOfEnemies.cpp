#include "GroupOfEnemies.h"

void GroupOfEnemies::spawnEnemy() {
	if (enemies.size() < 6 && spawnDelayTimer == spawnDelay) {
		Enemy enemy;
		enemies.push_back(enemy);
		spawnDelayTimer = 0;
	}
    if (spawnDelayTimer < spawnDelay){
        spawnDelayTimer++;
    }
}

void GroupOfEnemies::spawnEnemy(float X, float Y) {
	if (enemies.size() < 6 && spawnDelayTimer == spawnDelay) {
		Enemy enemy(X, Y);
		enemies.push_back(enemy);
		spawnDelayTimer = 0;
	}
    if (spawnDelayTimer < spawnDelay){
        spawnDelayTimer++;
    }
}

void GroupOfEnemies::moveEnemies(const Player& player) {
	for (auto& i : enemies) {
		if (i.getPosition().x < player.getPosition().x - 1) {
			i.move(i.getVelocity(), 0);
		}
		else if (i.getPosition().x > player.getPosition().x + 1) {
			i.move(-1 * i.getVelocity(), 0);
		}
		if (i.getPosition().y < player.getPosition().y - 1) {
			i.move(0, i.getVelocity());
		}
		else if (i.getPosition().y > player.getPosition().y + 1) {
			i.move(0, -1 * i.getVelocity());
		}
		i.updateHitbox();
	}
}

void GroupOfEnemies::eraseEnemies(ScoreText &score) {
	for (auto& i : enemiesIndexesToErase) {
		score.updateScore();
		std::list<Enemy>::iterator it = enemies.begin();
		std::advance(it, i);
		enemies.erase(it);
	}
	enemiesIndexesToErase.clear();
}

void GroupOfEnemies::draw(sf::RenderTarget& target, sf::RenderStates state) const {
	for (auto& i : enemies) {
		target.draw(i.getTexture(), state);
	}
}