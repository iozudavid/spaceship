#pragma once
#include <tuple>

class Rect {

public:

	Rect(int x, int y, int width, int height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	~Rect() {}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	int getWidth() {
		return width;
	}

	int getHeight() {
		return height;
	}

	std::tuple<int, int> getBottomLeftCorner() {
		return std::make_tuple(x, y);
	}

	std::tuple<int, int> getBottomRightCorner() {
		return std::make_tuple(x + width, y);
	}

	std::tuple<int, int> getTopLeftCorner() {
		return std::make_tuple(x, y + height);
	}

	std::tuple<int, int> getTopRightCorner() {
		return std::make_tuple(x + width, y + height);
	}

private:

	int x, y, width, height;



};