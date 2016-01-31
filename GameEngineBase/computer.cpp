#include "computer.h"
#include "loadTexture.h"
#include "draw.h"



computer::computer() {
}

void computer::contextCreated() {
	this->setTexture(loadTexture::at("tiles.png"), 0, 2, 16, 1);
	this->frame = loadTexture::at("message.png");
	write.setFont("fonts\\default.png");
}

void computer::update() {
	draw::flashingQuad(this->getX(), this->getY(), this->getW(), this->getH(), 75, true, this->getTexture(), 1, 2, 16, 1);
	if (screenOpened) drawScreen();
}

void computer::input(char key, int x, int y, int mod) {
	if (key == 'e' || key == 'E') {
		this->screenOpened = true;
	}
	else if (key == 'r')
		this->screenOpened = false;
}

void computer::drawScreen() {
	float scrW = (float)glutGet(GLUT_WINDOW_WIDTH);
	float scrH = (float)glutGet(GLUT_WINDOW_HEIGHT);
	float sizeX = 400;
	float sizeY = 200;
	
	draw::quad((scrW / 2) - (sizeX / 2), (scrH / 2) - (sizeY / 2), sizeX, sizeY, frame);
	write.setX(45);
	write.setY(540);
	write.setSize(16);
	write.draw("The quick brown fox jumped over the lazy dog!\n(but he DIDN'T jump too high?)\nTHE QUICK, BROWN \"FOX\" JUMPED: OVER THE LAZY [DOG].", 40, 0, 0, 255);
}

computer::~computer() {}