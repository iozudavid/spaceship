#include "GameObject.h"
#include "../GameEngine.h"

const float GameObject::xScale = 1;
const float GameObject::yScale = 1;

GameObject::GameObject() {
	xPos = 0;
	yPos = 0;
	sprite = Sprite();
	speedMovement = .25f;
	life = 1;
	health = 1;
	canGoBeyondWalls = false;
	GameEngine* engine = engine->getInstance();
	engine->addToInsertGameObject(this);
	stillExists = true;
}

GameObject::GameObject(bool canGoBeyond) {
	xPos = 0;
	yPos = 0;
	sprite = Sprite();
	speedMovement = .25f;
	life = 1;
	health = 1;
	canGoBeyondWalls = canGoBeyond;
	GameEngine* engine = engine->getInstance();
	engine->addToInsertGameObject(this);
	stillExists = true;
}

GameObject::GameObject(float xPos, float yPos, bool canGo) {
	this->xPos = xPos;
	this->yPos = yPos;
	sprite = Sprite();
	speedMovement = .25f;
	life = 1;
	health = 1;
	canGoBeyondWalls = canGo;
	GameEngine* engine = engine->getInstance();
	engine->addToInsertGameObject(this);
	stillExists = true;
}

void GameObject::setXPosition(float xPos) {
	this->xPos = xPos;
}

void GameObject::setYPosition(float yPos) {
	this->yPos = yPos;
}

void GameObject::moveUp() {
	
	if (!this->isAlive())
		return;

	if (!canGoBeyondWalls)
		if (this->goBeyondTopWall())
			return;

	if (canGoBeyondWalls)
		if (this->yPos + speedMovement > GameEngine::SCREEN_HEIGHT) {
			GameEngine* engine = engine->getInstance();
			engine->addToDeleteGameObject(this);
			stillExists = false;
		}
		
	this->yPos += speedMovement;
}

void GameObject::moveDown() {

	if (!this->isAlive())
		return;


	if (!canGoBeyondWalls)
		if (this->goBeyondBottomWall())
			return;

	if (canGoBeyondWalls)
		if (this->yPos + (sprite.getYScale() * Sprite::genericSize) < spriteDistanceToMargin) {
			GameEngine* engine = engine->getInstance();
			engine->addToDeleteGameObject(this);
			stillExists = false;
		}

	this->yPos -= speedMovement;
}

void GameObject::moveRight() {

	if (!this->isAlive())
		return;


	if (!canGoBeyondWalls)
		if (this->goBeyondRightWall())
			return;

	if (canGoBeyondWalls)
		if (this->xPos + speedMovement > GameEngine::SCREEN_WIDTH) {
			GameEngine* engine = engine->getInstance();
			engine->addToDeleteGameObject(this);
			stillExists = false;
		}

	this->xPos += speedMovement;
}

void GameObject::moveLeft() {

	if (!this->isAlive())
		return;


	if (!canGoBeyondWalls)
		if (this->goBeyondLeftWall())
			return;

	if (canGoBeyondWalls)
		if (this->xPos + (sprite.getXScale() * Sprite::genericSize) < spriteDistanceToMargin) {
			GameEngine* engine = engine->getInstance();
			engine->addToDeleteGameObject(this);
			stillExists = false;
		}

	this->xPos -= speedMovement;
}

void GameObject::update() {
	this->sprite.update();
}

void GameObject::render() {
	this->sprite.render(this->xPos, this->yPos);
}

float GameObject::getX() {
	return xPos;
}

float GameObject::getY() {
	return yPos;
}

float GameObject::getSpriteXScale() {
	return sprite.getXScale();
}

float GameObject::getSpriteYScale() {
	return sprite.getYScale();
}

float GameObject::getXScale() {
	return xScale;
}

float GameObject::getYScale() {
	return yScale;
}

bool GameObject::goBeyondBottomWall() {
	float desiredPos = this->yPos - speedMovement;
	return desiredPos < spriteDistanceToMargin;
}

bool GameObject::goBeyondTopWall() {
	float desiredPos = this->yPos + speedMovement + (sprite.getYScale() * Sprite::genericSize);
	return desiredPos > GameEngine::SCREEN_HEIGHT - spriteDistanceToMargin;

}

bool GameObject::goBeyondLeftWall() {
	float desiredPos = this->xPos - speedMovement;
	return desiredPos < spriteDistanceToMargin;
}

bool GameObject::goBeyondRightWall() {
	float desiredPos = this->xPos + speedMovement + (sprite.getXScale() * Sprite::genericSize);
	return desiredPos > GameEngine::SCREEN_WIDTH - spriteDistanceToMargin;
}

bool GameObject::isAlive() {
	return this->stillExists;
}
