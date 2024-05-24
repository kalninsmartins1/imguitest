#pragma once

#include <string>
#include <vector>
#include "Tool.h"

class Malfunction
{
public:
    Malfunction(const char* name, const std::vector<Tool*>& tools, const int fixCosts);
    ~Malfunction();

    inline const std::string& GetName() const { return m_name; }
    inline int GetFixCosts() const { return m_fixCosts;  }
    inline const std::vector<Tool*>& GetNeededTools() const { return m_tools; }

private:
    std::string m_name;
    std::vector<Tool*> m_tools;
    int m_fixCosts;
};

class Vehicle
{
public:
    Vehicle(const char* type);
    ~Vehicle();

    inline const std::string& GetType() const { return m_type; }
    inline const std::vector<Malfunction*>& GetPossibleMalfunctions() const { return m_malfunctions; }

    void AddMalfunction(Malfunction* value);

private:
    std::string m_type;
    std::vector<Malfunction*> m_malfunctions;
};

