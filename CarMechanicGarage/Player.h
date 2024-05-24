#pragma once

#include <vector>
#include <string>
#include "Tool.h"

constexpr int START_MONEY = 200;

class EventDispatcher;

class Player
{
public:
    Player(EventDispatcher& eventDispatcher);
    ~Player();

    inline int GetCurrentMoneyAmount() const { return m_money; }
    inline const std::map<const Tool*, int>& GetToolsUsedForLastJob() const { return m_toolsUsedForLastJob; }    
    inline const std::map<const Tool*, int>& GetUsableTools() const { return m_usableTools; }
    int GetToolWear(const Tool* tool) const;

    bool AttemptJob(const std::vector<Tool*>& requiredTools);
    void ReceiveMoney(int amount);
    void BuyTool(const Tool* tool);
    void InitTool(Tool* tool);

private:
    int m_money;
    EventDispatcher& m_eventDispatcher;
    std::map<const Tool*, int> m_usableTools;
    std::map<const Tool*, int> m_toolsUsedForLastJob;
};

