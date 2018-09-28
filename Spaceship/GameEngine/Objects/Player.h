#pragma once
#ifndef Player_Included
#define Player_Included
#include "../Graphics/Sprite.h"
#include "GameObject.h"
#include "../GameEngine.h"
#include "../utils/RGB.h"
#include "../utils/Rect.h"

class Player : public GameObject {
public:

	Player(bool goBeyond);
	Player(float xPos, float yPos, bool goBeyond);
	~Player(){}

	const char* className() override {
		return "Player";
	}

	static float getXScale();
	static float getYScale();
	virtual void shoot();
	void render() override;
	void onHit(float xPos, float yPos, float damage) override;

	int getBullets();
	void setBullets(int blt);

	int getScore();
	void increaseScore();
	void setScore(int s);

protected:

	static const char* spriteName;
	static const float startX;
	static const float startY;
	static const float xScale;
	static const float yScale;

	//explosion projected x seconds
	const int secondsDamageOnHit = 2;
	//count x seconds
	float explosionDT;
	
	int bullets;
	int score;


	virtual void renderHealth();
	void renderHealthPortion(Rect* rect, RGB* color);

};

#endif
