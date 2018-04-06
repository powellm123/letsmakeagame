#pragma once

#include "IMenu.h"
#include "IScene.h"
#include "MainMenu.h"
#include "UtilMethods.h"

class AwaitKeyPressMenu : public IMenu
{
	void BackCommand() override
	{
	}
public:
	static constexpr unsigned MenuId = UtilMethods::const_hash("AwaitKeyPressMenu");
	AwaitKeyPressMenu(Action action) : IMenu(MenuId)
	{
		MenuAction action1;
		action1.name = " ";
		action1.action = action;
		m_menuActions.push_back(action1);
	}
};