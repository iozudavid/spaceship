#include "TextRenderer.h"
#include "../Graphics/Sprite.h"

TextRenderer::TextRenderer(std::string text, float _xScale, float _yScale) {
	this->xScale = _xScale;
	this->yScale = _yScale;
	load(text);
}

TextRenderer::TextRenderer(std::string text, float _xScale) {
	this->xScale = _xScale;
	this->yScale = _xScale;
	load(text);

}

void TextRenderer::changeText(std::string text) {
	this->images.clear();
	this->load(text);
}

void TextRenderer::load(std::string text) {
	for (char c : text) {
		if (c == ' ') {
			c = '!';
		}
		std::string relativePath = "res/font/";
		relativePath += c;
		std::string fileExt = ".png";
		std::string finalPath = relativePath + fileExt;
		Sprite s = Sprite(finalPath, xScale, yScale);
		this->images.push_back(s);
	}
}

void TextRenderer::render(int xPos, int yPos) {
	int xToRender = xPos;
	int yToRender = yPos;
	for (Sprite s : images) {
		s.render(xToRender, yToRender);
		xToRender += (Sprite::genericSize * s.getXScale());
	}
}

float TextRenderer::getTextWidth() {
	float width = 0;
	for (Sprite s : images) 
		width += (Sprite::genericSize * s.getXScale());
	return width;
}

float TextRenderer::getTextHeight() {
	float height = 0;
	for (Sprite s : images) {
		float m = (Sprite::genericSize * s.getYScale());
		height = std::fmaxf(height, m);
	}
	return height;
}
