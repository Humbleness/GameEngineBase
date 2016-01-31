#pragma once

#include <string>
#include "gameObject.h"

class text : public gameObject
{
protected:
	GLuint font;
	GLint textureW, textureH;
	float size = 64;
public:
	text();

	void contextCreated();
	void draw(std::string text, float r, float g, float b, float a);

	// the rules for the font sheet are as follows:
	// 45 units wide, 2 units tall (one unit = the size you define here) with 1 pixel space between each character (feel free to put a grid here)
	// spaces 1-26 are letters 'A'-'Z', bottem row lowercase, top row uppercase
	// spaces 27-37 are numbers '1'-'9', as well as '0', '-', and '=' in the bottem row, and their shift counterparts in the top
	// spaces 38-43 is ','(comma), '.', ';', '''(apostrophe), and '\' and their shift counterparts
	// space 44 is '?' under and '/' over
	// space 45 is completely blank, above and below
	void setFont(std::string path);

	void setSize(float size) { this->size = size; }
	float getSize() { return this->size; }

	~text();
};

