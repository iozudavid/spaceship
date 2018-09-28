#include "Texture.h"


Texture::Texture() {
	this->id = -1;
}

Texture::Texture(int id) {
	this->id = id;

	if (!this->getTextureParams()) 
		cout << "Error loading id: " << this->id;
	
		

}

Texture::Texture(string path) {
	this->id = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y);
	
	if (!this->getTextureParams())
		cout << "Error loading path: " << this->imagePath;

	
}

Texture::~Texture() {}

bool Texture::getTextureParams() {

	if (this->id > 0) {

		int mipLVL = 0;
		glBindTexture(GL_TEXTURE_2D, id);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLVL, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLVL, GL_TEXTURE_HEIGHT, &height);
		return true;
	}

	return false;

}


//getters

int Texture::getID() {
	return this->id;
}

int Texture::getHeight() {
	return this->height;
}

int Texture::getWidth() {
	return this->width;
}

string Texture::getImagePath() {
	return this->imagePath;
}

int Texture::getRGB(int xPos, int yPos) {

	if (this->id > 0) {

		int mipLVL = 0;
		glBindTexture(GL_TEXTURE_2D, id);
		unsigned char pixel[4];
		glReadPixels(xPos, yPos, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

		return ((int)pixel[0] + (int)pixel[1] + (int)pixel[2]);
	}
	return -1;
}

