#include "bouncer.h"
#include "gameObject.h"

#include <stdio.h>

const float SPEED = 4.0f;

bouncer::bouncer(float x, float y) {
	this->setVariables(x, y, 15, 15, 255, 175, 0, 255, false, "");
}

void bouncer::update() {
	if (this->posX) this->x += SPEED;
	else this->x -= SPEED;
	if (this->posY) this->y += SPEED;
	else this->y -= SPEED;

	if ((this->x + this->w) > glutGet(GLUT_WINDOW_WIDTH)) this->posX = false;
	if ((this->y + this->h) > glutGet(GLUT_WINDOW_HEIGHT)) this->posY = false;
	if (this->x < 0) this->posX = true;
	if (this->y < 0) this->posY = true;
}

bouncer::~bouncer() {}
