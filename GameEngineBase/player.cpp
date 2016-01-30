#include "player.h"
#include "draw.h"
#include "gameObject.h"
#include "physics.h"
#include "loadTexture.h"
#include "simulated.h"

#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <typeinfo>

const float SPEED = 2.75f;

player::player(float x, float y, float width, float height) {
	//enableGravity();
}

void player::input(char key, int x, int y, int mod) {
	enum modifier { off, shift, ctrl, alt };
	key = tolower(key);
	switch (key) {
		case 'w':	
			if (mod == modifier::shift) this->velPosY = 0.2f;
			else if (mod == modifier::ctrl) this->velPosY = 1.75f;
			else this->velPosY = 1.0f;
			this->wDown = true; 
			break;

		case 'a':
			if (mod == modifier::shift) this->velNegX = .2f;
			else if (mod == modifier::ctrl) this->velNegX = 1.75f;
			else this->velNegX = 1;
			this->aDown = true;
			break;

		case 's':
			if (mod == modifier::shift) this->velNegY = 0.2f;
			else if (mod == modifier::ctrl) this->velNegY = 1.75f;
			else this->velNegY = 1.0f;
			this->sDown = true;
			break;

		case 'd':
			if (mod == modifier::shift) this->velPosX = .2f;
			else if (mod == modifier::ctrl) this->velPosX = 1.75f;
			else this->velPosX = 1;
			this->dDown = true;
			break;
	}
}

void player::keyUp(char key, int x, int y) {
	key = tolower(key);
	switch (key) {
		case 'w':	this->wDown = false; velPosY = 0;		break;
		case 'a':	this->aDown = false; this->velNegX = 0;	break;
		case 's':	this->sDown = false; velNegY = 0;		break;
		case 'd':	this->dDown = false; this->velPosX = 0;	break;
	}
}

// remove all objects from vector
void player::clearObjs() { objs.clear(); }

void player::advanceFrame() {
	if (this->wDown || this->aDown || this->sDown || this->dDown) {
		frameNumber++;
	}
	
	else {
		frameNumber = 0;
		this->setSpriteX(0);
	}

	switch ((int)frameNumber) {
		case 1:
			this->setSpriteX(1);
			break;
		case 25:
			this->setSpriteX(2);
			break;
		case 49:
			frameNumber = 0;
			break;
	}
}

void player::update() {
	move(velPosX - velNegX, velPosY - velNegY);
	advanceFrame();
}

// returns true if moved succesfully, false if a collision is encountered and cannot move
bool player::move(float x, float y) {
	// check collisions
	bool canMoveX = true;
	bool canMoveY = true;

	for (int i = 0; i < (int)objects.size(); i++) {
		boost::shared_ptr<gameObject> go = objects.at(i);
		if (go->collides()) {
			// set to X values
			simulated sim = simulated(this->getX() + (x * SPEED), this->getY(), w, h);

			// check X direction
			if (physics::collides(sim, *go)) {
				canMoveX = false;
			
				// if ply is to the left of the object and colliding, move it as close as possible
				if (this->getX() < go->getX()) this->x = go->getX() - this->getW();
				// to the right...
				if (this->getX() > go->getX()) this->x = go->getX() + go->getW();
			}

			// set to Y values
			sim.setX(this->x);
			sim.setY(this->getY() + y * SPEED);
			
			// check Y direction
			if (physics::collides(sim, *go)) {
				canMoveY = false;

				// if ply is underneath of the object and colliding, move it as close as possible
				if (this->getY() < go->getY()) this->y = go->getY() - this->getH();
				// and over...
				if (this->getY() > go->getY()) this->y = go->getY() + go->getH();
			}
		}
	}

	// move
	if (canMoveX) this->x += x * SPEED;
	if (canMoveY) this->y += y * SPEED;

	return (canMoveX || canMoveY);
}

player::~player() {}
