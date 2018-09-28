#include"AlienBullet.h"

const char* AlienBullet::spriteName = "res/bltEnemy.png";
const float AlienBullet::xScale = .008f;
const float AlienBullet::yScale = .04f;

AlienBullet::AlienBullet(bool goBeyond) : Bullet(goBeyond, NULL) {
	sprite = Sprite(AlienBullet::spriteName);
	sprite.setScale(xScale, yScale);
}

AlienBullet::AlienBullet(float xPos, float yPos, bool goBeyond) : Bullet(xPos, yPos, goBeyond, NULL) {
	sprite = Sprite(AlienBullet::spriteName);
	sprite.setScale(xScale, yScale);
}

void AlienBullet::update() {
	GameObject::update();
	this->moveDown();
}

float AlienBullet::getXScale() {
	return xScale;
}

float AlienBullet::getYScale() {
	return yScale;
}
