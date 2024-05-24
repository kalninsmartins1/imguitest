#include <iostream>
#include "Tool.h"


Tool::Tool(const char* name, const int price)
    :   m_name(name),
        m_price(price)
{
    
}

Tool::~Tool()
{
}

ToolManager::ToolManager()
{  
}

ToolManager::~ToolManager()
{
    for (const auto& toolIterator : m_tools)
    {
        Tool* tool = toolIterator.second;
        if (tool != nullptr)
        {
            delete tool;
        }        
    }
    m_tools.clear();
}

Tool* ToolManager::GetToolByIndex(int toolIndex) const
{
    Tool* result = nullptr;
    const auto& toolsIterator = m_tools.find(toolIndex);

    if(toolsIterator != m_tools.end())
    {
        result = toolsIterator->second;        
    }
    return result;
}

void ToolManager::AddTool(Tool* tool)
{
    if (tool != nullptr)
    {
        const int nextIndex = m_tools.size();
        m_tools[nextIndex] = tool;
    }
    else
    {
        std::cerr << "Player::AddTool: tool was nullptr !" << std::endl;
    }
}

Tool* ToolManager::FindToolByName(const std::string& name) const
{
    Tool* found = nullptr;

    for (auto iter(m_tools.begin()); iter != m_tools.end(); ++iter)
    {
        Tool* tool = iter->second;
        if (tool != nullptr && tool->GetName() == name)
        {
            found = tool;
            break;
        }
    }

    return found;
}
