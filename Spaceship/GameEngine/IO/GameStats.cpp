#include "GameStats.h"
#include "../GameEngine.h"

GameStats::GameStats(std::vector<std::string> stats) {
	this->stats = stats;
	this->load();
}

GameStats::~GameStats() {
	for (TextRenderer* text : this->gameStatsToRender) 
		delete text;
	this->gameStatsToRender.clear();
}

void GameStats::changeStats(std::vector<std::string> stats) {
	this->stats = stats;
	this->reload();
}

void GameStats::load() {
	for (std::string text : this->stats) {
		TextRenderer* toRender = new TextRenderer(text, 0.05f, 0.05f);
		this->gameStatsToRender.push_back(toRender);
	}	
}

void GameStats::reload() {
	for (int i = 0; i < stats.size(); i++) {
		this->gameStatsToRender.at(i)->changeText(stats.at(i));
	}
}


void GameStats::render() {
	int xPos = GameEngine::SCREEN_WIDTH;
	int yPos = GameEngine::SCREEN_HEIGHT;
	for (TextRenderer* text : this->gameStatsToRender) {
		text->render(xPos - text->getTextWidth(), yPos - text->getTextHeight());
		yPos -= text->getTextHeight();
		yPos -= 10; //padding
	}
}
