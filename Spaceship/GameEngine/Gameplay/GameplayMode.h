#pragma once
#include <vector>

class GameObject;

class GameplayMode {
public:
	
	GameplayMode(std::vector<GameObject*> *gameObjects) 
	{ 
		this->gameObjects = gameObjects;
		level = 1;
	}

	~GameplayMode() {
		delete gameObjects;
	}

	virtual void updateGame() {
		this->updateControls();
		this->updateHit();
		this->updateObjects();
	}
	virtual void render() = 0;

protected:
	
	std::vector<GameObject*> *gameObjects;
	virtual void updateControls() = 0;
	virtual void updateHit() = 0;
	virtual void updateObjects() = 0;
	int level;


};