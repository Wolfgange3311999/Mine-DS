#pragma once
#include "../world.h"
#include "../blockupdate.h"

class snowGrassUpdater : public blockUpdater {
public:
	snowGrassUpdater();
	virtual void update(worldObject* world, int x, int y, bool bg);
};