#include "../blocks.h"
#include "hurt.h"
#include "../graphics/graphics.h"
#include "HerobrineMob.h"
#include "mobHandler.h"
#include "../blockID.h"
#include "../collision.h"
#include "../worldRender.h"
#include "../inventory.h"
#include "../mining.h"
#include "../general.h"
//#include "../sounds.h"

Graphic herobrineMobGraphic[3];

HerobrineMob::HerobrineMob()
{
	jump = 0;
	x = 0;
	y = 0;
	vy = 0;
	vx = 0;
	ping = 0;
	alive = false;
	health = 7;
	framesHurtSprite = 0;
	notarget = 0;
	waitingCount = -rand() % 4000;
}

HerobrineMob::HerobrineMob(int a, int b)
{
	jump = 0;
	sx = 6;
	sy = 32;
	x = a;
	y = b;
	vy = 0;
	vx = 0;
	alive = false;
	facing = false;
	type = MOB_HEROBRINE;
	health = 7;
	ping = 0;
	spriteState = 0;
	notarget = 0;
	timeTillWifiUpdate = rand() % 4 + 4;
	waitingCount = -rand() % 4000;
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
		++jump;
		int distance = target->x - x;
		if (distance < 0)
			distance *= -1;
		if (target->type != MOB_PLAYER)
		{
			++notarget;
			jump = 0;
		}
		else if (!collisions[SIDE_RIGHT] && !collisions[SIDE_TOP] && jump > 1)
		{
			if (waitingCount > 1000)
			{
				waitingCount = 1100;
				vx = ((facing ? -1 : 1) * rand() % (distance < 40 && rand() % 2 ? 2 : 3));
			}
			else
			{
				if (!(distance < 65 && distance > 55))
					x += ((facing ? -1 : 1)*(distance > 60 ? 1 : -1) * rand() % 5);
				else if (rand() % 10 == 1)
					x += ((rand() % 2) ? -1 : 1)*(rand() % 15);
				jump = 0;
			}
		}
		else if ((collisions[SIDE_RIGHT] || collisions[SIDE_LEFT]) && collisions[SIDE_BOTTOM] && !collisions[SIDE_TOP] && spriteState != 1)
			vy = JUMP_VELOCITY;
		ping = 0;
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
	kill();
}

bool canHerobrineMobSpawnHere(WorldObject* world, int x, int y)
{
	++y;
	if (!isBlockWalkThrough(world->blocks[x][y + 1]) && isBlockWalkThrough(world->blocks[x][y]) && world->blocks[x][y] != CACTUS && world->blocks[x][y + 1] != CACTUS)
	{
		/*if (getBrightness(world, x, y + 1) > 7)*/
		return true;
	}
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
	//playSound(HEROBRINE_H);
	health -= amount;
	spriteState = 1;
	framesHurtSprite = 20;
	if (health <= 0)
	{
		if (type == CACTUS_HURT)
		{
			addInventory(rand() % (NUM_BLOCKS - 2) + 2, rand() % 4 + 1);
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
