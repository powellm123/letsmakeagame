#pragma once

#include <string>
#include <vector>
#include <list>
#include "TimeController.h"
#include "Buttons.h"

typedef void(*Action)();
struct MenuAction
{
	std::string name;
	Action action;

	MenuAction(){}
};

class IMenu
{
protected:
	int m_index;
	float m_moveCoolDown;
	bool m_justSwitched;
	std::vector<MenuAction> m_menuActions;
	static std::list<Uint8> keypresses;
	unsigned m_menuId;
	virtual void BackCommand();
public:
	IMenu(unsigned menuId);
	unsigned GetMenuId();
	virtual void Update();
	virtual void Draw();
	static void ClearKeyPress();
	static void AddkeyPress(Uint8 key);
};