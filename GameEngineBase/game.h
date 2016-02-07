#pragma once

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <array>
#include <boost/shared_ptr.hpp>
#include <stdio.h>

#include "gameObject.h"
#include "player.h"
#include "tile.h"
#include "draw.h"
#include "physics.h"
#include "loadTexture.h"
#include "bouncer.h"
#include "tileLoader.h"
#include "computer.h"



class game
{

protected:
	std::vector<boost::shared_ptr<gameObject>> objects;
	boost::shared_ptr<player> ply;

public:
	

	game();

	// called once the openGL context has been fully initialized (so you can load textures etc)
	void contextCreated();

	void update();
	void recieveInput(char key, int x, int y, int mod);
	void keyUp(char key, int x, int y);
	void updateObjs();

	// returns in this format
	// pos0 = is obj sharing coords with another tile to the LEFT?
	// pos1 = is is sharing to the TOP?
	// pos2 = is it sharing to the RIGHT?
	// pos3 = is it sharing to the BOTTEM?
	std::array<bool, 4> areSharingCoordinates(boost::shared_ptr<gameObject> obj);
	// draw the black polygons preventing you from seeing
	void blockVisionAndRender();

	// return the size of a default tile
	static float TS() { return 80; }

	~game();

private:
	void render();
};

