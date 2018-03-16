#pragma once

#include "Player.h"
#include <vector>
#include <string>
#include <sstream>
#include "TimeController.h"

class Menu : public Player
{
public:
	static constexpr size_t type = UtilMethods::const_hash("menu");
	Menu(std::vector<std::string> menuActions, bool isActable, bool shouldDrawText, Buttons* buttons, std::string menuName);
	void PerformAction(Player::Action action) override;
	void PerformMove(float angle, float value) override;
	void Update() override;
	void Draw() override;
	bool GetIsActionSelected();
	std::string GetSelectedAction();
	bool GetIsActable();
	void SetIsActable(bool);
	std::string GetMenuName();
	static Menu* GetActiveMenu();
	static void ChangeActiveMenu(Menu *menu);
	static Menu* FindMenu(std::string menuName);
	static std::list<Menu*>* GetAllMenus();
private:
	void FireAction();
	void AltFireAction();
	void MoveAction(float angle);
	void PauseAction();

	bool m_justSwitched;
	bool m_shouldDrawText;
	bool m_isActionSelected;
	bool m_isActable;
	float m_moveCoolDown;
	std::string m_selectedAction;
	std::vector<std::string> m_menuActions;
	int m_index;
	std::string m_menuName;
};