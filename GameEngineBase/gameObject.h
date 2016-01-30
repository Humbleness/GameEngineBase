#pragma once

#include <vector>
#include <boost/shared_ptr.hpp>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class gameObject {
protected:
	float x = 100;
	float y = 100;
	float w = 100;
	float h = 200;
	float r = 255;
	float g = 255;
	float b = 255;
	float a = 255;
	bool collisionEnabled = false;
	std::string texturePath = "";
	GLuint texture = NULL;

	int spriteX = -1;
	int spriteY = -1;
	int spriteSize = -1;
	int spriteOffset = -1;

	// gravity-related
	bool gravityAffected = false;
	bool onGround = false;
	float velY = 0.0f;

	std::vector<boost::shared_ptr<gameObject>> objects;
	// this will determine if calling updateObjects will affect this object (enable this by using calling enableObjects)
	bool objectsEnabled = false;

public:
	gameObject();

	bool contextInstantiated = false;
	virtual void contextCreated();
	
	// setters
	void setVariables(float x, float y, float w, float h, float r, float g, float b, float a, bool collisionEnabled, std::string texture);
	void setVariables(float x, float y, float w, float h, float r, float g, float b, float a, bool collisionEnabled, std::string texture, int spriteX, int spriteY, int spriteSize, int spriteOffset);
	void setX(float x);
	void setY(float y);
	void setWidth(float w);
	void setHeight(float h);
	void setColor(float r, float g, float b, float a);
	void setCollides(bool collisionEnabled);
 	 // set texture to a path loaded in class
	void setTexture(std::string texture);
 	 // set texture to a pre-loaded texture
	void setTexture(GLuint texture);
	 // set texture to a sprite from a pre-loaded texture
	void setTexture(GLuint texture, int spriteX, int spriteY, int spriteSize, int spriteOffset);
	void setSprite(gameObject go, int x, int y, int size, int offset);
	void setSpriteX(int x);
	void setSpriteY(int y);
	void setSpriteSize(int size);
	void setSpriteOffset(int offset);

	void render();

	virtual void input(char key, int x, int y, int modifier);
	virtual void keyUp(char key, int x, int y);

	// this should only be called once
	void enableObjs(std::vector<boost::shared_ptr<gameObject>> objs);
	// call this whenever you want to UPDATE the vector (and you have already called enableObjs)
	void updateObjs(std::vector<boost::shared_ptr<gameObject>> objs);

	virtual void update(); // called every specified milliseconds (specified in Main)
	void doGameObjectShit(); // like update, but not meant to be overriden (hint: DON'T OVERRIDE THIS)

	void enableGravity(); // call this instead

	// getters
	float getX();
	float getY();
	float getW();
	float getH();
	float getR();
	float getG();
	float getB();
	bool collides();
	std::string getTexturePath();
	GLuint getTexture();
	int getSpriteX();
	int getSpriteY();
	int getSpriteSize();
	int getSpriteOffset();

	~gameObject();
};