#include "InventoryTab.h"
#include "imgui.h"
#include "Player.h"

InventoryTab::InventoryTab(const Player& player)
	:	m_player(player)
{
}

InventoryTab::~InventoryTab()
{
}

void InventoryTab::Draw()
{
    ImGui::Text("  Money: %d$", m_player.GetCurrentMoneyAmount());
    ImGui::Text("  Tools:");
    const std::map<const Tool*, int>& usableTools = m_player.GetUsableTools();
    for (const auto& toolIterator : usableTools)
    {
        const Tool* tool = toolIterator.first;
        if (tool != nullptr)
        {            
            int usageCounter = toolIterator.second;
            ImGui::Text("  - %s x%d", tool->GetName().c_str(), usageCounter);
        }        
    }    
}
