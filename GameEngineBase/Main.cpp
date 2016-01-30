/*
 * Copyright (c) 2009, 2014 University of Michigan, Ann Arbor.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of Michigan, Ann Arbor. The name of the University 
 * may not be used to endorse or promote products derived from this 
 * software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Authors: Manoj Rajagopalan, Sugih Jamin
*/
#include <stdio.h>
#include <stdlib.h>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "draw.h"
#include "player.h"
#include "game.h"

#define WIDTH 800
#define HEIGHT 600
#define TITLE "Lighthouse Expirement"
#define TIME 10 // how many milliseconds between updates


GLdouble width, height;   /* window width and height */
int wd;                   /* GLUT window handle */
int ends[2][2];       /* array of 2D points */

game instance = game();		/* where all the juicy game stuff goes */

GLfloat     rtri;                       // Angle For The Triangle ( NEW )
GLfloat     rquad;                      // Angle For The Quad     ( NEW )

// draw.cpp draw.h player.cpp player.h game.cpp game.h  gameObject.cpp gameObject.h tile.cpp tile.h tileLoader.cpp tileLoader.h physics.cpp physics.h loadTexture.cpp loadTexture.h 

/* Program initialization NOT OpenGL/GLUT dependent,
   as we haven't created a GLUT window yet */
void init(void)
{
  width  = 1280.0;                 /* initial window width and height, */
  height = 800.0;                  /* within which we draw. */
  ends[0][0] = (int)(0.25*width);  /* (0,0) is the lower left corner */
  ends[0][1] = (int)(0.75*height);
  ends[1][0] = (int)(0.75*width);
  ends[1][1] = (int)(0.25*height);

 // gameObject objs = new gameObject[101];

  return;
}

/* Callback functions for GLUT */



/* Draw the window - this is where all the GL actions are */
void display(void)
{
	//draw::quad(100, 100, 500, 300);
	return;
}



/* Called when window is ,
   also when window is first created,
   before the first call to display(). */
void reshape(int w, int h)
{
  /* save new screen dimensions */
  width = (GLdouble) w;
  height = (GLdouble) h;

  /* tell OpenGL to use the whole window for drawing */
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);

  /* do an orthographic parallel projection with the coordinate
     system set to first quadrant, limited by screen/window size */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, width, 0.0, height, 0, 100);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glTranslatef(0.0f, 0.0f, -1.0f);
  glutSwapBuffers();
  
  return;
}

// keyboard down
void kbd(unsigned char key, int x, int y)
{
  switch((char)key) {
  case 'q':
  case 27:
    glutDestroyWindow(wd);
    exit(0);
  default:
    break;
  }

  glutGetModifiers();
  enum modifier { off, shift, ctrl, alt };
  int mod = 0;
  if (glutGetModifiers() & GLUT_ACTIVE_SHIFT) mod = modifier::shift;
  else if (glutGetModifiers() & GLUT_ACTIVE_CTRL) mod = modifier::ctrl;
  else if (glutGetModifiers() & GLUT_ACTIVE_ALT) mod = modifier::alt;
  else mod = modifier::off;
  if (mod == modifier::ctrl) key += 96;

  instance.recieveInput(key, x, y, mod);

  return;
}

// keyboard up
void kbu(unsigned char key, int x, int y) {
	instance.keyUp(key, x, y);
}

// call update() function every specified milliseconds
void update(int in) {
	instance.update();
	glutTimerFunc(TIME, update, 0);
}

void createWindow(int w, int h, char *title) {

	/* specify the display to be single
	buffered and color as RGBA values */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	/* set the initial window size */
	glutInitWindowSize((int)w, (int)h);

	/* create the window and store the handle to it */
	wd = glutCreateWindow(title /* title */);
	
}


int main(int argc, char *argv[])
{
	  /* perform initialization NOT OpenGL/GLUT dependent,
		 as we haven't created a GLUT window yet */
	init();

	/* initialize GLUT, let it extract command-line
	GLUT options that you may provide
	- NOTE THE '&' BEFORE argc */
	glutInit(&argc, argv);

	createWindow(WIDTH, HEIGHT, TITLE);

	  /* register function to handle window resizes */
	glutReshapeFunc(reshape);
	
	  /* register keyboard event processing function */
	glutKeyboardFunc(kbd);
	glutKeyboardUpFunc(kbu);
	glutTimerFunc(TIME, update, 0);

	  /* register function that draws in the window */
	glutDisplayFunc(display);

	  /* init GL */
	glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3.0);

	instance.contextCreated();

	//////printf("%s\n", gluErrorString(glGetError()));
	  /* start the GLUT main loop */
	glutMainLoop();


	exit(0);
}