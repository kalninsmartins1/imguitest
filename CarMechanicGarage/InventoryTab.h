#pragma once

class Player;

class InventoryTab
{
public:
	InventoryTab(const Player& player);
	~InventoryTab();

	void Draw();

private:
	const Player& m_player;
};