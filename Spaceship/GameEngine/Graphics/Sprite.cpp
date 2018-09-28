#include "Sprite.h"

const float Sprite::genericSize = 500;

Sprite::Sprite() {
	texture = Texture();
	this->xScale = 1;
	this->yScale = 1;
}

Sprite::Sprite(string imagePath) {
	texture = Texture(imagePath);
	this->xScale = 1;
	this->yScale = 1;
}

Sprite::Sprite(string imagePath, float xScale, float yScale) {
	texture = Texture(imagePath);
	this->xScale = xScale;
	this->yScale = yScale;
}


void Sprite::update() {

}

void Sprite::render(float xPos, float yPos) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.getID());
	glLoadIdentity();

	//translate
	glTranslatef(xPos, yPos, 0);

	//rotate


	//scale
	glScalef(this->xScale, this->yScale, 1);
	
	//render
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);		glVertex2f(0, 0);
	glTexCoord2f(1, 0);		glVertex2f(genericSize, 0);
	glTexCoord2f(1, 1);		glVertex2f(genericSize, genericSize);
	glTexCoord2f(0, 1);		glVertex2f(0, genericSize);
	
	glEnd();

	glDisable(GL_TEXTURE_2D);

}

void Sprite::setScale(float x, float y) {
	this->xScale = x;
	this->yScale = y;
}

float Sprite::getXScale() {
	return this->xScale;
}

float Sprite::getYScale() {
	return this->yScale;
}

Texture Sprite::getTexture() {
	return this->texture;
}


