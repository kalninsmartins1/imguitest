#pragma once

#include <string>

class ToolManager;
class Player;
class EventDispatcher;
class Event;
class Tool;

class ShopTab
{
public:
	ShopTab(const Player& player, const ToolManager& toolManager, EventDispatcher& eventDispatcher);
	~ShopTab();

	void Draw();

private:
	void OnToolBoughtEvent(const Event& genericEvent);
	void DrawBoughtPopup();

private:
	bool m_shouldDrawBoughtPopup;
	int m_toolWearAfterBuy;

	const Player& m_player;
	const ToolManager& m_toolManager;
	const Tool* m_lastBoughtTool;
	EventDispatcher& m_eventDispatcher;	
};