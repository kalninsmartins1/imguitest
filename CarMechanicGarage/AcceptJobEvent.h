#pragma once

#include "Event.h"
#include "EventType.h"

class AcceptJobEvent : public Event
{
public:
	AcceptJobEvent(int jobIndex);
	~AcceptJobEvent();

	inline EventType GetEventType() const override { return EventType::ACCEPT_JOB; }
	inline int GetJobIndex() const { return m_jobIndex; }

private:
	int m_jobIndex;
};
