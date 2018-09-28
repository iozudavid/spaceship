#pragma once
class RGB {

public:

	RGB(int r, int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

	~RGB(){}

	int getR() {
		return r;
	}

	int getG() {
		return g;
	}

	int getB() {
		return b;
	}

private:
	int r, g, b;

};