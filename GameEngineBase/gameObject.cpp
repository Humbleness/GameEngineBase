#include "gameObject.h"
#include "draw.h"
#include "physics.h"
#include "objects.h"
#include "simulated.h"
#include "loadTexture.h"

#include <stdio.h>
#include <typeinfo>



gameObject::gameObject() {}

// called once the openGL context has been fully initialized
void gameObject::contextCreated() {
	this->contextInstantiated = true;

	if (this->getTexturePath() != "") {
		this->setTexture(this->getTexturePath());
	}
}

// setters 
  // set every variable at once
void gameObject::setVariables(float x, float y, float w, float h, float r, float g, float b, float a, bool collisionEnabled, std::string texture) {
	setVariables(x, y, w, h, r, g, b, a, collisionEnabled, texture, -1, -1, -1, -1);
}
void gameObject::setVariables(float x, float y, float w, float h, float r, float g, float b, float a, bool collisionEnabled, std::string texture, int spriteX, int spriteY, int spriteSize, int spriteOffset) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	this->collisionEnabled = collisionEnabled;
	if (texture != "") this->texturePath = texture;
	else this->texture = NULL;

	this->spriteX = spriteX;
	this->spriteY = spriteY;
	this->spriteSize = spriteSize;
	this->spriteOffset = spriteOffset;
}

  // set each variable individually
void gameObject::setX(float x) { this->x = x; }
void gameObject::setY(float y) { this->y = y; }
void gameObject::setWidth(float w) { this->w = w; }
void gameObject::setHeight(float h) { this->h = h; }
void gameObject::setColor(float r, float g, float b, float a) { this->r = r; this->g = g; this->b = b; this->a = a; }
void gameObject::setCollides(bool collisionEnabled) { this->collisionEnabled = collisionEnabled; }

void gameObject::setTexture(std::string path) {
	this->texturePath = path;
	if (this->contextInstantiated) {
		this->texture = loadTexture::at(path);
	}
}

void gameObject::setTexture(GLuint texture) {
	if (texture != NULL) this->texture = texture;
}

void gameObject::setTexture(GLuint texture, int spriteX, int spriteY, int spriteSize, int spriteOffset) {
	if (texture != NULL) {
		this->texture = texture;
		this->setSpriteX(spriteX);
		this->setSpriteY(spriteY);
		this->setSpriteSize(spriteSize);
		this->setSpriteOffset(spriteOffset);
	}
}

void gameObject::setSprite(gameObject go, int x, int y, int size, int offset) {
	go.setSpriteX(x);
	go.setSpriteY(y);
	go.setSpriteSize(size);
	go.setSpriteOffset(offset);
}
void gameObject::setSpriteX(int x) { this->spriteX = x; }
void gameObject::setSpriteY(int y) { this->spriteY = y; }
void gameObject::setSpriteSize(int size) { this->spriteSize = size; }
void gameObject::setSpriteOffset(int offset) { this->spriteOffset = offset; }

// this way I won't have to include the openGL libraries in every single object
void gameObject::render() {
	// no texture set
	if (this->texture == NULL) {
		draw::quad(this->x, this->y, this->w, this->h, this->r, this->g, this->b, this->a);
	} else {
		if (this->getSpriteX() >= 0 && this->getSpriteY() >= 0 && getSpriteSize() > 0 && getSpriteOffset() >= 0) {
			// texture set from a sprite sheet
			draw::quad(this->x, this->y, this->w, this->h, this->texture, this->r, this->g, this->b, this->a, this->getSpriteX(), this->getSpriteY(), this->getSpriteSize(), this->getSpriteOffset());
		} else {
			// texture set whithout a sprite sheet
			draw::quad(this->x, this->y, this->w, this->h, this->texture, this->r, this->g, this->b, this->a);
		}
	}
}


void gameObject::input(char key, int x, int y, int modifier) {}
void gameObject::keyUp(char key, int x, int y) {}

void gameObject::enableObjs(std::vector<boost::shared_ptr<gameObject>> objs) {
	this->objects = objs;
	this->objectsEnabled = true;
}

void gameObject::updateObjs(std::vector<boost::shared_ptr<gameObject>> objs) {
	if (this->objectsEnabled) {
		this->objects.clear();
		this->objects = objs;
	}
}

// gets called every specified milliseconds (defined as a constant in main as TIME)
void gameObject::update() {}
// like update, but specifically for lower level gameObject.cpp shit
void gameObject::doGameObjectShit() {
	if (this->gravityAffected) {
		GLfloat diff = 0;
		this->onGround = false;
		for (GLint i = 0; i < (GLint)objects.size(); i++) {
			boost::shared_ptr<gameObject> go = objects.at(i);
			if (objects.at(i)->collides()) {
				simulated sim = simulated(this->x, this->y + this->velY, w, h);
				if (physics::collides(sim, *go)) {
					if (sim.getY() > go->getY()) { // make sure you're not just teleporting from underneath a cieling
						this->onGround = true;
						diff = this->getY() - (go->getY() + go->getH());
						if (diff >= 1 || diff < 0) this->y -= diff;
					} else {
						this->velY = 0;
						this->y = go->getY() - this->getH();
					}
				}
			}
		}
		if (!this->onGround) velY = physics::applyGravity(velY);
		else velY = 0.0f;
	}
}

void gameObject::enableGravity() {
	this->gravityAffected = true;
}

// getters
float gameObject::getX() { return this->x; }
float gameObject::getY() { return this->y; }
float gameObject::getW() { return this->w; }
float gameObject::getH() { return this->h; }
float gameObject::getR() { return this->r; }
float gameObject::getG() { return this->g; }
float gameObject::getB() { return this->b; }
bool gameObject::collides() { return this->collisionEnabled; }
std::string gameObject::getTexturePath() { return this->texturePath; }
GLuint gameObject::getTexture() { return this->texture; }
int gameObject::getSpriteX() { return this->spriteX; }
int gameObject::getSpriteY() { return this->spriteY; }
int gameObject::getSpriteSize() { return this->spriteSize; }
int gameObject::getSpriteOffset() { return this->spriteOffset; }

gameObject::~gameObject() {}
