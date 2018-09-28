#pragma once
#include <string>
#include <vector>

class Sprite;

class TextRenderer {
public:
	TextRenderer(std::string text, float xScale, float yScale);
	TextRenderer(std::string text, float xScale);

	void render(int xPos, int yPos);

	float getTextWidth();
	float getTextHeight();
	void changeText(std::string text);

private:
	std::vector<Sprite> images;
	float xScale;
	float yScale;
	void load(std::string text);
};
