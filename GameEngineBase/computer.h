#pragma once
#include "gameObject.h"
#include "text.h"

class computer : public gameObject
{
protected:
	text write = text();
	std::string message = "";
	bool screenOpened = false;
	// texture of the opening box
	GLuint frame = 0;

public:
	computer();

	void contextCreated();
	void update();
	void input(char key, int x, int y, int mod);
	void drawScreen();

	~computer();
};

