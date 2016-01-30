#include "loadTexture.h"
#include <iostream>


loadTexture::loadTexture() {}

// remember to include file extension in the path (path is relative to ThisDirectory/res)
GLuint loadTexture::at(std::string path) {
	path = "res\\" + path;

	GLuint texture = SOIL_load_OGL_texture(
		path.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if (texture == 0) return false;

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texture;
}

loadTexture::~loadTexture() {}
