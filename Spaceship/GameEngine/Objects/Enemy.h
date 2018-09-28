#ifndef Enemy_Included
#define Enemy_Included
#include "../Graphics/Sprite.h"
#include "Player.h"

class Enemy : public Player {
public:	

	Enemy(bool goBeyond, int life);
	Enemy(float xPos, float yPos, bool goBeyond, int life);
	~Enemy(){}

	const char* className() override {
	   return "Enemy";
	} 

	void update() override;
	void decide();
	void shoot() override;

	static float getXScale();
	static float getYScale();
	bool stillOnMap();

private:
	static const float xScale;
	static const float yScale;
	static const float startY;
	static const char* spriteName;
	double dt;
	double lastTime;
	double changeDt;
	double changeLastTime;
	void(Enemy::*decision) ();
	void init(int lvl);

protected:

	void renderHealth() override;

};
#endif;
