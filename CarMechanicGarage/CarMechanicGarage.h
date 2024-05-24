#pragma once

#include <memory>
#include <vector>

class ToolManager;
class Player;
class Vehicle;
class JobList;
class EventDispatcher;
class Event;

class CarMechanicGarage
{
public:
	CarMechanicGarage(EventDispatcher& eventDispatcher);
	~CarMechanicGarage();

	inline const JobList& GetJobList() const { return *m_jobList; }
	inline const Player& GetPlayer() const { return *m_player; }
	inline const ToolManager& GetToolManger() const { return *m_toolManager; }

private:
	void InitTools();
	void InitVehicles();
	void InitPlayer();

	void OnBuyToolEvent(const Event& genericEvent);
	void OnAcceptJobEvent(const Event& genericEvent);

private:
	std::unique_ptr<ToolManager> m_toolManager;
	std::unique_ptr<Player> m_player;
	std::unique_ptr<JobList> m_jobList;	

	EventDispatcher& m_eventDispatcher;
	std::vector<Vehicle*> m_vehicles;
};