#pragma once

#include <map>
#include <string>
#include <stdio.h>


constexpr int MAX_WEAR_COUNT = 5;

class ToolManager;

class Tool
{
public:
    Tool(const char* name, const int price);
    ~Tool();

    inline const std::string& GetName() const { return m_name; }
    inline int GetPrice() const { return m_price;  }
    inline constexpr int GetMaxWearCount() const { return MAX_WEAR_COUNT; }

private:
    std::string m_name;
    int m_price;
};

class ToolManager
{
public:
    ToolManager();
    ~ToolManager();
    
    inline const std::map<int, Tool*>& GetTools() const { return m_tools; }
    Tool* GetToolByIndex(int toolIndex) const;

    Tool* FindToolByName(const std::string& name) const;    

    void AddTool(Tool* tool);

private:
    std::map<int, Tool*> m_tools;
};
