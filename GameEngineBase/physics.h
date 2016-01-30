#pragma once

#include "gameObject.h"


class physics
{
protected:
	std::vector<boost::shared_ptr<gameObject>> objectList;

public:
	physics(std::vector<boost::shared_ptr<gameObject>> objectList);

	void updateObjList(std::vector<boost::shared_ptr<gameObject>> objectList);
	bool hasLineOfSight(gameObject obj1, gameObject obj2);
	static bool hasLineOfSight(gameObject obj1, gameObject obj2, std::vector<boost::shared_ptr<gameObject>> objectList);

	static bool collides(gameObject obj1, gameObject obj2);
	static bool quadOver(gameObject obj1, gameObject obj2);
	static float applyGravity(float vel);

	~physics();
};

