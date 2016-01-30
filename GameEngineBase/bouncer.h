#pragma once
#include "enemy.h"

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class bouncer : public enemy
{
protected:
	bool posX = true;
	bool posY = true;
public:
	bouncer(float x, float y);

	void update();

	~bouncer();
};

