#include "Player.h"
#include "Bullet.h"

const char* Player::spriteName = "res/user.png";
const float Player::startX = GameEngine::SCREEN_WIDTH / 2 - (Sprite::genericSize * Player::getXScale()) / 2;
const float Player::startY = 10;
const float Player::xScale = .2f;
const float Player::yScale = .32f;

Player::Player(bool goBeyond) : GameObject(startX, startY, goBeyond) {
	sprite = Sprite(Player::spriteName);
	sprite.setScale(xScale, yScale);
	bullets = 5;
	score = 0;
}

Player::Player(float xPos, float yPos, bool goBeyond) : GameObject(xPos, yPos, goBeyond) {
	sprite = Sprite(Player::spriteName);
	sprite.setScale(xScale, yScale);
	bullets = 5;
	score = 0;
}

float Player::getXScale() {
	return xScale;
}

float Player::getYScale() {
	return yScale;
}

void Player::shoot() {
	if (bullets <= 0)
		return;
	float topX = this->getX() + (Sprite::genericSize * this->getSpriteXScale()) / 2;
	topX -= (Sprite::genericSize * Bullet::getXScale()) / 2;
	float topY = this->getY() + (Sprite::genericSize * this->getSpriteYScale());
	Bullet* bullet = new Bullet(topX, topY, true, this);
	bullets--;
}

void Player::render() {
	if (!this->isAlive())
		return;
	GameObject::render();
	this->renderHealth();

}

void Player::renderHealth() {
	
	const int margin = 9;
	float width = (float)((this->getSpriteXScale() * Sprite::genericSize)/life);
	int y = this->yPos - margin;
	const int height = 5;
	for (int i = 0; i < this->life; i++) {
		if (i < this->health) {
			RGB* color = new RGB(0, 1, 0);
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

void Player::renderHealthPortion(Rect* rect, RGB* color){

	int genericSize = Sprite::genericSize;

	glLoadIdentity();

	//translate
	glTranslatef(rect->getX(), rect->getY(), 0);

	//rotate

	//scale
	glScalef((float)rect->getWidth() / (float)genericSize, (float)rect->getHeight() / (float)genericSize, 1);


	//render
	glColor3f(color->getR(), color->getG(), color->getB());
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);		glVertex2f(0, 0);
	glTexCoord2f(1, 0);		glVertex2f(genericSize, 0);
	glTexCoord2f(1, 1);		glVertex2f(genericSize, genericSize);
	glTexCoord2f(0, 1);		glVertex2f(0, genericSize);

	glEnd();

	delete rect;
	delete color;

}

void Player::onHit(float xPos, float yPos, float damage) {
	if (!isAlive())
		return;
	this->health -= damage;
	if (this->health <= 0) {
		stillExists = false;
		GameEngine::getInstance()->addToDeleteGameObject(this);
	}
}

int Player::getBullets() {
	return bullets;
}

void Player::setBullets(int blt) {
	bullets = blt;
}

int Player::getScore() {
	return score;
}

void Player::increaseScore() {
	score++;
}

void Player::setScore(int s) {
	score = s;
}
