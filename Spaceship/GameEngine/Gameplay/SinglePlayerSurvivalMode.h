#pragma once
#include "GameplayMode.h"

class Player;
class Enemy;
class GameStats;


class SinglePlayerSurvivalMode : public GameplayMode{
public:

	SinglePlayerSurvivalMode(std::vector<GameObject*> *gameObjects);
	
	~SinglePlayerSurvivalMode() {
		if(player!=NULL)
			delete player;
		if(enemy1!=NULL)
			delete enemy1;
		if (enemy2 != NULL)
			delete enemy2;
		if (enemy3 != NULL)
			delete enemy3;
		if (enemy4 != NULL)
			delete enemy4;
	}

	void updateGame() override;
	void render() override;

protected:
	//single player
	Player* player;
	//a maximum of 4 enemies will be displayed on screen
	Enemy *enemy1, *enemy2, *enemy3, *enemy4;
	GameStats *gameStats;

	void updateHit() override;
	void updateObjects() override;
	void updateControls() override;
	void initEnemies();

	int lastAmmo, lastLevel, lastScore;

};
