#pragma once
#include "gameObject.h"

#include <vector>

//template <class gameObject>
class player : public gameObject {

protected:
	float velPosX = 0; // x and y are moved by this much every frame
	float velNegX = 0; // pos X and neg X (and Y) are subtracted by eachother to determine the distance
	float velPosY = 0;
	float velNegY = 0;

	bool wDown = false; // move keys are pressed down
	bool aDown = false;
	bool sDown = false;
	bool dDown = false;
	float frameNumber = 0;

	std::vector<gameObject *> objs;
public:
	player(float x, float y, float width, float height);

	void clearObjs();
	void advanceFrame();
	bool move(float x, float y);
	void input(char key, int x, int y, int mod);
	void keyUp(char key, int x, int y);
	void update();

	~player();
};

