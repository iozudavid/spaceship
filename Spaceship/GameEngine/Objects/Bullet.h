#pragma once
#include "GameObject.h"
#include "../utils/RelativePosition.h"
#include "../GameEngine.h"

class Player;

class Bullet : public GameObject {
public:
	Bullet(bool goBeyond, Player* shooter);
	Bullet(float xPos, float yPos, bool goBeyond, Player* shooter);
	~Bullet(){}

	void increaseDamage();
	void decreaseDamage();
	void update() override;

	const char* className() override{
		return "Bullet";
	}

	static float getXScale();
	static float getYScale();

	void onHit(float xPos, float yPos, float damage) override;

	float getDamage();

	Player* getShooter();

protected:
	Player* shooter;

private:
	static const char* spriteName;
	float damage;
	static const float xScale;
	static const float yScale;
};
