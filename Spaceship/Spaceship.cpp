#include "GameEngine/GameEngine.h"
#include "GameEngine/Graphics/Sprite.h"
#include "GameEngine/IO/Keyboard.h"
#include "GameEngine/Objects/Player.h"
#include "GameEngine/Objects/Bullet.h"
#include "GameEngine/Objects/Enemy.h"
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

int main() {
	GameEngine* gameEngine = gameEngine->getInstance();
	const char* title = "SpaceShip Game";
	cout << gameEngine->initialise(title);
/*
	Player* player = new Player(false);
	Enemy* enemy = new Enemy(0, GameEngine::SCREEN_HEIGHT ,true, 1);
	Enemy* enemy2 = new Enemy(0.25 * GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT, true, 1);
	Enemy* enemy3 = new Enemy(0.5 * GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT, true, 1);
	Enemy* enemy4 = new Enemy(0.75 * GameEngine::SCREEN_WIDTH, GameEngine::SCREEN_HEIGHT, true, 1);
*/

	gameEngine->start();
	return 0;
}