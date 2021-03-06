#pragma once
#include "Button.h"
#include "../localizations/locale.h"
#include <memory>
#include <vector>
#include <string>

void slideButtonAction(UIElement *button, int sizeY, bool extra);
using UIElement_ptr = std::shared_ptr<UIElement>;

enum MenuType
{
	MENU_BUTTON,
	MENU_LIST
};

class Menu
{
private:
	MenuType type;
	int frameX, frameY; //In tiles
	int sizeX, sizeY; //In tiles
	int listX, listY; //For list menus

	std::vector<UIElement_ptr> elements;
	std::vector<std::string> listItems;

public:
	void draw(bool labels = true);
	int activate();
	int update(const touchPosition &touch);
	void setListXY(int x, int y);
	void setFrame(int x, int y = 0);
	void setAction(void (*function)(UIElement *element, int data, bool data2), int sendData);

	UIElement_ptr getBack();
	void addButton(int x, int y, const char * const label, int length = -1, bool isVisible = true);
	void addButton(int x, int y, const char * const label, bool isVisible);
	void addButton(int y, const char * const label, bool isVisible = true);
	void addButton(int y, const char * const label, int length, bool isVisible = true);
	void addListItem(const char *label);
	void addSlider(int x, int y, const char * const label, int initPos, int length = 30, bool isVisible = true);
	void addCheckButton(int x, int y, const char * const label, bool enabled, int length = -1, bool isVisible = true);

	Menu(MenuType type = MENU_BUTTON, bool back = true, int sizeY = 24)
	: type(type), frameX(0), frameY(0), sizeX(32), sizeY(sizeY), listX(0), listY(0)
	, elements(), listItems()
	{
		elements.push_back(UIElement_ptr(new Button(1, 20, "\x1F", sizeY > 24)));
		setAction(slideButtonAction, sizeY);
		elements.push_back(UIElement_ptr(new Button(25, 20, locale("back"), back)));
	}
};