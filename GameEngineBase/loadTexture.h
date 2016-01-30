#pragma once
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "SOIL.h"

#include <string>

class loadTexture
{
public:
	loadTexture();
	
	static GLuint at(std::string path);

	~loadTexture();
};

