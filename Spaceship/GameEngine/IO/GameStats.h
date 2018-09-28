#pragma once
#include <vector>
#include <string>
#include "TextRenderer.h"

class GameStats {
public:
	
	GameStats(std::vector<std::string> stats);
	~GameStats();
	void render();
	void changeStats(std::vector<std::string> stats);

private:
	std::vector<std::string> stats;
	void load();
	void reload();
	std::vector<TextRenderer*> gameStatsToRender;

};