#pragma once
#include "../world.h"
#include "../blockupdate.h"

class CactusUpdater : public BlockUpdater
{
public:
	CactusUpdater();
	virtual void update(WorldObject* world, int x, int y, bool bg);
	virtual void chanceUpdate(WorldObject* world, int x, int y, bool bg);
};
