#include <stdio.h>
#include <nds.h>
#include "world.h"
#include "blocks.h"
#include "blockID.h"


void leafVirus(worldObject* world,int x, int y,int amount,bool down,int blockID)
{
	if (amount<=0) return;
	world->blocks[x][y]=blockID;
	leafVirus(world,x+1,y,amount-1,down,blockID);
	leafVirus(world,x-1,y,amount-1,down,blockID);
	leafVirus(world,x,y-1,amount-1,down,blockID);
	if (down) leafVirus(world,x,y+1,amount-1,down,blockID);

}
void growNormalTree(worldObject* world,int x,int y,bool birch)
{
	int blockID=birch==true ? BIRCH_WOOD:LOG;
	int height = 2 + rand() % 2;
	int i;
	for (i=y;i>=y-height;i--)
	{
		world->blocks[x][i]=blockID; // Draw the trunk.
	}
	//Now for the leaves...
	leafVirus(world,x,i,2+(rand()%2),false,LEAF);
}
void growOakTree(worldObject* world,int x,int y)
{
	int height = 2 + rand() % 2;
	int blockID=OAK_WOOD;
	int i;
	for (i=y;i>=y-height;i--)
	{
		world->blocks[x][i]=blockID; // Draw the trunk.
	}
	leafVirus(world,x,y-height,2,false,REDWOOD_LEAF);
	y=i;
	for (i=y;i>=y-height;i--)
	{
		world->blocks[x][i]=blockID; // Draw the trunk.
	}
	leafVirus(world,x,i,2+rand()%2,false,REDWOOD_LEAF);
}
void growCactus(worldObject* world,int x,int y)
{
	int height = rand()%3;
	int j;
	for (j=y-height;j<=y;j++) world->blocks[x][j]=CACTUS;
}
void growFlower(worldObject* world,int x,int y)
{
	if (rand() % 2) world->blocks[x][y]=RED_FLOWER;
	else world->blocks[x][y]=YELLOW_FLOWER;
}
void growPumpkinPatch(worldObject* world,int x,int y)
{
	/*int i;
	for (i=x-5;i<=x;i++)
		if (!(rand()%5))
		{
			int y = findFirstBiomeBlock(world,i);
			world->blocks[i][y]=PUMPKIN_SIDE_1 + rand() % 2;
			if (i==-1) iprintf("\n\n\n\n\n\n\n\nHi!");
		}*/
}