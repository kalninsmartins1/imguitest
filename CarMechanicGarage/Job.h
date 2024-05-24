#pragma once

#include <vector>
#include <string>

class Tool;
class Malfunction;

class Job
{
public:
	Job(const std::string& vehicleType, const Malfunction& malfunction);
	~Job();

	inline const std::string& GetVehicleType() const { return m_vehicleType; }
	inline const Malfunction& GetMalfunction() const { return m_malfunction; }
	const std::vector<Tool*>& GetNeededTools() const;

	int GetMoneyRewardAmount() const;

private:
	const std::string& m_vehicleType;
	const Malfunction& m_malfunction;
};

