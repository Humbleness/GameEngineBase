#include "loadTexture.h"

#include "draw.h"

// draw with a texture
void draw::quad(float x, float y, float w, float h, GLuint tex) {
	draw::quad(x, y, w, h, tex, 255, 255, 255, 255);
}

// draw with a texture, but still apply color
void draw::quad(float x, float y, float w, float h, GLuint tex, float r, float g, float b, float a) {
	quad(x, y, w, h, tex, r, g, b, a, -1, -1, -1, -1);
}

// draw a specific portion from a texture (useful for sprites) with color
void draw::quad(float x, float y, float w, float h, GLuint texture, float r, float g, float b, float a, int spriteX, int spriteY, int spriteSize, int spriteOffset) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	if (a > 255) a = 255;
	r /= 255;
	g /= 255;
	b /= 255;
	a /= 255;

	float coordX1 = spriteX;
	float coordY1 = spriteY;
	float coordX2 = 1;
	float coordY2 = 1;

	if (spriteX < 0 || spriteY < 0 || spriteSize < 1 || spriteOffset < 0) {
		coordX1 = 0;
		coordY1 = 0;
	} else {
		glBindTexture(GL_TEXTURE_2D, texture);
		GLint textureW, textureH;
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureW);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureH);

		
		coordX1 += (spriteX * spriteSize + ((spriteOffset - 1) * (spriteX)));
		coordX2 = coordX1 + spriteSize;
		coordX1 /= textureW;
		coordX2 /= textureW;

		coordY1 += (spriteY * spriteSize + ((spriteOffset - 1) * (spriteY)));
		coordY2 = coordY1 + spriteSize;
		coordY1 /= textureH;
		coordY2 /= textureH;
	}


	glEnable(GL_TEXTURE_2D);

	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix(); {
		glTranslatef(0, 0, -2);
		glBegin(GL_QUADS); {
			glColor3f(r, g, b);

			glTexCoord2f(coordX1, coordY1);
			glVertex3f(x, y, 1);

			glTexCoord2f(coordX1, coordY2);
			glVertex3f(x, y + h, 1);

			glTexCoord2f(coordX2, coordY2);
			glVertex3f(x + w, y + h, 1);

			glTexCoord2f(coordX2, coordY1);
			glVertex3f(x + w, y, 1);
		} glEnd();
	} glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

// draw with no texture
void draw::quad(float x, float y, float w, float h, float r, float g, float b, float a) {
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	if (a > 255) a = 255;
	r /= 255;
	g /= 255;
	b /= 255;
	a /= 255;

	glPushMatrix(); {
		glTranslatef(0, 0, -2);
		glBegin(GL_QUADS); {
			glColor3f(r, g, b);

			glVertex3f(x, y, 1);
			glVertex3f(x, y + h, 1);
			glVertex3f(x + w, y + h, 1);
			glVertex3f(x + w, y, 1);
		} glEnd();
	} glPopMatrix();
}

void draw::flashingQuad(float x, float y, float w, float h, float speed, bool changeColorsByVertices, GLuint texture) {
	draw::flashingQuad(x, y, w, h, speed, changeColorsByVertices, texture, -1, -1, -1, -1);
}

void draw::flashingQuad(float x, float y, float w, float h, float speed, bool changeColorsByVertices, GLuint texture, int spriteX, int spriteY, int spriteSize, int spriteOffset) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float coordX1 = spriteX;
	float coordY1 = spriteY;
	float coordX2 = 1;
	float coordY2 = 1;

	if (spriteX < 0 || spriteY < 0 || spriteSize < 1 || spriteOffset < 0) {
		coordX1 = 0;
		coordY1 = 0;
	}
	else {
		glBindTexture(GL_TEXTURE_2D, texture);
		GLint textureW, textureH;
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureW);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureH);


		coordX1 += (spriteX * spriteSize + ((spriteOffset - 1) * (spriteX)));
		coordX2 = coordX1 + spriteSize;
		coordX1 /= textureW;
		coordX2 /= textureW;

		coordY1 += (spriteY * spriteSize + ((spriteOffset - 1) * (spriteY)));
		coordY2 = coordY1 + spriteSize;
		coordY1 /= textureH;
		coordY2 /= textureH;
	}

	float time = (float)glutGet(GLUT_ELAPSED_TIME);
	float r = sin(time / speed) / 2 + 0.5f;
	float g = cos(time / speed) / 2 + 0.5f;
	float b = sin(time / speed) / 2 + 0.5f;


	glEnable(GL_TEXTURE_2D);

	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix(); {
		glTranslatef(0, 0, -2);
		if (changeColorsByVertices) {
			glBegin(GL_QUADS); {
				glColor3f(r, g, b);
				glTexCoord2f(coordX1, coordY1);
				glVertex3f(x, y, 1);

				glColor3f(g, r, b);
				glTexCoord2f(coordX1, coordY2);
				glVertex3f(x, y + h, 1);

				glColor3f(g, b, r);
				glTexCoord2f(coordX2, coordY2);
				glVertex3f(x + w, y + h, 1);

				glColor3f(b, r, g);
				glTexCoord2f(coordX2, coordY1);
				glVertex3f(x + w, y, 1);
				glEnd();
			}
		}
		else {
			glBegin(GL_QUADS); {
				glColor3f(r, g, b);

				glTexCoord2f(coordX1, coordY1);
				glVertex3f(x, y, 1);

				glTexCoord2f(coordX1, coordY2);
				glVertex3f(x, y + h, 1);

				glTexCoord2f(coordX2, coordY2);
				glVertex3f(x + w, y + h, 1);

				glTexCoord2f(coordX2, coordY1);
				glVertex3f(x + w, y, 1);
				glEnd();
			}
		}
	} glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void draw::polygon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float r, float g, float b, float a) {
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	if (a > 255) a = 255;
	r /= 255;
	g /= 255;
	b /= 255;
	a /= 255;

	glPushMatrix(); {
		glTranslatef(0, 0, -2);
		glBegin(GL_POLYGON); {
			glColor3f(r, g, b);

			//glVertex3f(x1, y1, 1);
			//glVertex3f(x1, y2, 1);
			//glVertex3f(x2, y2, 1);
			//glVertex3f(x2, y1, 1);
			glVertex3f(x1, y1, 1);
			glVertex3f(x2, y2, 1);
			glVertex3f(x3, y3, 1);
			glVertex3f(x4, y4, 1);
		} glEnd();
	} glPopMatrix();
}

// call this after you have FINISHED drawing elements to render it to the screen (should only be called once per frame (I think maybe, I have no fucking clue when you use this actually))
void draw::render() {
	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}