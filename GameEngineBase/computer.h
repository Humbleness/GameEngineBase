#pragma once
#include "gameObject.h"

class computer : public gameObject
{
protected:
	std::string message = "";
	bool screenOpened = false;

public:
	computer();

	void contextCreated();
	void update();
	void input(char key, int x, int y, int mod);
	void drawScreen();

	~computer();
};

