#include "physics.h"
#include "gameObject.h"

#include <stdio.h>


physics::physics(std::vector<boost::shared_ptr<gameObject>> objectList) {
	this->updateObjList(objectList);
}

void physics::updateObjList(std::vector<boost::shared_ptr<gameObject>> objectList) {
	this->objectList = objectList;
}

bool physics::hasLineOfSight(gameObject obj1, gameObject obj2) {
	return this->hasLineOfSight(obj1, obj2, this->objectList);
}

bool physics::hasLineOfSight(gameObject obj1, gameObject obj2, std::vector<boost::shared_ptr<gameObject>> objectList) {
	// if the coordinates are the exact same return true (why tf are you comparing two objs with the same coordinates anyways?)
	if (obj1.getX() == obj2.getX() && obj1.getY() == obj2.getY() && obj1.getW() == obj2.getW() && obj1.getH() == obj2.getH()) return true;

	bool out = true;
	for (int i = 0; i < (int)objectList.size(); i++) {
		boost::shared_ptr<gameObject> curObj = objectList.at(i);

	}
	return out;
}

bool physics::collides(gameObject obj1, gameObject obj2) {
	if ((obj1.getX() + obj1.getW()) > obj2.getX())
		if (obj1.getX() < (obj2.getX() + obj2.getW()))
			if ((obj1.getY() + obj1.getH()) > obj2.getY())
				if (obj1.getY() < (obj2.getY() + obj2.getH()))
					return true;

	return false;
}

// returns if obj1 is colliding with obj2 with obj1 being on top (not working)
bool physics::quadOver(gameObject obj1, gameObject obj2) {
	if ((obj1.getX() + obj1.getW()) > obj2.getX())
		if (obj1.getX() < (obj2.getX() + obj2.getW()))
			if ((obj1.getY() + obj1.getH()) > obj2.getY())
				//if (obj1.getY() < (obj2.getY() + obj2.getH()))
					return true;

	return false;
}

// vel = current velocity (very complicated function as you can see)
float physics::applyGravity(float vel) {
	return vel - .1f;
}

physics::~physics(){}
