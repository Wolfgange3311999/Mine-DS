#pragma once
#include "../world.h"
#include "../blockupdate.h"

class LadderUpdater : public BlockUpdater
{
public:
	LadderUpdater();
	virtual void update(WorldObject* world, int x, int y, bool bg);
};