#pragma once

#include <vector>
#include <map>
#include <memory>

class Vehicle;
class Job;
class Player;
class EventDispatcher;
class Tool;

class JobList
{
public:
	JobList(const std::vector<Vehicle*>& vehicles, EventDispatcher& eventDispatcher);
	~JobList();

	inline const std::map<int, std::unique_ptr<Job>>& GetAvailableJobs() const { return m_jobs; }	

	void AcceptJob(Player* player, int jobIndex);

private:			
	void GenerateRandomJob(int jobIndex);	

private:
	static constexpr int MAX_JOBS = 10;

	const std::vector<Vehicle*>& m_vehicles;
	std::map<int, std::unique_ptr<Job>> m_jobs;
	EventDispatcher& m_eventDispatcher;
};

