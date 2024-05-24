#include "Job.h"
#include "Vehicle.h"

Job::Job(const std::string& vehicleType, const Malfunction& malfunction)
	:	m_vehicleType(vehicleType),
		m_malfunction(malfunction)
{
}

Job::~Job()
{
}

const std::vector<Tool*>& Job::GetNeededTools() const
{
	return m_malfunction.GetNeededTools();
}

int Job::GetMoneyRewardAmount() const
{
	return m_malfunction.GetFixCosts();
}
