#pragma once
#include "GLFW/glfw3.h"
#include "SOIL/src/SOIL.h"
#include <string>
#include <iostream>

using namespace std;

class Texture {
public:

	Texture();
	Texture(int id);
	Texture(string imagePath);

	~Texture();


	int getID();
	int getWidth();
	int getHeight();
	string getImagePath();
	int getRGB(int xPos, int yPos);

private:

	bool getTextureParams();

	int id;
	int width;
	int height;
	string imagePath;
};
