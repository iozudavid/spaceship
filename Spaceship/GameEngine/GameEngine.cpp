#include "GameEngine.h"
#include "IO/Keyboard.h"
#include <algorithm>
#include "Objects/Player.h"
#include "Objects/Enemy.h"
#include "GL/freeglut.h"
#include "Gameplay/SinglePlayerSurvivalMode.h"
#include "IO/TextRenderer.h"

//variable initializers
int GameEngine::SCREEN_WIDTH = 700;
int GameEngine::SCREEN_HEIGHT = 1000;
GLFWwindow* GameEngine::gameWindow = NULL;
double GameEngine::dt = 0;
double GameEngine::lastTime = 0;
GameEngine* GameEngine::m_instanceSingleton = nullptr;


GameEngine::GameEngine() {
	score1 = 0;
	score2 = 0;
	state = START_MENU;
}

GameEngine::~GameEngine() {
	if(gameplayMode!=NULL)
		delete gameplayMode;
}

bool GameEngine::initialise(const char* title) {

	if (!glfwInit()) {
		cout << "init error";
		return false;
	}

	gameWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title, NULL, NULL);

	if (gameWindow == NULL) {
		cout << "gamewindow";
		return false;
	}

	//start setup opengl
	glfwMakeContextCurrent(gameWindow);

	int w, h;

	glfwGetFramebufferSize(gameWindow, &w, &h);

	glfwSwapInterval(1);

	//keyboard handler
	glfwSetKeyCallback(gameWindow, Keyboard::keyCallback);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	if (monitor == NULL) {
		cout << "monitor";
		return false;
	}
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	if (mode == NULL) {
		cout << "mode";
		return false;
	}


	int xPos = (mode->width - SCREEN_WIDTH) / 2;
	int yPos = (mode->height - SCREEN_HEIGHT) / 2;

	glfwGetWindowPos(gameWindow, &xPos, &yPos);

	//start setup gl
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -10, 10);
	glDepthRange(-10, 10);
	glMatrixMode(GL_MODELVIEW);


	//alpha
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	lastTime = glfwGetTime();

	backSprite = new Sprite("res/background.jpg", SCREEN_WIDTH, SCREEN_HEIGHT);
	moveBackground = 0;


	return true;
}


void GameEngine::update() {

	backSprite->update();

	for (GameObject* obj : this->gameObjectsToBeDeleted) 
		this->removeGameObject(obj);
	
	this->eraseToDeleteGameObject();

	for (GameObject* obj : this->gameObjectsToBeInserted)
		this->addGameObject(obj);
	this->eraseToInsertGameObject();

	
	for (GameObject* obj : this->gameObjects)
		obj->update();
	double now = glfwGetTime();
	dt = now - lastTime;
	lastTime = now;
	glfwPollEvents();

}

void GameEngine::beginRender() {
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, backSprite->getTexture().getID());
	glLoadIdentity();

	//translate
	glTranslatef(0, -moveBackground, 0);
	moveBackground += 0.2;

	if (moveBackground >= 2 * SCREEN_HEIGHT)
		moveBackground = 0;
	
	//rotate


	//scale
	glScalef(1, 4, 1);

	//render
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);		glVertex2f(0, 0);
	glTexCoord2f(1, 0);		glVertex2f(SCREEN_WIDTH, 0);
	glTexCoord2f(1, 1);		glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT);
	glTexCoord2f(0, 1);		glVertex2f(0, SCREEN_HEIGHT);

	glEnd();

	glDisable(GL_TEXTURE_2D);

	for (GameObject* obj : this->gameObjects)
			obj->render();
	
}

void GameEngine::endRender() {
	glfwSwapBuffers(gameWindow);
}

double GameEngine::getDT() {
	return dt;
}


void GameEngine::addGameObject(GameObject* obj) {
		this->gameObjects.push_back(obj);
}


bool GameEngine::removeGameObject(GameObject* gameObj) {
	int index = -1;
	for (int i = 0; i < this->gameObjects.size(); i++) {
		if (areEquals(gameObjects.at(i), gameObj)) {
			index = i;
			break;
		}
	}
	if (index == -1) {
 		cout << "Object not found";
		return false;
	}
	this->gameObjects.erase(gameObjects.begin() + index);
	return true;
}

void GameEngine::addToInsertGameObject(GameObject* object) {
	this->gameObjectsToBeInserted.push_back(object);
}

void GameEngine::addToDeleteGameObject(GameObject* obj) {
	this->gameObjectsToBeDeleted.push_back(obj);
}

void GameEngine::eraseToDeleteGameObject() {
	for (auto obj : this->gameObjectsToBeDeleted) {
		//free bullet memory
		if(strcmp(obj->className(),"Bullet") == 0 || strcmp(obj->className(), "AlienBullet") == 0)
			delete obj;
	}
	this->gameObjectsToBeDeleted.clear();
}

