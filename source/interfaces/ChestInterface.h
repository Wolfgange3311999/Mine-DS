/*#include "Interface.h"
#include "../inventory.h"
#include "../mainGame.h"
#include "../graphics/Menu.h"
#include "../graphics/graphics.h"
#include "../blockID.h"

#pragma once

class ChestInterface : public Interface
{
	Menu menu;

	//Buttons
	static const int BACK = 1;
	static const int SAVE = 2;
	static const int CRAFT_MENU = 3;
	static const int PAGE_MENU = 4;

	static bool shouldUpdate;

	int oldInvSlot;
	Graphic selectedGraphic;
	int loadedGraphic;
	UIElement_ptr backButton;

	void updateInv();
	static void checkLimits(int &value);
	void moveSlot(bool right);
	void parseKeyInput();
	void openInventory();
	void closeInventory();
	static bool touchesInvSlot(const touchPosition &touch);
	static int touchedSlot(const touchPosition &touch);
	void parseTouchInput(const touchPosition &touch);

public:
	static void triggerUpdate();
	static void staticUpdate();

	void update(WorldObject *world, touchPosition *touch);

	void draw();

	ChestInterface() : Interface(INTERFACE_CHEST), menu(MENU_BUTTON, false), loadedGraphic(AIR)
	{
		loadGraphicSub(&selectedGraphic, GRAPHIC_BLOCK, AIR);
		menu.addButton(1, 16, "Back");
		backButton = menu.getBack();
		menu.addButton(8, 16, "Save World");
		menu.addButton(21, 16, "Crafting", isSurvival());
		menu.addButton(21, 16, "Pages", 9, !isSurvival());
	}

	~ChestInterface() { }
};*/