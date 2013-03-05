#include "graphics/graphics.h"
#include "graphics/subBgHandler.h"
#include "mobs/mobHandler.h"
#include "mining.h"
#include <stdio.h>
#include <nds.h>
bool deathScreenShow=true;
touchPosition touch;
int oldKeys;
void deathScreenSetup()
{
	if (deathScreenShow == true)
	{	
		consoleClear();
		lcdMainOnTop();
		int i,j;
		for (i=0;i<=32;i++)
			for (j=0;j<=32;j++) setSubBgTile(i,j,0);
		for (i=0;i<=25;i++)
			for (j=0;j<=6;j++)
				setSubBgTile(i+2,j,i+(j*32)); //Draw the MineDS Logo!
		printf("\x1b[8;10HYou Died!");
		drawButton(8,10,14);
		drawButton(8,15,14);
		iprintf("\x1b[11;12HRespawn");
		iprintf("\x1b[16;10HTitleScreen");
		deathScreenShow = false;
		oldKeys=keysHeld();
		touchRead(&touch);
		miningSetScene(true);
	}
}
bool deathScreenUpdate()
{
	if (deathScreenShow == false)
	{	
		int i,j;
		scanKeys();
		if (keysHeld() & KEY_TOUCH && !(oldKeys & KEY_TOUCH)) //New Press
		{
			if (touch.px > 64 && touch.px < 160 && touch.py > 80 && touch.py < 96)
				drawButtonColored(8,10,14);
			else if (touch.px > 64 && touch.px < 160 && touch.py > 120 && touch.py < 136)
				drawButtonColored(8,15,14);	
		}
		else if (!(keysHeld() & KEY_TOUCH) && oldKeys & KEY_TOUCH)
		{
			if (touch.px > 64 && touch.px < 176 && touch.py > 80 && touch.py < 96)
			{
				for (i=0;i<=32;i++)
					for (j=7;j<=32;j++) setSubBgTile(i,j,0);
				deathScreenShow=true;
				consoleClear();
				printf("\n\n\n\n\n\n\n\n");
				mobHandlerRespawnPlayer();
				lcdMainOnBottom();
				miningSetScene(false);
				return false;
			}
			else drawButton(8,10,14);
			if (touch.px > 64 && touch.px < 176 && touch.py > 120 && touch.py < 136)
			{	
				for (i=0;i<=32;i++)
					for (j=7;j<=32;j++) setSubBgTile(i,j,0);
				deathScreenShow=true;
				miningSetScene(false);
				return true;
			}
			else drawButton(8,15,14);
		}
		oldKeys=keysHeld();
		touchRead(&touch);
	}
	return false;
}