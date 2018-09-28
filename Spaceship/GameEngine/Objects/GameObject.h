#pragma once
#ifndef Object_Included
#define Object_Included
#include "../Graphics/Sprite.h"

class GameObject {
public:
	GameObject();
	GameObject(bool goBeyond);
	GameObject(float xPos, float yPos, bool goBeyond);
	~GameObject(){}

	void setXPosition(float xPos);
	void setYPosition(float yPos);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	virtual void update();
	virtual void render();

	float getX();
	float getY();
	float getSpriteXScale();
	float getSpriteYScale();
	static float getXScale();
	static float getYScale();

	bool goBeyondLeftWall();
	bool goBeyondRightWall();
	bool goBeyondBottomWall();
	bool goBeyondTopWall();
    
	const float spriteDistanceToMargin = 10;

	virtual const char* className() {
		return "GameObject";
	}	

	virtual void onHit(float xPos, float yPos, float damage) = 0;

	bool isAlive();

protected:
	float xPos;
	float yPos;
	Sprite sprite;
	float speedMovement;
	int life;
	int health;
	static const char* spritePath;
	bool canGoBeyondWalls;
	static const float xScale;
	static const float yScale;
	bool stillExists;
};

#endif
