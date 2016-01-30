#pragma once

#include "gameObject.h"
#include "player.h"

class tile : public gameObject {
protected:
	std::string textureP = "";

	// an id used by the tilemerger to identify if two tiles are the same type
	int id = -1;

public:
	tile(float x, float y, float width, float height, bool collides, std::string texture);
	tile(float x, float y, float width, float height, bool collides, std::string texture, int spriteX, int spriteY, int spriteSize, int spriteOffset);

	void setID(int num) { this->id = num; }
	int getID() { return id; }
	//void contextCreated();

	~tile();
};

