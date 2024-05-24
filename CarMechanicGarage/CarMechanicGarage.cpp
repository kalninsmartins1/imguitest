#include <string>
#include <vector>
#include <iostream>
#include "CarMechanicGarage.h"
#include "Tool.h"
#include "Player.h"
#include "JobList.h"
#include "Vehicle.h"
#include "EventDispatcher.h"
#include "EventType.h"
#include "BuyToolEvent.h"
#include "AcceptJobEvent.h"


CarMechanicGarage::CarMechanicGarage(EventDispatcher& eventDispatcher)
    :   m_toolManager(new ToolManager()),
        m_player(new Player(eventDispatcher)),
        m_jobList(nullptr),
        m_eventDispatcher(eventDispatcher)
{
    InitTools();
    InitPlayer();
    InitVehicles();
    m_jobList.reset(new JobList(m_vehicles, eventDispatcher));

    m_eventDispatcher.SubscribeToEvent(std::bind(&CarMechanicGarage::OnBuyToolEvent, this, 
        std::placeholders::_1), EventType::BUY_TOOL);
    m_eventDispatcher.SubscribeToEvent(std::bind(&CarMechanicGarage::OnAcceptJobEvent, this,
        std::placeholders::_1), EventType::ACCEPT_JOB);
}

CarMechanicGarage::~CarMechanicGarage()
{
    for (const Vehicle* vehicle : m_vehicles)
    {
        if (vehicle != nullptr)
        {
            delete vehicle;
        }
    }
    m_vehicles.clear();
    m_eventDispatcher.UnsubscribeFromEvent(EventType::BUY_TOOL);
    m_eventDispatcher.UnsubscribeFromEvent(EventType::ACCEPT_JOB);
}

void CarMechanicGarage::InitTools()
{
    if (m_toolManager != nullptr)
    {
        m_toolManager->AddTool(new Tool("Jack", 50));
        m_toolManager->AddTool(new Tool("Torque brace", 40));
        m_toolManager->AddTool(new Tool("Jumper Cables", 20));
        m_toolManager->AddTool(new Tool("Phase tester", 10));
        m_toolManager->AddTool(new Tool("Hammer", 20));
        m_toolManager->AddTool(new Tool("Screwdriver", 10));
    }
    else
    {
        std::cerr << "CarMechanicGarage::InitTools: m_toolManager was nullptr !" << std::endl;
    }
}

