#include "../blocks.h"
#include "hurt.h"
#include "../graphics/graphics.h"
#include "HerobrineMob.h"
#include "mobHandler.h"
#include "mobFunctions.h"
#include "../blockID.h"
#include "../collision.h"
#include "../worldRender.h"
#include "../inventory.h"
#include "../mining.h"
#include "../general.h"
//#include "../sounds.h"

Graphic herobrineMobGraphic[3];

void HerobrineMob::calcMiscData(WorldObject* world)
{
	calculateMiscData(world, this);
}

void HerobrineMob::updateMob(WorldObject* world)
{
	++waitingCount;
	if (spriteState == 0) showGraphic(&herobrineMobGraphic[0], x - world->camX - 7, y - world->camY - 15, facing ? true : false);
	else if (spriteState == 1) showGraphic(&herobrineMobGraphic[1], x - world->camX - 7, y - world->camY - 15, facing ? true : false);
	if (host == true)
	{
		if (collisions[SIDE_BOTTOM] && collisions[SIDE_TOP])
			while (y > 16 && (world->blocks[int(x) / 16][(int(y) / 16) + 1] != AIR || world->blocks[int(x) / 16][int(y) / 16] != AIR))
				y -= 16;
		BaseMob_ptr target = mobHandlerFindMob(128, MOB_PLAYER, x, y);
		if (target->x < x && target->type == MOB_PLAYER) facing = true;
		else if (target->type == MOB_PLAYER) facing = false;
		int distance = target->x - x;
		if (distance < 0)
			distance *= -1;
		else if (!collisions[SIDE_RIGHT] && !collisions[SIDE_TOP])
		{
			if (waitingCount > 1000)
			{
				waitingCount = 1100;
				vx = ((facing ? -1 : 1) * rand() % (distance < 40 && rand() % 2 ? 5 : 7));
			}
			else
			{
				if (!(distance < 65 && distance > 55))
					x += ((facing ? -1 : 1)*(distance > 60 ? 1 : -1) * rand() % 5);
				else if (rand() % 10 == 1)
					x += ((rand() % 2) ? -1 : 1)*(rand() % 15);
			}
		}
		else if ((collisions[SIDE_RIGHT] || collisions[SIDE_LEFT]) && collisions[SIDE_BOTTOM] && !collisions[SIDE_TOP] && spriteState != 1)
			vy = JUMP_VELOCITY;
		if (framesHurtSprite == 0) spriteState = 0;
		else --framesHurtSprite;
		if (spriteCol(x, y, target->x, target->y, sx, sy, target->sx, target->sy) && waitingCount > 1000)
			target->hurt(3, HEROBRINE_HURT);
	}
}

void HerobrineMob::sendWifiUpdate()
{
}

void HerobrineMob::saveToFile(FILE* pFile)
{
}

void HerobrineMob::loadFromFile(FILE* pFile)
{
	health = 0;
}

bool canHerobrineMobSpawnHere(WorldObject* world, int x, int y)
{
	++y;
	if (!isBlockWalkThrough(world->blocks[x][y + 1]) && isBlockWalkThrough(world->blocks[x][y]) && world->blocks[x][y] != CACTUS && world->blocks[x][y + 1] != CACTUS)
		return true;
	return false;
}

void herobrineMobInit()
{
	loadGraphic(&herobrineMobGraphic[0], GRAPHIC_MOB, 8);
	loadGraphic(&herobrineMobGraphic[1], GRAPHIC_MOB, 9);
}

void HerobrineMob::hurt(int amount, int type)
{

	if (spriteState == 1)
		return;
	if (jumpHurtType(type) && collisions[SIDE_BOTTOM])
		vy = JUMP_VELOCITY;
	playSound(SOUND_PLAYER_HURT);
	health -= amount;
	spriteState = 1;
	framesHurtSprite = 20;
	if (health <= 0)
	{
		if (type == CACTUS_HURT)
		{
			createItemMob(x/16, y/16, rand() % (NUM_BLOCKS - 2) + 2, rand() % 4 + 1);
			health = 0;
		}
		else
		{
			x = getDefaultSpawnX()*16;
			waitingCount = -rand() % 4000;
			health = 7;
		}
	}
}

bool HerobrineMob::isMyPlayer()
{
	return false;
}