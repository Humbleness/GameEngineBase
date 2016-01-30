#include "simulated.h"

#include <stdio.h>

// a class solely for the purpose of being lightweight and easy to instantiate (good for physics collisions)
simulated::simulated(float x, float y, float w, float h) {
	this->setVariables(x, y, w, h, 255, 255, 255, 255, false, "");
}


simulated::~simulated() {}