void CarMechanicGarage::InitVehicles()
{
    if (m_toolManager != nullptr)
    {
        // init first vehicle
        Vehicle* motorCycle = new Vehicle("Racing motorcycle");

        std::vector<Tool*> requiredTools;
        requiredTools.emplace_back(m_toolManager->FindToolByName("Jack"));
        requiredTools.emplace_back(m_toolManager->FindToolByName("Torque brace"));
        motorCycle->AddMalfunction(new Malfunction("Flat tire", requiredTools, 18));

        requiredTools.clear();
        requiredTools.emplace_back(m_toolManager->FindToolByName("Jumper cables"));
        requiredTools.emplace_back(m_toolManager->FindToolByName("Phase tester"));
        motorCycle->AddMalfunction(new Malfunction("Empty battery", requiredTools, 6));

        requiredTools.clear();
        requiredTools.emplace_back(m_toolManager->FindToolByName("Phase tester"));
        motorCycle->AddMalfunction(new Malfunction("Lights not working", requiredTools, 2));

        // init second vehicle
        Vehicle* compactCar = new Vehicle("Family car");

        requiredTools.clear();
        requiredTools.emplace_back(m_toolManager->FindToolByName("Hammer"));
        requiredTools.emplace_back(m_toolManager->FindToolByName("Screwdriver"));
        requiredTools.emplace_back(m_toolManager->FindToolByName("Torque brace"));
        compactCar->AddMalfunction(new Malfunction("Broken shock absorber", requiredTools, 14));

        requiredTools.clear();
        requiredTools.emplace_back(m_toolManager->FindToolByName("Torque brace"));
        requiredTools.emplace_back(m_toolManager->FindToolByName("Screwdriver"));
        compactCar->AddMalfunction(new Malfunction("Failed engine", requiredTools, 10));

        requiredTools.clear();
        requiredTools.emplace_back(m_toolManager->FindToolByName("Phase tester"));
        requiredTools.emplace_back(m_toolManager->FindToolByName("Screwdriver"));
        compactCar->AddMalfunction(new Malfunction("Spark plug defect", requiredTools, 4));

        requiredTools.clear();
        requiredTools.emplace_back(m_toolManager->FindToolByName("Jumper cables"));
        requiredTools.emplace_back(m_toolManager->FindToolByName("Phase tester"));
        compactCar->AddMalfunction(new Malfunction("Battery is empty", requiredTools, 6));

        // init third vehicle
        Vehicle* racingCar = new Vehicle("Sports car");

        requiredTools.clear();
        requiredTools.emplace_back(m_toolManager->FindToolByName("Screwdriver"));
        requiredTools.emplace_back(m_toolManager->FindToolByName("Torque brace"));
        motorCycle->AddMalfunction(new Malfunction("Broken gas pedal", requiredTools, 10));

        requiredTools.clear();
        requiredTools.emplace_back(m_toolManager->FindToolByName("Torquebrace"));
        requiredTools.emplace_back(m_toolManager->FindToolByName("Screwdriver"));
        racingCar->AddMalfunction(new Malfunction("Failed engine", requiredTools, 10));

        requiredTools.clear();
        requiredTools.emplace_back(m_toolManager->FindToolByName("Jack"));
        requiredTools.emplace_back(m_toolManager->FindToolByName("Torque brace"));
        racingCar->AddMalfunction(new Malfunction("Tire is bald", requiredTools, 18));

        requiredTools.clear();
        requiredTools.emplace_back(m_toolManager->FindToolByName("Hammer"));
        requiredTools.emplace_back(m_toolManager->FindToolByName("Screwdriver"));
        racingCar->AddMalfunction(new Malfunction("Damaged bumper", requiredTools, 6));

        m_vehicles.emplace_back(motorCycle);
        m_vehicles.emplace_back(compactCar);
        m_vehicles.emplace_back(racingCar);
    }   
    else
    {
        std::cerr << "CarMechanicGarage::InitVehicles: m_toolManager was nullptr !" << std::endl;
    }
}

void CarMechanicGarage::InitPlayer()
{
    if (m_player != nullptr)
    {     
        m_player->InitTool(m_toolManager->FindToolByName("Jack"));
        m_player->InitTool(m_toolManager->FindToolByName("Torque brace"));
        m_player->InitTool(m_toolManager->FindToolByName("Hammer"));
    }
    else
    {
        std::cerr << "CarMechanicGarage::InitPlayer: m_player was nullptr !" << std::endl;
    }
}

void CarMechanicGarage::OnBuyToolEvent(const Event& genericEvent)
{
    if (genericEvent.GetEventType() == EventType::BUY_TOOL)
    {
        if (m_player != nullptr)
        {
            const BuyToolEvent& typedBuyToolEvent = static_cast<const BuyToolEvent&>(genericEvent);
            const Tool& toolToBuy = typedBuyToolEvent.GetToolToBuy();
            m_player->BuyTool(&toolToBuy);
        }
        else
        {
            std::cerr << "CarMechanicGarage::OnBuyToolEvent: m_player was nullptr !" << std::endl;
        }
    }    
}

void CarMechanicGarage::OnAcceptJobEvent(const Event& genericEvent)
{
    if (genericEvent.GetEventType() == EventType::ACCEPT_JOB)
    {
        if (m_jobList != nullptr)
        {
            const AcceptJobEvent& acceptJobEvent = static_cast<const AcceptJobEvent&>(genericEvent);
            m_jobList->AcceptJob(m_player.get(), acceptJobEvent.GetJobIndex());
        }
        else
        {
            std::cerr << "CarMechanicGarage::OnAcceptJobEvent: m_jobList was nullptr !" << std::endl;
        }
    }   
}
