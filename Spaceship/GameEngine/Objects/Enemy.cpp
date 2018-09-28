#include "Enemy.h"
#include "../utils/EnemyBehaviour.h"
#include <cstdlib>
#include <iostream>
#include "AlienBullet.h"
#include "../utils/EnemyDifficulty.h"


const char* Enemy::spriteName = "res/enemy.png";
const float Enemy::startY = GameEngine::SCREEN_HEIGHT;
const float Enemy::xScale = .25f;
const float Enemy::yScale = .18f;


Enemy::Enemy(bool goBeyond, int level) : Player(goBeyond) {
	init(level);
}

Enemy::Enemy(float xPos, float yPos, bool goBeyond, int level) : Player(xPos, yPos, goBeyond) {
	init(level);
}

void Enemy::init(int level) {
	sprite = Sprite(Enemy::spriteName);
	speedMovement = .1f;
	life = level;
	health = level;
	this->speedMovement += EnemyDifficulty::getMoreSpeedMovement(level);
	sprite.setScale(xScale, yScale);
	dt = 0;
	lastTime = glfwGetTime();
	changeDt = 1;
	changeLastTime = glfwGetTime();
}

void Enemy::update() {
	GameObject::update();
	this->moveDown();
	this->decide();
	
	double now = glfwGetTime();
	double timeGone = now - lastTime;
	dt += timeGone;
	lastTime = now;

	now = glfwGetTime();
	timeGone = now - changeLastTime;
	changeDt += timeGone;
	changeLastTime = now;

}

void Enemy::decide() {
	
	if (changeDt < 0.9) {
		(*this.*decision) ();
	}
	else {
		changeDt = 0;
		//std::srand(time(0)); // use current time as seed for random generator

		const int min = 1;
		const int max = 3;
		int x = 4;
		while (x > 3)
			x = 1 + std::rand() / ((RAND_MAX + 1u) / 3);  // Note: 1+rand()%6 is biased

		x = std::rand() % max + min;

		switch (x) {
		case MOVE_LEFT:
			if (this->goBeyondLeftWall()) {
				decision = &GameObject::moveRight;
				this->moveRight();
			}
			else {
				decision = &GameObject::moveLeft;
				this->moveLeft();
			}
			break;
		case MOVE_RIGHT:
			if (this->goBeyondRightWall()) {
				decision = &GameObject::moveLeft;
				this->moveLeft();
			}
			else {
				decision = &GameObject::moveRight;
				this->moveRight();
			}
			break;
		case SHOOT:
			this->shoot();
			decision = &Enemy::shoot;
			break;
		default:
			break;
		}
	}
}

void Enemy::shoot() {
	if (dt < 0.5) {
		return;
	}
	dt = 0;
	float topX = this->getX() + (Sprite::genericSize * this->getSpriteXScale()) / 2;
	topX -= (Sprite::genericSize * AlienBullet::getXScale()) / 2;
	float topY = this->getY();
	AlienBullet* bullet = new AlienBullet(topX, topY, true);
}

void Enemy::renderHealth() {

	const int margin = 5;
	float width = (float)((this->getSpriteXScale() * Sprite::genericSize) / life);
	int y = this->yPos + (this->getSpriteYScale() * Sprite::genericSize) + margin;
	const int height = 5;
	for (int i = 0; i < this->life; i++) {
		if (i < this->health) {
			RGB* color = new RGB(1, 0, 0);
			int x = this->xPos + i * width;
			Rect* r = new Rect(x, y, width, height);
			this->renderHealthPortion(r, color);
		}
		else {
			RGB* color = new RGB(1, 1, 1);
			int x = this->xPos + i * width;
			Rect* r = new Rect(x, y, width, height);
			this->renderHealthPortion(r, color);
		}
	}

}

float Enemy::getXScale() {
	return xScale;
}

float Enemy::getYScale() {
	return yScale;
}

bool Enemy::stillOnMap() {
	return !(this->yPos + (sprite.getYScale() * Sprite::genericSize) < spriteDistanceToMargin);
}
