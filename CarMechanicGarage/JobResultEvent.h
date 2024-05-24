#pragma once

#include <map>
#include "Event.h"
#include "EventType.h"

class Tool;

class JobResultEvent : public Event
{
public:
	JobResultEvent(bool isJobSuccessful, const std::map<const Tool*, int>& usedTools);
	~JobResultEvent();

	inline EventType GetEventType() const override { return EventType::ACCEPT_JOB_RESULT; };
	inline bool IsJobSuccessful() const { return m_isJobSuccessful; }
	inline const std::map<const Tool*, int>& GetUsedTools() const { return m_usedTools; }

private:
	const std::map<const Tool*, int>& m_usedTools;
	bool m_isJobSuccessful;
};