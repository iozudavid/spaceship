#pragma once
#ifndef Engine_Included
#define Engine_Included
#include "Objects/GameObject.h"
#include "GLFW/glfw3.h"
#pragma comment(lib, "opengl32.lib")
#include <iostream>
#include <vector>
#include <mutex>
#include "GameState.h"
//#include "Gameplay/SinglePlayerSurvivalMode.h"

class SinglePlayerSurvivalMode;

class GameEngine {
public:

	~GameEngine();

	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	static double getDT();

	static GameEngine* getInstance() {
		return (!m_instanceSingleton) ?
			m_instanceSingleton = new GameEngine :
			m_instanceSingleton;
	}

	bool initialise(const char* title);
	void update();
	void beginRender();
	void endRender();

	void addToInsertGameObject(GameObject* object);

	void addToDeleteGameObject(GameObject* object);

	void start();

	void gameOver(int score);


private:

	GameEngine();

	GameEngine(const GameEngine&);              
	GameEngine& operator=(const GameEngine&);

	static GameEngine *m_instanceSingleton;

	static GLFWwindow* gameWindow;
	static double dt;
	static double lastTime;
	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> gameObjectsToBeDeleted;
	std::vector<GameObject*> gameObjectsToBeInserted;

	bool removeGameObject(GameObject* object);
	void eraseToDeleteGameObject();
	void addGameObject(GameObject* object);
	void eraseToInsertGameObject();
	void eraseGameObjects();

	Sprite* backSprite;
	SinglePlayerSurvivalMode* gameplayMode;


	bool areEquals(GameObject* obj1, GameObject* obj2);

	float moveBackground;
	bool stopEngine = false;

	GameState state;

	void stop();

	int score1;
	int score2;

};

#endif
