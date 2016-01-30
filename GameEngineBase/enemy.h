#pragma once

#include "gameObject.h"

class enemy : public gameObject
{
public:
	enemy();

	virtual void update();

	~enemy();
};

