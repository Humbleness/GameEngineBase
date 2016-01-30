#pragma once

#include <stdio.h>
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class draw
{
public:
	// draw a rectangle using width and height
	static void quad(float x, float y, float w, float h, GLuint texture);
	static void quad(float x, float y, float w, float h, GLuint texture, float r, float g, float b, float a);
	static void quad(float x, float y, float w, float h, GLuint texture, float r, float g, float b, float a, int spriteX, int spriteY, int spriteSize, int spriteOffset);
	static void quad(float x, float y, float w, float h, float r, float g, float b, float a);

	// draw a texture with randomly changing colors
	// if changeColorsByVertices is true, each vertex will have its colors changed instead of just applying it to the entire plane
	static void flashingQuad(float x, float y, float w, float h, float speed, bool changeColorsByVertices, GLuint texture);
	static void flashingQuad(float x, float y, float w, float h, float speed, bool changeColorsByVertices, GLuint texture, int spriteX, int spriteY, int spriteSize, int spriteOffset);

	// draw an amorphous shape using defined coordinates
	static void polygon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float r, float g, float b, float a);
	static void render();
};

