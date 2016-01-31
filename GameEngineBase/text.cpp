#include "text.h"
#include "loadTexture.h"
#include "draw.h"


text::text() {}

void text::contextCreated() {
	this->setFont("fonts\\default.png");
	this->a = 0;
}

void text::setFont(std::string path) {
	this->font = loadTexture::at(path);
	glBindTexture(GL_TEXTURE_2D, font);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureW);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureH);
}

void text::draw(std::string text, float r, float g, float b, float a) {
	// define these outside the loop in case someone uses \n
	float textY = this->getY();
	float textX = this->getX();
	float xPos = 0;
	for (int i = 0; i < (int)text.length(); i++) {
		char c = text.at(i);

		// the coordinates X and Y in the font sheet
		int cX = 0;
		int cY = 0;

		if (isupper(c) && isalpha(c)) cY = 1; else cY = 0;

		switch (tolower(c)) {
			case 'a': cX = 0; break;
			case 'b': cX = 1; break;
			case 'c': cX = 2; break;
			case 'd': cX = 3; break;
			case 'e': cX = 4; break;
			case 'f': cX = 5; break;
			case 'g': cX = 6; break;
			case 'h': cX = 7; break;
			case 'i': cX = 8; break;
			case 'j': cX = 9; break;
			case 'k': cX = 10; break;
			case 'l': cX = 11; break;
			case 'm': cX = 12; break;
			case 'n': cX = 13; break;
			case 'o': cX = 14; break;
			case 'p': cX = 15; break;
			case 'q': cX = 16; break;
			case 'r': cX = 17; break;
			case 's': cX = 18; break;
			case 't': cX = 19; break;
			case 'u': cX = 20; break;
			case 'v': cX = 21; break;
			case 'w': cX = 22; break;
			case 'x': cX = 23; break;
			case 'y': cX = 24; break;
			case 'z': cX = 25; break;

			case '1': cX = 26; cY = 0; break;
			case '2': cX = 27; cY = 0; break;
			case '3': cX = 28; cY = 0; break;
			case '4': cX = 29; cY = 0; break;
			case '5': cX = 30; cY = 0; break;
			case '6': cX = 31; cY = 0; break;
			case '7': cX = 32; cY = 0; break;
			case '8': cX = 33; cY = 0; break;
			case '9': cX = 34; cY = 0; break;
			case '0': cX = 35; cY = 0; break;
			case '!': cX = 26; cY = 1; break;
			case '@': cX = 27; cY = 1; break;
			case '#': cX = 28; cY = 1; break;
			case '$': cX = 29; cY = 1; break;
			case '%': cX = 30; cY = 1; break;
			case '^': cX = 31; cY = 1; break;
			case '&': cX = 32; cY = 1; break;
			case '*': cX = 33; cY = 1; break;
			case '(': cX = 34; cY = 1; break;
			case ')': cX = 35; cY = 1; break;

			case '-': cX = 36; cY = 0; break;
			case '=': cX = 37; cY = 0; break;
			case ',': cX = 38; cY = 0; break;
			case '.': cX = 39; cY = 0; break;
			case ';': cX = 40; cY = 0; break;
			case '\'': cX = 41; cY = 0; break;
			case '\\': cX = 42; cY = 0; break;
			case '_': cX = 36; cY = 1; break;
			case '+': cX = 37; cY = 1; break;
			case '<': cX = 38; cY = 1; break;
			case '>': cX = 39; cY = 1; break;
			case ':': cX = 40; cY = 1; break;
			case '\"': cX = 41; cY = 1; break;
			case '|': cX = 42; cY = 1; break;

			case '?': cX = 43; cY = 0; break;
			case '/': cX = 43; cY = 1; break;

			default: cX = 44; cY = 1; break;
		}

		// width is less then height, multiply that shit by the ratio of height to width
		textX = this->getX() + (xPos * this->getSize() * 0.640625);
		// size is the size that gets rendered, physicalSize is the actual height in pixels of one tile
		int physicalSize = (this->textureH - 1) / 2;
		draw::quad(textX, textY, this->getSize(), this->getSize(), this->font, r, g, b, a, cX, cY, physicalSize, 1);
		if (c == '\n') {
			xPos = 0;
			textY -= this->getSize();
		} else {
			xPos++;
		}
	}
}

text::~text() {}
