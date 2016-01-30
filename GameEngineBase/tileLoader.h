#pragma once

#include "gameObject.h"

#include <vector>

class tileLoader
{
public:
	tileLoader();

	static std::vector<boost::shared_ptr<gameObject>> loadTiles(std::vector<boost::shared_ptr<gameObject>> objs, std::string filePath);
	// optional spritesheet that can be referenced by registered tiles
	static std::vector<boost::shared_ptr<gameObject>> loadTiles(std::vector<boost::shared_ptr<gameObject>> objs, std::string filePath, GLuint spriteSheet);
	

	~tileLoader();
};

