#include "tile.h"
#include "player.h"
#include "gameObject.h"
#include "physics.h"
#include "loadTexture.h"

#include <stdio.h>


tile::tile(float x, float y, float width, float height, bool collides, std::string texture) {
	tile(x, y, width, height, collides, texture, -1, -1, -1, -1);
}

tile::tile(float x, float y, float width, float height, bool collides, std::string texture, int spriteX, int spriteY, int spriteSize, int spriteOffset) {
	this->setVariables(x, y, width, height, 255, 255, 255, 255, collides, texture, spriteX, spriteY, spriteSize, spriteOffset);
}

tile::~tile() {}
