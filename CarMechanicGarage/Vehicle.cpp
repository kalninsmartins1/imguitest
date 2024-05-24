#include <iostream>
#include "Vehicle.h"

Malfunction::Malfunction(const char* name, const std::vector<Tool*>& tools, const int fixCosts)
    :   m_name(name),
        m_tools(tools),
        m_fixCosts(fixCosts)
{
}

Malfunction::~Malfunction()
{
}

Vehicle::Vehicle(const char* type)
    :   m_type(type)
{
}

Vehicle::~Vehicle()
{
    for (const Malfunction* malfunction : m_malfunctions)
    {
        if (malfunction != nullptr)
        {
            delete malfunction;
        }
    }
    m_malfunctions.clear();
}

void Vehicle::AddMalfunction(Malfunction* value)
{
    if (value != nullptr)
    {
        m_malfunctions.emplace_back(value);
    }    
    else
    {
        std::cerr << "Vehicle::AddMalfunction: value was nullptr !" << std::endl;
    }
}
