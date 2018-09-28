#pragma once
#include "Bullet.h"

class AlienBullet : public Bullet {
	
public: 
	AlienBullet(bool goBeyond);
	AlienBullet(float xPos, float yPos, bool goBeyond);
	~AlienBullet(){}

	void update() override;

	const char* className() override {
		return "AlienBullet";
	}

	static float getXScale();
	static float getYScale();

protected:
	static const char* spriteName;
	static const float xScale;
	static const float yScale;


};