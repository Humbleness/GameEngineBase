#pragma once
#include "gameObject.h"

// a class solely for the purpose of being lightweight and easy to instantiate (good for physics collisions)
class simulated : public gameObject
{
public:
	simulated(float x, float y, float width, float height);
	~simulated();
};

