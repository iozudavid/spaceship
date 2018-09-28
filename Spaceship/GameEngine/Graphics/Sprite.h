#ifndef SPRITE_H
#define SPRITE_H

#include "GLFW/glfw3.h"
#include "Texture.h"
#include <iostream>
#include <string>

using namespace std;

class Sprite {
public:

	Sprite();
	Sprite(string imgPath);
	Sprite(string imgPath, float xScale, float yScale);
	~Sprite(){}
	void update();
	void render(float xPos, float yPos);
	void setScale(float x, float y);
	float getXScale();
	float getYScale();

	Texture getTexture();
	Texture getSubTexture(int x, int y, int width, int height);

	const static float genericSize;

private:
	Texture texture;
	float xScale;
	float yScale;

};


#endif