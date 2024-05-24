#include <iostream>
#include "JobList.h"
#include "Job.h"
#include "Vehicle.h"
#include "Player.h"
#include "EventDispatcher.h"
#include "JobResultEvent.h"

JobList::JobList(const std::vector<Vehicle*>& vehicles, EventDispatcher& eventDispatcher)
	:	m_vehicles(vehicles),
		m_jobs(),		
		m_eventDispatcher(eventDispatcher)
{
	for (int index = 0; index < MAX_JOBS; ++index)
	{
		GenerateRandomJob(index);
	}
}

JobList::~JobList()
{
}

void JobList::AcceptJob(Player* player, int jobIndex)
{
	if (player != nullptr)
	{
		Job* job = m_jobs[jobIndex].get();
		if (job != nullptr)
		{
			const std::vector<Tool*>& neededTools = job->GetNeededTools();									
			bool isJobSuccessful = player->AttemptJob(neededTools);
			if (isJobSuccessful)
			{
				player->ReceiveMoney(job->GetMoneyRewardAmount());				
			}									
			JobResultEvent jobResultEvent(isJobSuccessful, player->GetToolsUsedForLastJob());
			m_eventDispatcher.DispatchEvent(jobResultEvent);	
			GenerateRandomJob(jobIndex);
		}
		else
		{
			std::cerr << "JobList::AcceptJob: job was nullptr !" << std::endl;
		}
	}
	else
	{
		std::cerr << "JobList::AcceptJob: player was nullptr !" << std::endl;
	}
}

void JobList::GenerateRandomJob(int jobIndex)
{
	if (!m_vehicles.empty())
	{
		const Vehicle* randomVehicle = m_vehicles[std::rand() % m_vehicles.size()];
		const std::vector<Malfunction*>& possibleMalfunctions = randomVehicle->GetPossibleMalfunctions();
		const Malfunction* randomMalfunction = possibleMalfunctions[std::rand() % possibleMalfunctions.size()];

		if (randomVehicle != nullptr && randomMalfunction != nullptr)
		{
			m_jobs[jobIndex].reset(new Job(randomVehicle->GetType(), *randomMalfunction));
		}
		else
		{
			std::cerr << "JobList::GenerateRandomJob: randomVehicle and/or randomMalfunction was nullptr !" << std::endl;
		}
	}
	else
	{
		std::cerr << "JobList::GenerateRandomJob: m_vehicles was empty !" << std::endl;
	}
}