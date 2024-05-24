#include <iostream>
#include "Player.h"
#include "EventDispatcher.h"
#include "ToolBoughtEvent.h"


Player::Player(EventDispatcher& eventDispatcher)
    :   m_money(START_MONEY), 
        m_eventDispatcher(eventDispatcher)
{
}

Player::~Player()
{
}

int Player::GetToolWear(const Tool* tool) const
{
    int toolWear = -1;
    const auto& toolIterator = m_usableTools.find(tool);
    if (toolIterator != m_usableTools.end())
    {
        toolWear = toolIterator->second;
    }
    return toolWear;
}

bool Player::AttemptJob(const std::vector<Tool*>& requiredTools)
{
    m_toolsUsedForLastJob.clear();
    for (Tool* tool : requiredTools)
    {
        const auto& toolIterator = m_usableTools.find(tool);
        if (toolIterator != m_usableTools.end() && toolIterator->second > 0)
        {
            bool shouldToolTakeDamage = std::rand() % 2 == 1;
            if (shouldToolTakeDamage)
            {
                toolIterator->second--;
            }

            int toolWear = toolIterator->second;
            m_toolsUsedForLastJob[tool] = toolWear;
            if (toolWear == 0)
            {
                // Tool is broken
                m_usableTools.erase(tool);
            }
        }
    }
    // Was job successful
    return m_toolsUsedForLastJob.size() == requiredTools.size();
}

void Player::ReceiveMoney(int amount)
{
    m_money += amount;
}

void Player::BuyTool(const Tool* tool)
{
    if (tool != nullptr)
    {
        int price = tool->GetPrice();
        int wearCount = tool->GetMaxWearCount();

        if (m_money >= price)
        {
            m_money -= price;
            const auto& found = m_usableTools.find(tool);
            if (found != m_usableTools.end())
            {
                m_usableTools[tool] = wearCount;
            }
            else
            {
                m_usableTools[tool] += wearCount;
            }
            ToolBoughtEvent boughtEvent(*tool);
            m_eventDispatcher.DispatchEvent(boughtEvent);
        }
    }
    else
    {
        std::cerr << "Player::BuyTool: tool was nullptr !" << std::endl;
    }
}

void Player::InitTool(Tool* tool)
{
    if (tool != nullptr)
    {
        int wearCount = tool->GetMaxWearCount();
        m_usableTools[tool] = wearCount;
    }
    else
    {
        std::cerr << "Player::InitTool: tool was nullptr !" << std::endl;
    }
}