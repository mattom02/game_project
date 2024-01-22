#pragma once
#include "Player.h"
#include "Enemy.h"
#include "ScoreText.h"
#include <list>
#include <set>
class Player;

class GroupOfEnemies : public sf::Drawable {
public:
	void spawnEnemy();

	void spawnEnemy(float X, float Y);

	const std::list<Enemy>& getEnemies() const { return enemies; }

	void moveEnemies(const Player& player);

	void eraseEnemies(ScoreText& score);

	void addEnemiesIndexesToErase(std::size_t index) { enemiesIndexesToErase.emplace(index); }

	void setSpawnDelay(int delay) { spawnDelay = delay; }
private:
	std::list<Enemy> enemies;

	std::set<std::size_t> enemiesIndexesToErase;

	int spawnDelay = 0;

	int spawnDelayTimer = spawnDelay;

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

};

