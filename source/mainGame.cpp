#include <nds.h>
#include <stdio.h>
#include "world/World.h"
#include "world/worldGen.h"
#include "general.h"
#include "mining.h"
#include "blockID.h"
#include "inventory.h"
#include "world/worldRender.h"
#include "graphics/graphics.h"
#include "graphics/subBgHandler.h"
#include "mobs/mobHandler.h"
#include "mobs/hurt.h"
#include "mobs/PlayerMob.h"
#include "mobs/ItemMob.h"
#include "deathScreen.h"
#include "dayNight.h"
#include "inventory.h"
#include "titleScreen.h"
#include "graphics/UI.h"
#include "Config.h"
#include "files.h"
#include "mainGame.h"
#include "sounds.h"
#include "nifi.h"
#include "communications.h"
#include "blockUpdaters/blockUpdater.h"
#include "blockPages.h"
#include <time.h>
#include "blocks.h"
#include "graphics/Menu.h"
#include "graphics/3DHandler.h"
#include "graphics/particleHandler.h"
#include "graphics/interfaces/interfaceHandler.h"

#include "localizations/locale.h"

bool shouldQuitGame = false;
World *world;

static bool inGameMenu()
{
	bool exit = false;
	oamClear(&oamSub, 0, 0);
	oamUpdate(&oamSub);

	while (!exit)
	{
		lcdMainOnTop();
		drawBackground();
		setCurMenuSlot(false);
		clearText();

		Menu menu;
		const char *s1 = locale("save"), *s2 = locale("quit"), *s3 = locale("settings");
		int length = 2 + max(strlen(s1), strlen(s2), strlen(s3));

		menu.addButton(8, s1, length);
		menu.addButton(13, s2, length);
		menu.addButton(18, s3, length);

		switch (menu.activate())
		{
		case 1: // save game
			printXY(1, 22, locale("save"));
			if (!saveWorld(*world))
			{
				printXY(1, 22, "Failed to save game");
				sleepThread(1);
			}
			break;
		case 2: // quit game
			return true;
		case 3: // settings
			settingsScreen();
			startTransition(false);
			break;
		default: // back button
			exit = true;
			setSubBg(0, 0);
			updateSubBG();
			break;
		}
	}
	drawInterface();
	lcdMainOnBottom();
	return false;
}

bool isSurvival(void)
{
	return (world->gameMode == World::Mode::SURVIVAL);
}

void quitGame()
{
	shouldQuitGame = true;
}

void newGame(World::Mode mode)
{
	updateSubBG();
	delete world;
	world = new World(mode);
	mobsReset();
	clearInventory();
	shouldQuitGame = false;
}

void drawWorld()
{
	worldRender_Render(*world);
}

void previewGame(void)
{
	newGame(World::Mode::PREVIEW);
	drawWorld();
}

bool loadGame(void)
{
	shouldQuitGame = false;
	if (loadWorld(world))
	{
		srand(world->seed);
		return true;
	}
	return false;
}

void joinGame(void)
{
	nifiEnable();
	//fillWorld(*world, BEDROCK);
	delete world;
	world = new World();
	clearText();
	drawBackground();
	printXY(1, 10, "Looking for servers");
	// TODO: Rename clientNifiInit() to something that makes more sense
	while (!clientNifiInit()) // Looks for servers, sets up Nifi, and Asks the player to join a server.
		vBlank();
	printXY(1, 11, "Joining Server!");
	if (!doHandshake())
	{
		printXY(1, 12, "Handshake Failed");
		sleepThread(2);
		return;
	}
	recieveWorld(*world);
	// TODO: Move this to nifi.cpp
	unsigned short buffer[100];
	int client_id = getClientID();
	sprintf((char *) buffer, "%d joined the game.\n", client_id);
	printGlobalMessage((char *) buffer);
	startMultiplayerGame(false);
}

void startGame(void)
{
	setSubBg(0, 0);
	updateSubBG();
	touchPosition touch;

	clearText();
	clear_messages();

	playMusic(MUSIC_CALM);
	if (!isSurvival())
		setBlockPage(PAGE_WOOL);
	shouldQuitGame = false;
	setInterface(*world, INTERFACE_INVENTORY);

	while (!shouldQuitGame)
	{
		Graphic::resetSprites(true);
		clearUnusedBlockSprites();
		dayNightUpdate(*world);
		timeUpdate();

		scanKeys();
		if (keysHeld() & KEY_TOUCH)
			touchRead(&touch);

		mobHandlerUpdate(*world, touch);
		updateInterface(*world, touch);
		update_message();
		if (keysDown() & getGlobalSettings()->getKey(ACTION_MENU))
		{
			if (inGameMenu() != 0)
				break;
		}
		miningUpdate(*world, touch);
		proceduralBlockUpdate(*world);
		worldRender_RenderWater(*world);
		update3D();
		updateParticles(*world);
		vBlank();
		{
			worldRender_Render(*world);
			oamUpdate(&oamMain);
			updateSubBG();
		}
	}
}

// TODO: clean this function up

void startMultiplayerGame(bool host)
{
	/*int oldKeys = keysHeld();
	touchPosition touch;

	nifiEnable();
	clearText();
	clear_messages();

	drawBackground();
	playMusic(MUSIC_HAL2);
	mobsReset();
	lcdMainOnBottom();

	if (host)
	{
		printf("Generating World!\n");
		delete world;
		world = new WorldObject();
		world->gamemode = World::Mode::CREATIVE;
		generateWorld(*world);
		while (!hostNifiInit()) updateFrame();
		communicationInit(*world);
		clearText();
		unsigned short buffer[100];
		int server_id = getServerID();
		sprintf((char *) buffer, "Server ID: %d\n", server_id);
		printGlobalMessage((char *) buffer);
	}

	while (!shouldQuitGame)
	{
		recieveWorldUpdate();
		updateTime();
		scanKeys();
		mobHandlerUpdate(*world);
		updateInventory(touch, world, oldKeys);
		update_message();
		if (keysHeld() & KEY_B && keysHeld() & KEY_DOWN)
			clear_messages();
		if (keysDown() & getGlobalSettings()->getKey(ACTION_MENU) && getInventoryState() == 0)
			break;
		oldKeys = keysHeld();
		touchRead(&touch);
		miningUpdate(*world, touch);
		if (host)
			proceduralBlockUpdate(*world);
		updateFrame(); //Should be the only time called in the loop
		worldRender_Render(*world, world->camX, world->camY);
		oamUpdate(&oamMain);
		oamUpdate(&oamSub);
		clearMainGraphics();
		clearUnusedBlockSprites();
		if (host)
			timeUpdate(*world);
	}
	nifiDisable();*/ }
/*void setSeed(int seed)
{
	world->seed = seed;
}*/
