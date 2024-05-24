#include "ShopTab.h"
#include "imgui.h"
#include "Tool.h"
#include "Player.h"
#include "EventDispatcher.h"
#include "BuyToolEvent.h"
#include "ToolBoughtEvent.h"

static constexpr const char* BOUGHT_POPUP_NAME = "Buy Result";
static const ImVec2 POPUP_SIZE(300.f, 100.f);

ShopTab::ShopTab(const Player& player, const ToolManager& toolManager, EventDispatcher& eventDispatcher)
	:   m_shouldDrawBoughtPopup(false), 
        m_toolWearAfterBuy(-1),
        m_player(player),
        m_toolManager(toolManager),
        m_lastBoughtTool(nullptr),
        m_eventDispatcher(eventDispatcher)
{
    m_eventDispatcher.SubscribeToEvent(std::bind(&ShopTab::OnToolBoughtEvent, this, std::placeholders::_1), 
        EventType::TOOL_BOUGHT);
}

ShopTab::~ShopTab()
{
    m_eventDispatcher.UnsubscribeFromEvent(EventType::TOOL_BOUGHT);
}

void ShopTab::Draw()
{
    ImGui::Text("  Shop content:\n");
    const std::map<int, Tool*>& tools = m_toolManager.GetTools();
    for (const auto& toolIterator : tools)
    {        
        Tool* tool = toolIterator.second;
        if (tool != nullptr)
        {            
            int index = toolIterator.first;            
            int toolPrice = tool->GetPrice();
            ImGui::Text("  - %d: %s (%d$)\n", index, tool->GetName().c_str(), toolPrice);            
            if (m_player.GetCurrentMoneyAmount() >= toolPrice)
            {
                ImGui::SameLine();                
                ImGui::PushID(index);
                bool isButtonPressed = ImGui::Button("Buy");
                ImGui::PopID();
                if (isButtonPressed)
                {
                    BuyToolEvent buyEvent(*tool);
                    m_eventDispatcher.DispatchEvent(buyEvent);                    
                }                                                
            }            
        }
    }

    if (m_shouldDrawBoughtPopup)
    {
        DrawBoughtPopup();
    }
}

void ShopTab::OnToolBoughtEvent(const Event& genericEvent)
{
    if (genericEvent.GetEventType() == EventType::TOOL_BOUGHT)
    {
        const ToolBoughtEvent& boughtEvent = static_cast<const ToolBoughtEvent&>(genericEvent);
        m_shouldDrawBoughtPopup = true;
        m_lastBoughtTool = &boughtEvent.GetBoughtTool();
        m_toolWearAfterBuy = m_player.GetToolWear(m_lastBoughtTool);
        ImGui::OpenPopup(BOUGHT_POPUP_NAME);
    }    
}

void ShopTab::DrawBoughtPopup()
{    
    if (m_lastBoughtTool != nullptr)
    {
        ImGui::SetNextWindowSize(POPUP_SIZE);        
        if (ImGui::BeginPopupModal(BOUGHT_POPUP_NAME))
        {
            ImGui::Text("You now have: %s x%d", m_lastBoughtTool->GetName().c_str(), m_toolWearAfterBuy);
            ImGui::Text("and Money %d$", m_player.GetCurrentMoneyAmount());
            ImGui::NewLine();

            if (ImGui::Button("Close"))
            {
                ImGui::CloseCurrentPopup();
                m_shouldDrawBoughtPopup = false;
            }
            ImGui::EndPopup();
        }        
    }    
}