void GameEngine::eraseToInsertGameObject() {
	this->gameObjectsToBeInserted.clear();
}

bool GameEngine::areEquals(GameObject* obj1, GameObject* obj2) {

	if (obj1->getX() != obj2->getX())
		return false;

	if (obj1->getY() != obj2->getY())
		return false;

	if (obj1->getSpriteXScale() != obj2->getSpriteXScale())
		return false;

	if (obj1->getSpriteYScale() != obj2->getSpriteYScale())
		return false;

	return true;
}


void GameEngine::start() {
	//this->beginRender();
	std::string score1S = "Score";
	std::string score2S = "Score";
	TextRenderer* startSingleText = new TextRenderer("Enter to start", 0.065f);
	TextRenderer* restartSingleText = new TextRenderer("Enter to restart", 0.06f);
	TextRenderer* quitText = new TextRenderer("Esc to quit", 0.05f);
	TextRenderer* score1Text = new TextRenderer(score1S, 0.055);

	while (!stopEngine) {

		switch (state) {
		case START_MENU:
			glfwPollEvents();
			this->beginRender();
			startSingleText->render(GameEngine::SCREEN_WIDTH/2.f - (startSingleText->getTextWidth() / 2.0f), GameEngine::SCREEN_HEIGHT/2.f - (startSingleText->getTextHeight() / 2.0f));
		//	startDoubleText->render(GameEngine::SCREEN_WIDTH/2.f - (startDoubleText->getTextWidth() / 2.0f), GameEngine::SCREEN_HEIGHT/2.f - startSingleText->getTextHeight() - 10 - (startDoubleText->getTextHeight() / 2.0f));
			quitText->render(GameEngine::SCREEN_WIDTH / 2.f - (quitText->getTextWidth() / 2.0f), GameEngine::SCREEN_HEIGHT / 2.f - startSingleText->getTextHeight() - 10 - (quitText->getTextHeight() / 2.0f));
			this->endRender();
			if (Keyboard::keyPressed(GLFW_KEY_ENTER)) {
				state = PLAYING;
				gameplayMode = new SinglePlayerSurvivalMode(&gameObjects);
			}
			if (Keyboard::keyPressed(GLFW_KEY_ESCAPE)) {
				stop();
			}
			break;
		case PLAYING:
			
			this->gameplayMode->updateGame();

			if (state == GAME_OVER_1)
				break;

			this->update();

			this->beginRender();

			this->gameplayMode->render();

			this->endRender();
			break;
		case GAME_OVER_1:
			glfwPollEvents();
			this->beginRender();
			if (score1S != "Score " + std::to_string(score1)) {
				score1S = "Score " + std::to_string(score1);
				score1Text->changeText(score1S);
			}
			score1Text->render(GameEngine::SCREEN_WIDTH / 2.f - (score1Text->getTextWidth() / 2.0f), GameEngine::SCREEN_HEIGHT / 2.f + restartSingleText->getTextHeight() + 10 - (score1Text->getTextHeight() / 2.0f));
			restartSingleText->render(GameEngine::SCREEN_WIDTH / 2.f - (restartSingleText->getTextWidth() / 2.0f), GameEngine::SCREEN_HEIGHT / 2.f - (restartSingleText->getTextHeight() / 2.0f));
			//restartDoubleText->render(GameEngine::SCREEN_WIDTH / 2.f - (restartDoubleText->getTextWidth() / 2.0f), GameEngine::SCREEN_HEIGHT / 2.f - restartSingleText->getTextHeight() - 10 - (restartDoubleText->getTextHeight() / 2.0f));
			quitText->render(GameEngine::SCREEN_WIDTH / 2.f - (quitText->getTextWidth() / 2.0f), GameEngine::SCREEN_HEIGHT / 2.f - restartSingleText->getTextHeight() - 10 - (quitText->getTextHeight() / 2.0f));

			this->endRender();
			if (Keyboard::keyPressed(GLFW_KEY_ENTER)) {
				state = PLAYING;
				gameplayMode = new SinglePlayerSurvivalMode(&gameObjects);
			}
			if (Keyboard::keyPressed(GLFW_KEY_ESCAPE)) {
				stop();
			}
			break;
		}

	}

	delete startSingleText;
	delete restartSingleText;
	delete quitText;

}

void GameEngine::stop() {
	stopEngine = true;
	this->update();
	this->eraseGameObjects();
	delete gameplayMode;
}

void GameEngine::eraseGameObjects() {
	for (auto obj : this->gameObjects) {
		if (strcmp(obj->className(), "Bullet") == 0 || strcmp(obj->className(), "AlienBullet") == 0)
			delete obj;
	}
	this->gameObjects.clear();
}

void GameEngine::gameOver(int score) {
	this->update();
	this->eraseGameObjects();
	gameplayMode = NULL;
	state = GAME_OVER_1;
	score1 = score;
}
