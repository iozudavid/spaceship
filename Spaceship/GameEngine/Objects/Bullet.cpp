#include "Bullet.h"
#include "Player.h"

const char* Bullet::spriteName = "res/blt2.png";
const float Bullet::xScale = .008f;
const float Bullet::yScale = .04f;


Bullet::Bullet(bool goBeyond, Player* _shooter) : GameObject(0, 0, goBeyond) {
	sprite = Sprite(Bullet::spriteName);
	sprite.setScale(xScale, yScale);
	damage = 1;
	this->shooter = _shooter;
}

Bullet::Bullet(float xPos, float yPos, bool goBeyond, Player* shooter) : GameObject(xPos, yPos, goBeyond) {
	sprite = Sprite(Bullet::spriteName);
	sprite.setScale(xScale, yScale);
	damage = 1;
	this->shooter = shooter;
}

void Bullet::increaseDamage() {
	this->damage++;
}

void Bullet::decreaseDamage() {
	this->damage--;
}

void Bullet::update() {
	GameObject::update();
	this->moveUp();
}

float Bullet::getXScale() {
	return xScale;
}

float Bullet::getYScale() {
	return yScale;
}

void Bullet::onHit(float xPos, float yPos, float damage) {
	//remove bullet from game
	if (!isAlive())
		return;
	stillExists = false;
	GameEngine::getInstance()->addToDeleteGameObject(this);
}

float Bullet::getDamage() {
	return damage;
}

Player* Bullet::getShooter() {
	return shooter;
}
