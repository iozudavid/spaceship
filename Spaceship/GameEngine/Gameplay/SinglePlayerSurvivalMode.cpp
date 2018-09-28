#include "SinglePlayerSurvivalMode.h"
#include "../IO/Keyboard.h"
#include "../Objects/Enemy.h"
#include "../Objects/AlienBullet.h"
#include "../Physics/Hit.h"
#include <string>
#include <vector>
#include "../IO/GameStats.h"

SinglePlayerSurvivalMode::SinglePlayerSurvivalMode(std::vector<GameObject*> *gameObjects) : GameplayMode(gameObjects){
	level = 0;
	this->player = new Player(false);
	this->initEnemies();
	std::vector<std::string> stats;
	lastAmmo = 5;
	lastLevel = 1;
	lastScore = 0;
	stats.push_back("score 0");
	stats.push_back("ammo 5");
	stats.push_back("level 1");
	this->gameStats = new GameStats(stats);
}

void SinglePlayerSurvivalMode::initEnemies() {
	level++;
	this->enemy1 = new Enemy(0, GameEngine::SCREEN_HEIGHT, true, level);
	this->enemy2 = new Enemy(0.25 * GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT, true, level);
	this->enemy3 = new Enemy(0.5 * GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT, true, level);
	this->enemy4 = new Enemy(0.75 * GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT, true, level);
}

void SinglePlayerSurvivalMode::updateGame() {
	GameplayMode::updateGame();
}

void SinglePlayerSurvivalMode::updateControls() {

	//single player controls
	if (Keyboard::keyPressed(GLFW_KEY_RIGHT)) {
		player->moveRight();
	}

	if (Keyboard::keyPressed(GLFW_KEY_LEFT)) {
		player->moveLeft();
	}

	if (Keyboard::keyPressed(GLFW_KEY_UP)) {
		player->moveUp();
	}

	if (Keyboard::keyPressed(GLFW_KEY_DOWN)) {
		player->moveDown();
	}

	if (Keyboard::keyDown(GLFW_KEY_SPACE)) {
		player->shoot();
	}
}
void SinglePlayerSurvivalMode::updateHit() {
	std::vector<Player*> individs = { player };
	std::vector<Enemy*> enemies = { enemy1,enemy2,enemy3,enemy4 };
	std::vector<Bullet*> bullets;
	std::vector<AlienBullet*> alienBullets;

	std::vector<GameObject*> objs = *gameObjects;


	for (auto obj : objs) {
		if (strcmp(obj->className(), "Bullet") == 0) {
			bullets.push_back((Bullet*)obj);
		}
		else if (strcmp(obj->className(), "AlienBullet") == 0) {
			alienBullets.push_back((AlienBullet*)obj);
		}
	}
	for (auto obj : individs) {
		for (auto blt : alienBullets) {
			Rect* individRect = new Rect(obj->getX(), obj->getY(), obj->getSpriteXScale() * Sprite::genericSize, obj->getSpriteYScale() * Sprite::genericSize);
			Rect* bulletRect = new Rect(blt->getX(), blt->getY(), blt->getSpriteXScale() * Sprite::genericSize, blt->getSpriteYScale() * Sprite::genericSize);
			Hit* hitted = new Hit(bulletRect, individRect);
			if (hitted->didHit()) {
				obj->onHit(blt->getX(), blt->getY(), blt->getDamage());
				blt->onHit(0, 0, 0);
			}
		}
	}

	for (auto obj : enemies) {
		if (obj == NULL)
			continue;
		if (!obj->isAlive())
			continue;
		for (auto blt : bullets) {
			Rect* individRect = new Rect(obj->getX(), obj->getY(), obj->getSpriteXScale() * Sprite::genericSize, obj->getSpriteYScale() * Sprite::genericSize);
			Rect* bulletRect = new Rect(blt->getX(), blt->getY(), blt->getSpriteXScale() * Sprite::genericSize, blt->getSpriteYScale() * Sprite::genericSize);
			Hit* hitted = new Hit(bulletRect, individRect);
			if (hitted->didHit()) {
				obj->onHit(blt->getX(), blt->getY(), blt->getDamage());
				blt->getShooter()->increaseScore();
				blt->onHit(0, 0, 0);
			}
		}
	}

}

void SinglePlayerSurvivalMode::updateObjects() {

	std::vector<Enemy**> enemies = { &enemy1,&enemy2,&enemy3,&enemy4 };

	for (auto obj : enemies) {
		if (*obj == NULL)
			continue;
		if (!(*obj)->stillOnMap()) {
			Enemy** a = (obj);
			*obj = NULL;
			delete (*a);
		}
		else if (!(*obj)->isAlive()) {
			*obj = NULL;
		}
	}

	if (!this->player->isAlive()) {
		GameEngine::getInstance()->gameOver(player->getScore());
		return;
	}

	bool newRowEnemy = true;

	for (auto obj : enemies) {
		if ((*obj)!=NULL) {
			newRowEnemy = false;
		}
	}

	if (newRowEnemy) {
		this->initEnemies();
		player->setBullets(level * 5);
	}

}


void SinglePlayerSurvivalMode::render() {
	if (lastAmmo == player->getBullets() && lastLevel == level && lastScore == player->getScore()) {
		gameStats->render();
	}
	else {
		std::vector<std::string> stats;
		stats.push_back("score " + std::to_string(player->getScore()));
		stats.push_back("ammo " + std::to_string(player->getBullets()));
		stats.push_back("level " + std::to_string(level));
		gameStats->changeStats(stats);
		lastAmmo = player->getBullets();
		lastScore = player->getScore();
		lastLevel = level;
		gameStats->render();
	}
}
